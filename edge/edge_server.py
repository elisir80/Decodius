# edge_server.py — voce neurale via Microsoft edge-tts (cloud, gratis).
# Interfaccia:
#   GET  /health   -> 200 "ok"
#   GET  /ready    -> 200 "ready"
#   GET  /voices   -> 200 JSON {voci IT + per-lingua}
#   GET  /shutdown -> spegne
#   POST /tts      -> 200 audio/mpeg (MP3)
#       body JSON: {"text":"...", "voice":"giuseppe"|nome-edge, "lang":"it|en|de|es|fr",
#                   "rate":"+8%", "pitch":"+0Hz", "volume":"+0%"}
#   I campi extra sono OPZIONALI: senza, usa i default (retrocompatibile).
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

# Voci italiane disponibili (alias breve -> voce edge). Giuseppe = caldo/narrativo.
IT_VOICES = {
    "giuseppe": "it-IT-GiuseppeNeural",   # maschile, caldo ed espressivo (default)
    "diego":    "it-IT-DiegoNeural",      # maschile, neutro
    "isabella": "it-IT-IsabellaNeural",   # femminile
    "elsa":     "it-IT-ElsaNeural",       # femminile
}
# Voce maschile per lingua, per rispondere nella lingua dell'interlocutore (QSO DX).
LANG_VOICES = {
    "it": "it-IT-GiuseppeNeural",
    "en": "en-US-GuyNeural",
    "de": "de-DE-ConradNeural",
    "es": "es-ES-AlvaroNeural",
    "fr": "fr-FR-HenriNeural",
    "pt": "pt-BR-AntonioNeural",
}

# Default espressivi: rate moderato (meno robotico del +10% secco), pitch naturale.
VOICE  = "it-IT-GiuseppeNeural"
RATE   = "+8%"
PITCH  = "+0Hz"
VOLUME = "+0%"

def log(*a): print("[edge]", *a, flush=True)

def resolve_voice(voice=None, lang=None):
    """Risolve la voce da alias/lingua/nome-edge completo."""
    if voice:
        v = voice.strip()
        if v.lower() in IT_VOICES:
            return IT_VOICES[v.lower()]
        if "-" in v:            # nome edge completo, es. en-US-GuyNeural
            return v
    if lang:
        return LANG_VOICES.get(lang.strip().lower(), VOICE)
    return VOICE

async def _synth(text, voice, rate, pitch, volume):
    com = edge_tts.Communicate(text, voice, rate=rate, pitch=pitch, volume=volume)
    buf = bytearray()
    async for chunk in com.stream():
        if chunk["type"] == "audio":
            buf += chunk["data"]
    return bytes(buf)

def synth_mp3(text, voice, rate, pitch, volume):
    return asyncio.run(_synth(text, voice, rate, pitch, volume))

from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

class Handler(BaseHTTPRequestHandler):
    def log_message(self, *a): pass
    def _send(self, code, body=b"", ctype="text/plain; charset=utf-8"):
        self.send_response(code); self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(body))); self.end_headers()
        if body: self.wfile.write(body)
    def do_GET(self):
        if self.path == "/health": self._send(200, b"ok")
        elif self.path == "/ready": self._send(200, b"ready")
        elif self.path == "/voices":
            self._send(200, json.dumps({"it": IT_VOICES, "lang": LANG_VOICES,
                                        "default": VOICE}).encode("utf-8"),
                       "application/json; charset=utf-8")
        elif self.path == "/shutdown":
            self._send(200, b"bye"); threading.Thread(target=lambda:(time.sleep(0.2), os._exit(0)), daemon=True).start()
        else: self._send(404, b"not found")
    def do_POST(self):
        if self.path != "/tts": self._send(404, b"not found"); return
        try:
            n = int(self.headers.get("Content-Length", 0))
            req = json.loads(self.rfile.read(n) or b"{}")
            text = (req.get("text") or "").strip()
            if not text: self._send(400, b"empty"); return
            voice  = resolve_voice(req.get("voice"), req.get("lang"))
            rate   = req.get("rate")   or RATE
            pitch  = req.get("pitch")  or PITCH
            volume = req.get("volume") or VOLUME
            self._send(200, synth_mp3(text, voice, rate, pitch, volume), "audio/mpeg")
        except Exception as e:
            log("errore:", "".join(traceback.format_exception(e)))
            self._send(500, ("errore tts: " + str(e)).encode("utf-8"))

def main():
    global VOICE, RATE, PITCH, VOLUME
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=5069)
    ap.add_argument("--speaker", default=VOICE)
    ap.add_argument("--rate", default=RATE)
    ap.add_argument("--pitch", default=PITCH)
    ap.add_argument("--volume", default=VOLUME)
    args = ap.parse_args()
    if args.speaker: VOICE = resolve_voice(args.speaker)
    if args.rate:    RATE   = args.rate     # non azzerare i default con stringhe vuote
    if args.pitch:   PITCH  = args.pitch
    if args.volume:  VOLUME = args.volume
    log("voce:", VOICE, "rate:", RATE, "pitch:", PITCH, "volume:", VOLUME)
    ThreadingHTTPServer(("127.0.0.1", args.port), Handler).serve_forever()

if __name__ == "__main__":
    main()
