# whisper_server.py — STT locale per Decodius (faster-whisper su CPU).
# Cattura il microfono con VAD a energia e trascrive in italiano.
#   GET /health  -> 200 "ok"
#   GET /ready   -> 200 "ready" | 503
#   GET /device  -> 200 JSON {"index":..,"name":..} dispositivo di input in uso
#   GET /listen  -> registra finché parli, poi 200 JSON {"text": "..."}
#
# Microfono: di default segue il dispositivo di input di Windows, MA puoi
# fissarlo (consigliato: i mic virtuali tipo "WO Mic"/"VB-Cable" possono
# diventare muti senza preavviso e Decodius ammutolirebbe in silenzio).
# Preferenza letta in quest'ordine: --device <idx|nome> | env DECODIUS_MIC |
# file decodius_mic.txt (accanto allo script o in %LOCALAPPDATA%\Decodius).
# Il valore può essere un indice numerico o una sottostringa del nome (es. "WO Mic").
import os, sys, io, json, time, threading, argparse, traceback

# Sotto pythonw.exe (avvio persistente senza console) stdout/stderr sono None:
# print() fallirebbe e bloccherebbe il caricamento del modello. Li dirotto su devnull.
if sys.stdout is None:
    sys.stdout = open(os.devnull, "w", encoding="utf-8")
if sys.stderr is None:
    sys.stderr = open(os.devnull, "w", encoding="utf-8")
try:
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    sys.stderr.reconfigure(encoding="utf-8", errors="replace")
except Exception:
    pass

import numpy as np

READY = False
ERROR = None
g_model = None
g_lock = threading.Lock()   # un ascolto alla volta
g_device = None             # indice del dispositivo di input scelto (None = default di sistema)
g_device_name = "default di sistema"

SR = 16000                  # faster-whisper lavora a 16 kHz mono
CHUNK = 480                 # 30 ms
START_TIMEOUT = 30.0        # attesa voce (always-on): cicli lunghi, pochi "buchi"
SILENCE_END = 0.35          # silenzio (s) dopo il parlato per chiudere (molto reattivo)
MAX_UTTER = 8.0            # durata massima frase (limita anche il tempo di reazione del barge-in)
RMS_THRESH = 0.012          # soglia voce abbassata: il WO Mic ha livello basso

# Log persistente su file: sotto pythonw.exe stdout va su devnull, quindi senza
# questo file i messaggi (device scelto, livelli bassi) sarebbero invisibili.
LOG_PATH = None
def log(*a):
    msg = "[whisper] " + " ".join(str(x) for x in a)
    try: print(msg, flush=True)
    except Exception: pass
    try:
        if LOG_PATH:
            with open(LOG_PATH, "a", encoding="utf-8") as f:
                f.write(msg + "\n")
    except Exception:
        pass

def _read_mic_pref(script_dir):
    """Preferenza microfono: env DECODIUS_MIC, poi decodius_mic.txt (script dir / LOCALAPPDATA)."""
    env = os.environ.get("DECODIUS_MIC", "").strip()
    if env:
        return env
    candidates = [os.path.join(script_dir, "decodius_mic.txt")]
    la = os.environ.get("LOCALAPPDATA", "")
    if la:
        candidates.append(os.path.join(la, "Decodius", "decodius_mic.txt"))
    for p in candidates:
        try:
            with open(p, "r", encoding="utf-8") as f:
                v = f.read().strip()
                if v:
                    return v
        except Exception:
            pass
    return ""

def resolve_device(pref):
    """pref: indice numerico o sottostringa del nome. Ritorna (idx|None, descrizione)."""
    import sounddevice as sd
    devs = sd.query_devices()
    if pref:
        if pref.lstrip("-").isdigit():           # indice numerico esplicito
            i = int(pref)
            if 0 <= i < len(devs) and devs[i].get("max_input_channels", 0) > 0:
                return i, devs[i]["name"]
        low = pref.lower()                        # match per nome (sottostringa)
        for i, d in enumerate(devs):
            if d.get("max_input_channels", 0) > 0 and low in d["name"].lower():
                return i, d["name"]
        log(f"ATTENZIONE: microfono '{pref}' non trovato tra i device di input, uso il default")
    try:                                          # default di sistema
        di = sd.default.device[0]
        if di is not None and di >= 0 and devs[di].get("max_input_channels", 0) > 0:
            return di, devs[di]["name"]
    except Exception:
        pass
    return None, "default di sistema"

def resolve_model(model_name, script_dir):
    """Modello BUNDLATO accanto allo script (installazione portabile, offline) se
    presente; altrimenti il nome simbolico (es. 'small') scaricato da HuggingFace."""
    bundled = os.path.join(script_dir, "model")
    if os.path.exists(os.path.join(bundled, "model.bin")):
        log("uso il modello bundlato:", bundled)
        return bundled
    return model_name

def load_model(model_name):
    global READY, ERROR, g_model
    try:
        from faster_whisper import WhisperModel
        log("carico modello", model_name, "(cpu/int8)...")
        g_model = WhisperModel(model_name, device="cpu", compute_type="int8")
        # warm-up su silenzio
        g_model.transcribe(np.zeros(SR, dtype=np.float32), language="it", beam_size=1)
        READY = True
        log("READY")
    except Exception as e:
        ERROR = "".join(traceback.format_exception(e))
        log("ERRORE load:\n", ERROR)

