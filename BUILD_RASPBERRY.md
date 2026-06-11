# Decodius su Raspberry Pi 4 (Linux ARM)

Decodius è C++/Qt6/QML standard, quindi gira anche su **Raspberry Pi 4 / Pi 5** con
Raspberry Pi OS (64-bit). Il "cervello" è in cloud (NVIDIA NIM): al Pi servono solo
le chiamate HTTP. Whisper STT locale è opzionale (lento su ARM); voce e cervello sono cloud.

> Consigliato: **Pi 4 (4–8 GB) o Pi 5**, Raspberry Pi OS **64-bit (Bookworm)**, scheda ≥16 GB.

---

## 1. Dipendenze

```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build \
  qt6-base-dev qt6-declarative-dev qt6-multimedia-dev \
  qml6-module-qtquick qml6-module-qtquick-controls \
  qml6-module-qtquick-layouts qml6-module-qtquick-window \
  qml6-module-qtquick-effects qml6-module-qtmultimedia \
  libqt6texttospeech6 qt6-speech-dev \
  python3 python3-pip
# voce (edge-tts, Microsoft cloud) — naturale e gratuita:
pip3 install --break-system-packages edge-tts
# (opzionale) STT locale, lento su ARM:
# pip3 install --break-system-packages faster-whisper
```

> Se `qt6-speech-dev` non c'è sui repo, Decodius compila lo stesso (senza `HAVE_TTS`)
> e usa comunque la voce edge via `edge/edge_server.py`.

---

## 2. Build

```bash
git clone https://github.com/iu8lmc/Decodius.git
cd Decodius
cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
# eseguibile: build/decodius
```

L'icona/risorse e `world.png` sono incorporati nel binario (risorse QML). Copia accanto
all'eseguibile i file di runtime: `decodius_system.txt`, `decodius_model.txt`,
`decodius_ham_kb.md`, e la cartella `edge/` (con `edge_server.py`).

---

## 3. Configurazione (la parte specifica del Pi)

### 3.1 Cervello (LLM)
Crea `decodius_provider.txt` accanto all'eseguibile:
```
base_url=https://integrate.api.nvidia.com/v1
api_key=nvapi-LA_TUA_CHIAVE
model=meta/llama-3.3-70b-instruct
```
Oppure un Ollama in rete: `base_url=http://<host>:11434/v1` ... (o lascia il default Ollama locale se installato sul Pi).

### 3.2 Decodium 4 (su un altro PC della LAN)
Su Linux NON c'è il registro di Windows: indica dove gira Decodium con
`decodius_decodium.txt` accanto all'eseguibile:
```
host=192.168.1.20        # IP del PC dove gira Decodium
web_port=8080
web_token=IL_TOKEN_WEB   # da Decodium: Settings -> Web Server (token generato)
cmd_port=19091
cmd_user=admin
cmd_token=               # vuoto se il command server è su loopback senza token
```
> Su quel PC, in Decodium imposta **WS bind = 0.0.0.0** (per accettare la LAN) e un
> **token** sul command server, e riportalo qui in `cmd_token`. (Su loopback il token
> non serve, ma da un altro host sì.)

### 3.3 Nominativo e HamQTH
- Il nominativo si imposta al primo avvio (salvato in `~/.config/Decodius/`).
- Per il lookup HamQTH crea `decodius_hamqth.txt` (riga1 utente, riga2 password).

---

## 4. Avvio

```bash
cd ~/Decodius/build
./decodius
```

Per avvio automatico a schermo intero (kiosk), crea un servizio systemd-user o un
`.desktop` in autostart che lancia `./decodius`.

---

## 5. Note prestazioni sul Pi
- La UI usa effetti **QtQuick MultiEffect** (blur/glow): sul Pi possono pesare.
  Se l'orb risulta scattoso, si possono ridurre gli effetti in `Main.qml`.
- **Voce** (edge-tts) e **cervello** (cloud): nessun carico locale, solo rete.
- **STT** locale (Whisper) è lento su ARM: meglio usare Decodius **a tastiera/touch**,
  oppure uno STT cloud in futuro.
- Audio: assicurati che ALSA/PulseAudio abbia l'uscita giusta (`pavucontrol`).

---

## 6. Cosa cambia rispetto a Windows
| Aspetto | Windows | Raspberry Pi (Linux) |
|--------|---------|----------------------|
| Config Decodium | registro (auto) | file `decodius_decodium.txt` |
| Host Decodium | `127.0.0.1` | IP del PC sulla LAN |
| Python voce | `pyedge`/`C:\Python314` | `python3` di sistema |
| Build | MSVC + Ninja | gcc + Ninja (apt) |
| Installer | Inno Setup (.exe) | build da sorgente |

Tutto il resto (UI, integrazione, comandi, scheda QRZ, roster, mappa) è identico.
