# Decodius su macOS (Apple Silicon / Intel)

Decodius è C++/Qt6/QML: compila **nativamente su Mac Apple Silicon** (M1/M2/M3/M4) e su
Intel. Il "cervello" (LLM) è in cloud, quindi al Mac servono solo le chiamate HTTP.

> Consigliato: **macOS 13+ (Ventura/Sonoma)**, **Apple Silicon**, Qt 6.5+.

---

## ⚡ Setup rapido (automatico)
```bash
git clone https://github.com/iu8lmc/Decodius.git
cd Decodius
chmod +x setup_mac.sh && ./setup_mac.sh
```
Installa le dipendenze (Homebrew), compila, configura (cervello, Decodium, HamQTH) e crea
il bundle `Decodius.app`. Le sezioni sotto sono il riferimento manuale.

---

## 1. Dipendenze (Homebrew)
```bash
# Xcode Command Line Tools (se non già installati)
xcode-select --install
# Homebrew: https://brew.sh
brew install qt cmake ninja python
# voce (edge-tts, Microsoft cloud):
pip3 install edge-tts
```

## 2. Build
```bash
git clone https://github.com/iu8lmc/Decodius.git
cd Decodius
cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
cmake --build build
# risultato: build/decodius.app
```

Per un'app distribuibile (incorpora i framework Qt):
```bash
"$(brew --prefix qt)/bin/macdeployqt" build/decodius.app -qmldir=.
```

## 3. Configurazione (accanto all'eseguibile, dentro il bundle: `decodius.app/Contents/MacOS/`)
- **Cervello** → `decodius_provider.txt`:
  ```
  base_url=https://integrate.api.nvidia.com/v1
  api_key=nvapi-LA_TUA_CHIAVE
  model=meta/llama-3.3-70b-instruct
  ```
- **Decodium 4** (gira su un PC Windows della LAN — non su Mac) → `decodius_decodium.txt`:
  ```
  host=192.168.1.20
  web_port=8080
  web_token=IL_TOKEN_WEB
  cmd_port=19091
  cmd_user=admin
  cmd_token=
  ```
- **HamQTH** → `decodius_hamqth.txt` (riga1 utente, riga2 password).
- **Nominativo**: chiesto al primo avvio (salvato in `~/Library/Preferences` / config).

> Suggerimento: tieni i file di config **accanto al bundle** e lancia con
> `./build/decodius.app/Contents/MacOS/decodius` durante lo sviluppo.

## 4. Avvio
```bash
open build/decodius.app
# oppure, per vedere i log:
./build/decodius.app/Contents/MacOS/decodius
```

## 5. Note macOS
- **Apple Silicon nativo**: Qt arm64, nessuna emulazione.
- **Voce** (edge-tts) e **cervello** (cloud): solo rete, zero carico locale.
- **STT locale** (Whisper) non incluso sul Mac: usa Decodius a tastiera, oppure aggiungeremo uno STT cloud.
- **Audio**: l'uscita usa CoreAudio via Qt Multimedia (di default l'uscita di sistema).
- **Permessi**: al primo uso del microfono macOS chiede l'autorizzazione (Impostazioni → Privacy → Microfono).
- **Gatekeeper**: un'app non firmata va aperta con tasto destro → "Apri" la prima volta (o `xattr -dr com.apple.quarantine build/decodius.app`).

## 6. Differenze rispetto a Windows
| Aspetto | Windows | macOS |
|--------|---------|-------|
| Config Decodium | registro (auto) | file `decodius_decodium.txt` |
| Host Decodium | `127.0.0.1` | IP del PC Windows sulla LAN |
| Python voce | `pyedge`/`C:\Python314` | `python3` (Homebrew) |
| Output | `decodius.exe` | `decodius.app` |
| Build | MSVC + Ninja | clang + Ninja (Xcode CLT) |

Tutto il resto (UI, integrazione, comandi, scheda QRZ, roster, mappa) è identico.