def record_utterance():
    """Registra dal mic: attende la voce, poi chiude al silenzio. Ritorna float32 mono 16k."""
    import sounddevice as sd
    frames = []
    started = False
    silence = 0.0
    peak = 0.0
    t0 = time.time()
    with sd.InputStream(samplerate=SR, channels=1, dtype="float32",
                        blocksize=CHUNK, device=g_device) as stream:
        while True:
            data, _ = stream.read(CHUNK)
            mono = data[:, 0]
            rms = float(np.sqrt(np.mean(mono * mono)) + 1e-9)
            peak = max(peak, float(np.max(np.abs(mono))))
            now = time.time()
            if not started:
                if rms > RMS_THRESH:
                    started = True
                    frames.append(mono.copy())
                elif now - t0 > START_TIMEOUT:
                    # Niente voce per tutto il timeout: rendilo VISIBILE (mic muto/scollegato?).
                    log(f"nessuna voce in {START_TIMEOUT:.0f}s su [{g_device}] {g_device_name} "
                        f"(picco={peak:.4f}, soglia={RMS_THRESH}) -> mic muto o scollegato?")
                    return None   # nessuno ha parlato
            else:
                frames.append(mono.copy())
                if rms < RMS_THRESH:
                    silence += CHUNK / SR
                    if silence > SILENCE_END:
                        break
                else:
                    silence = 0.0
                if now - t0 > MAX_UTTER:
                    break
    if not frames:
        return None
    return np.concatenate(frames).astype(np.float32)

def transcribe():
    with g_lock:
        audio = record_utterance()
        if audio is None or audio.size < SR // 3:
            return ""
        # Anti-allucinazione: se il livello è troppo basso è quasi-silenzio; NON gainare
        # (amplificherebbe solo rumore) e NON trascrivere (Whisper inventerebbe frasi).
        pk = float(np.max(np.abs(audio)))
        rms = float(np.sqrt(np.mean(audio * audio)))
        if pk < 0.05 or rms < 0.012:
            log(f"livello troppo basso (picco={pk:.3f} rms={rms:.3f}): ignoro per non allucinare")
            return ""
        # Auto-guadagno: il WO Mic ha livello basso; normalizzo a picco ~0,9.
        audio = np.clip(audio * (0.9 / pk), -1.0, 1.0).astype(np.float32)
        segments, _ = g_model.transcribe(audio, language="it", beam_size=5,
                                         vad_filter=False, condition_on_previous_text=False)
        text = " ".join(s.text for s in segments).strip()
        # Filtro allucinazioni note di Whisper su audio sporco/silenzio.
        low = text.lower()
        for h in ("sottotitoli", "qtss", "amara.org", "sous-titr", "subtitle",
                  "grazie per l'attenzione", "iscrivetevi al canale"):
            if h in low:
                return ""
        return text

from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

class Handler(BaseHTTPRequestHandler):
    def log_message(self, *a): pass
    def _send(self, code, body=b"", ctype="text/plain; charset=utf-8"):
        self.send_response(code); self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(body))); self.end_headers()
        if body: self.wfile.write(body)
    def do_GET(self):
        if self.path == "/health":
            self._send(200, b"ok")
        elif self.path == "/ready":
            self._send(200, b"ready") if READY else self._send(503, b"loading")
        elif self.path == "/device":
            self._send(200, json.dumps({"index": g_device, "name": g_device_name}).encode("utf-8"),
                       "application/json")
        elif self.path == "/shutdown":
            self._send(200, b"bye"); threading.Thread(target=lambda:(time.sleep(0.2), os._exit(0)), daemon=True).start()
        elif self.path == "/listen":
            if not READY: self._send(503, b"not ready"); return
            try:
                text = transcribe()
                self._send(200, json.dumps({"text": text}).encode("utf-8"), "application/json")
            except Exception as e:
                self._send(500, ("errore stt: " + str(e)).encode("utf-8"))
        else:
            self._send(404, b"not found")

def main():
    global g_device, g_device_name, LOG_PATH
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=5068)
    ap.add_argument("--model", default="small")
    ap.add_argument("--device", default="", help="indice o nome (sottostringa) del microfono")
    args = ap.parse_args()

    script_dir = os.path.dirname(os.path.abspath(__file__))
    LOG_PATH = os.path.join(script_dir, "whisper_server.log")

    pref = args.device.strip() or _read_mic_pref(script_dir)
    g_device, g_device_name = resolve_device(pref)
    log(f"microfono: [{g_device}] {g_device_name}" + (f" (preferenza='{pref}')" if pref else " (default)"))

    model = resolve_model(args.model, script_dir)
    threading.Thread(target=load_model, args=(model,), daemon=True).start()
    srv = ThreadingHTTPServer(("127.0.0.1", args.port), Handler)
    log(f"in ascolto su http://127.0.0.1:{args.port}")
    srv.serve_forever()

if __name__ == "__main__":
    main()
