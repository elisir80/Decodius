#!/usr/bin/env bash
# ============================================================================
#  setup_mac.sh — installa, compila e configura DECODIUS su macOS (Apple Silicon/Intel).
#  Uso:   chmod +x setup_mac.sh && ./setup_mac.sh
#  Eseguilo dalla cartella del repo Decodius (dove c'è CMakeLists.txt).
# ============================================================================
set -uo pipefail

c()  { printf '\033[36m%s\033[0m\n' "$*"; }
ok() { printf '\033[32m%s\033[0m\n' "$*"; }
wr() { printf '\033[33m%s\033[0m\n' "$*"; }
er() { printf '\033[31m%s\033[0m\n' "$*"; }

ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT"
[ -f CMakeLists.txt ] || { er "Esegui dalla cartella del repo Decodius (CMakeLists.txt non trovato)."; exit 1; }

echo; c "============================================"
c "  DECODIUS — setup macOS"
c "============================================"; echo

# --- 1. Dipendenze (Homebrew) ------------------------------------------------
c "[1/5] Dipendenze…"
if ! command -v brew >/dev/null 2>&1; then
  er "Homebrew non trovato. Installalo da https://brew.sh e rilancia."; exit 1
fi
if ! xcode-select -p >/dev/null 2>&1; then
  wr "Installo gli Xcode Command Line Tools (conferma la finestra)…"; xcode-select --install || true
fi
brew install qt cmake ninja python || wr "Alcuni pacchetti potrebbero essere già installati."
pip3 install edge-tts 2>/dev/null || pip3 install --user edge-tts || wr "edge-tts non installato: 'pip3 install edge-tts'."
ok "Dipendenze ok."

QT_PREFIX="$(brew --prefix qt)"

# --- 2. Build ----------------------------------------------------------------
echo; c "[2/5] Compilazione (Ninja)…"
cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$QT_PREFIX"
cmake --build build -j"$(sysctl -n hw.ncpu)"
APP="build/decodius.app"
BIN="$APP/Contents/MacOS/decodius"
[ -x "$BIN" ] || { er "Build fallita: $BIN non creato."; exit 1; }
ok "Compilato: $APP"

# --- 3. Bundle (incorpora i framework Qt) ------------------------------------
echo; c "[3/5] macdeployqt…"
"$QT_PREFIX/bin/macdeployqt" "$APP" -qmldir=. 2>/dev/null || wr "macdeployqt non riuscito (l'app gira lo stesso in locale)."

# --- 4. File di runtime + configurazione -------------------------------------
echo; c "[4/5] Runtime e configurazione…"
DEST="$APP/Contents/MacOS"
for f in decodius_system.txt decodius_model.txt decodius_ham_kb.md; do
  [ -f "$f" ] && cp -f "$f" "$DEST/" && echo "  + $f"
done
[ -d edge ] && cp -rf edge "$DEST/" && echo "  + edge/"

if [ ! -f "$DEST/decodius_provider.txt" ]; then
  read -r -p "  Chiave NVIDIA (nvapi-…): " KEY
  if [ -n "${KEY:-}" ]; then
    printf 'base_url=https://integrate.api.nvidia.com/v1\napi_key=%s\nmodel=meta/llama-3.3-70b-instruct\n' "$KEY" > "$DEST/decodius_provider.txt"
    chmod 600 "$DEST/decodius_provider.txt"; ok "  provider configurato."
  fi
fi
if [ ! -f "$DEST/decodius_decodium.txt" ]; then
  read -r -p "  IP del PC con Decodium [127.0.0.1]: " DH
  read -r -p "  Token web Decodium: " DWT
  read -r -p "  Token comandi Decodium (vuoto se loopback): " DCT
  printf 'host=%s\nweb_port=8080\nweb_token=%s\ncmd_port=19091\ncmd_user=admin\ncmd_token=%s\n' "${DH:-127.0.0.1}" "${DWT:-}" "${DCT:-}" > "$DEST/decodius_decodium.txt"
  ok "  Decodium configurato."
fi
if [ ! -f "$DEST/decodius_hamqth.txt" ]; then
  read -r -p "  Utente HamQTH: " HU
  if [ -n "${HU:-}" ]; then
    read -r -s -p "  Password HamQTH: " HP; echo
    printf '%s\n%s\n' "$HU" "$HP" > "$DEST/decodius_hamqth.txt"; chmod 600 "$DEST/decodius_hamqth.txt"; ok "  HamQTH configurato."
  fi
fi

# --- 5. Sblocca Gatekeeper (app non firmata) ---------------------------------
echo; c "[5/5] Rimuovo l'attributo di quarantena (app non firmata)…"
xattr -dr com.apple.quarantine "$APP" 2>/dev/null || true

echo; ok "============================================"
ok "  FATTO!  Avvia con:  open $APP"
ok "============================================"; echo
