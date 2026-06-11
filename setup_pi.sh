#!/usr/bin/env bash
# ============================================================================
#  setup_pi.sh — installa, compila e configura DECODIUS su Raspberry Pi OS (64-bit).
#  Uso:   chmod +x setup_pi.sh && ./setup_pi.sh
#  Eseguilo dalla cartella del repo Decodius (dove c'è CMakeLists.txt).
# ============================================================================
set -uo pipefail

c()  { printf '\033[36m%s\033[0m\n' "$*"; }   # info
ok() { printf '\033[32m%s\033[0m\n' "$*"; }   # ok
wr() { printf '\033[33m%s\033[0m\n' "$*"; }   # warning
er() { printf '\033[31m%s\033[0m\n' "$*"; }   # error

ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT"
if [ ! -f CMakeLists.txt ]; then
  er "CMakeLists.txt non trovato: esegui questo script dalla cartella del repo Decodius."
  exit 1
fi

echo
c "============================================"
c "  DECODIUS — setup Raspberry Pi"
c "============================================"
echo

# --- 1. Dipendenze -----------------------------------------------------------
c "[1/5] Installazione dipendenze (richiede sudo)…"
sudo apt update
sudo apt install -y build-essential cmake ninja-build \
  qt6-base-dev qt6-declarative-dev qt6-multimedia-dev \
  qml6-module-qtquick qml6-module-qtquick-controls \
  qml6-module-qtquick-layouts qml6-module-qtquick-window \
  qml6-module-qtquick-templates qml6-module-qtquick-effects \
  qml6-module-qtmultimedia qml6-module-qtqml-workerscript \
  python3 python3-pip || wr "Alcuni pacchetti potrebbero avere nomi diversi sulla tua distro."
# Qt TextToSpeech (opzionale: se manca, Decodius compila comunque)
sudo apt install -y qt6-speech-dev 2>/dev/null || wr "qt6-speech-dev non disponibile (ok, voce via edge-tts)."
# Voce edge-tts (Microsoft cloud)
c "Installazione edge-tts…"
pip3 install --break-system-packages edge-tts 2>/dev/null \
  || pip3 install edge-tts \
  || wr "edge-tts non installato: installalo a mano con 'pip3 install edge-tts'."
ok "Dipendenze ok."

# --- 2. Build ----------------------------------------------------------------
echo; c "[2/5] Compilazione (Ninja, $(nproc) core)…"
cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc)"
[ -x build/decodius ] || { er "Build fallita: build/decodius non creato."; exit 1; }
ok "Compilato: build/decodius"

# --- 3. File di runtime accanto all'eseguibile -------------------------------
echo; c "[3/5] Copio i file di runtime in build/…"
for f in decodius_system.txt decodius_model.txt decodius_ham_kb.md; do
  [ -f "$f" ] && cp -f "$f" build/ && echo "  + $f"
done
[ -d edge ] && cp -rf edge build/ && echo "  + edge/"
ok "Runtime pronto."

# --- 4. Configurazione -------------------------------------------------------
echo; c "[4/5] Configurazione (invio per saltare un campo)…"
cd build

# Cervello (provider cloud)
if [ ! -f decodius_provider.txt ]; then
  read -r -p "  Chiave NVIDIA (nvapi-…): " KEY
  if [ -n "${KEY:-}" ]; then
    cat > decodius_provider.txt <<EOF
base_url=https://integrate.api.nvidia.com/v1
api_key=$KEY
model=meta/llama-3.3-70b-instruct
EOF
    chmod 600 decodius_provider.txt
    ok "  decodius_provider.txt creato."
  else
    wr "  Nessuna chiave: userai Ollama locale (installalo, o lancia di nuovo per il cloud)."
  fi
fi

# Decodium (su un PC della LAN)
if [ ! -f decodius_decodium.txt ]; then
  read -r -p "  IP del PC con Decodium [127.0.0.1]: " DHOST
  read -r -p "  Token web Decodium (8080): " DWTOK
  read -r -p "  Token comandi Decodium (19091, vuoto se loopback): " DCTOK
  cat > decodius_decodium.txt <<EOF
host=${DHOST:-127.0.0.1}
web_port=8080
web_token=${DWTOK:-}
cmd_port=19091
cmd_user=admin
cmd_token=${DCTOK:-}
EOF
  ok "  decodius_decodium.txt creato."
fi

# HamQTH (lookup nominativi)
if [ ! -f decodius_hamqth.txt ]; then
  read -r -p "  Utente HamQTH: " HU
  if [ -n "${HU:-}" ]; then
    read -r -s -p "  Password HamQTH: " HP; echo
    printf '%s\n%s\n' "$HU" "$HP" > decodius_hamqth.txt
    chmod 600 decodius_hamqth.txt
    ok "  decodius_hamqth.txt creato."
  fi
fi
cd "$ROOT"

# --- 5. Avvio automatico (kiosk) opzionale -----------------------------------
echo; c "[5/5] Avvio automatico a schermo intero all'accensione?"
read -r -p "  Crea autostart kiosk? [s/N]: " KIOSK
if [[ "${KIOSK:-N}" =~ ^[sS] ]]; then
  mkdir -p "$HOME/.config/autostart"
  cat > "$HOME/.config/autostart/decodius.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=Decodius
Exec=$ROOT/build/decodius
X-GNOME-Autostart-enabled=true
EOF
  ok "  Autostart creato: ~/.config/autostart/decodius.desktop"
fi

echo
ok "============================================"
ok "  FATTO!  Avvia con:  $ROOT/build/decodius"
ok "============================================"
echo
