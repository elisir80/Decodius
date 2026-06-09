# edge_server.py — voce maschile neurale via Microsoft edge-tts (cloud, gratis).
# Stessa interfaccia degli altri server vocali di Decodius:
#   GET  /health   -> 200 "ok"
#   GET  /ready    -> 200 "ready"
#   GET  /shutdown -> spegne
#   POST /tts      -> 200 audio/mpeg (MP3)   body JSON {"text": "..."}
import os, sys, json, asyncio, threading, time, argparse, traceback

# Sotto pythonw.exe (avvio persistente senza console) stdout/stderr sono None.
if sys.stdout is None:
    sys.stdout = open(os.devnull, "w", encoding="utf-8")
if sys.stderr is None:
    sys.stderr = open(os.devnull, "w", encoding="utf-8")
try:
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    sys.stderr.reconfigure(encoding="utf-8", errors="replace")
except Exception:
    pass

import edge_tts

VOICE = "it-IT-DiegoNeural"
RATE = "+10%"   # velocità del parlato (più alto = più svelto)

def log(*a): print("[edge]", *a, flush=True)

async def _synth(text):
    com = edge_tts.Communicate(text, VOICE, rate=RATE)
    buf = bytearray()
    async for chunk in com.stream():
        if chunk["type"] == "audio":
            buf += chunk["data"]
    return bytes(buf)

def synth_mp3(text):
    return asyncio.run(_synth(text))

from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

class Handler(BaseHTTPRequestHandler):
    def log_message(self, *a): pass
    def _send(self, code, body=b"", ctype="text/plain; charset=utf-8"):
        self.send_response(code); self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(body))); self.end_headers()
        if body: self.wfile.write(body)
    def do_GET(self):
        if self.path == "/health": self._send(200, b"ok")
        elif self.path == "/ready": self._send(200, b"ready")   # nessun modello da caricare
        elif self.path == "/shutdown":
            self._send(200, b"bye"); threading.Thread(target=lambda:(time.sleep(0.2), os._exit(0)), daemon=True).start()
        else: self._send(404, b"not found")
    def do_POST(self):
        if self.path != "/tts": self._send(404, b"not found"); return
        try:
            n = int(self.headers.get("Content-Length", 0))
            text = (json.loads(self.rfile.read(n) or b"{}").get("text") or "").strip()
            if not text: self._send(400, b"empty"); return
            self._send(200, synth_mp3(text), "audio/mpeg")
        except Exception as e:
            log("errore:", "".join(traceback.format_exception(e)))
            self._send(500, ("errore tts: " + str(e)).encode("utf-8"))

def main():
    global VOICE, RATE
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=5069)
    ap.add_argument("--speaker", default="it-IT-DiegoNeural")
    ap.add_argument("--rate", default="+10%")
    args = ap.parse_args()
    VOICE = args.speaker
    RATE = args.rate
    log("voce:", VOICE, "rate:", RATE)
    ThreadingHTTPServer(("127.0.0.1", args.port), Handler).serve_forever()

if __name__ == "__main__":
    main()
