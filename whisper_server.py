# whisper_server.py — STT locale per Decodius (faster-whisper su CPU).
# Cattura il microfono con VAD a energia e trascrive in italiano.
#   GET /health  -> 200 "ok"
#   GET /ready   -> 200 "ready" | 503
#   GET /listen  -> registra finché parli, poi 200 JSON {"text": "..."}
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

SR = 16000                  # faster-whisper lavora a 16 kHz mono
CHUNK = 480                 # 30 ms
START_TIMEOUT = 30.0        # attesa voce (always-on): cicli lunghi, pochi "buchi"
SILENCE_END = 0.35          # silenzio (s) dopo il parlato per chiudere (molto reattivo)
MAX_UTTER = 8.0            # durata massima frase (limita anche il tempo di reazione del barge-in)
RMS_THRESH = 0.012          # soglia voce abbassata: il WO Mic ha livello basso

def log(*a): print("[whisper]", *a, flush=True)

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
    t0 = time.time()
    with sd.InputStream(samplerate=SR, channels=1, dtype="float32", blocksize=CHUNK) as stream:
        while True:
            data, _ = stream.read(CHUNK)
            mono = data[:, 0]
            rms = float(np.sqrt(np.mean(mono * mono)) + 1e-9)
            now = time.time()
            if not started:
                if rms > RMS_THRESH:
                    started = True
                    frames.append(mono.copy())
                elif now - t0 > START_TIMEOUT:
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
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=5068)
    ap.add_argument("--model", default="small")
    args = ap.parse_args()
    threading.Thread(target=load_model, args=(args.model,), daemon=True).start()
    srv = ThreadingHTTPServer(("127.0.0.1", args.port), Handler)
    log(f"in ascolto su http://127.0.0.1:{args.port}")
    srv.serve_forever()

if __name__ == "__main__":
    main()
