# make_pywhisper.ps1 — crea un Python PORTATILE (embeddable 3.12) con faster-whisper
# per lo STT di Decodius, sullo stesso modello di make_pyedge.ps1. Bundla anche il
# modello "small" così l'app installata ha la voce->testo OVUNQUE, offline, senza
# Python di sistema. Output: build\pywhisper\  (pythonw.exe + Lib + whisper_server.py + model\)
$ErrorActionPreference = "Stop"
$root = "C:\Users\IU8LMC\decodius"
$base = "$root\build\pywhisper"
if (Test-Path $base) { Remove-Item $base -Recurse -Force }
New-Item -ItemType Directory -Force -Path $base | Out-Null

$zip = "$env:TEMP\pyembed_whisper.zip"
Write-Output "scarico python embeddable 3.12..."
Invoke-WebRequest "https://www.python.org/ftp/python/3.12.8/python-3.12.8-embed-amd64.zip" -OutFile $zip
Expand-Archive -Path $zip -DestinationPath $base -Force
Write-Output "pythonw presente: $(Test-Path "$base\pythonw.exe")"

# abilita site-packages (decommenta 'import site' nel ._pth)
$pth = Get-ChildItem "$base\python*._pth" | Select-Object -First 1
(Get-Content $pth.FullName) -replace '#\s*import site', 'import site' | Set-Content $pth.FullName

# get-pip
Invoke-WebRequest "https://bootstrap.pypa.io/get-pip.py" -OutFile "$base\get-pip.py"
& "$base\python.exe" "$base\get-pip.py" --no-warn-script-location 2>&1 | Select-Object -Last 2

Write-Output "installo numpy + sounddevice + faster-whisper (wheel precompilate)..."
& "$base\python.exe" -m pip install --no-warn-script-location numpy sounddevice faster-whisper 2>&1 | Select-Object -Last 5

Write-Output "=== verifica import ==="
& "$base\python.exe" -c "import numpy, sounddevice, faster_whisper; print('import OK', faster_whisper.__version__)"

Write-Output "scarico il modello 'small' (Systran/faster-whisper-small) nel bundle..."
& "$base\python.exe" -c "from huggingface_hub import snapshot_download; p=snapshot_download('Systran/faster-whisper-small', local_dir=r'$base\model'); print('modello in', p)"

# copia il server STT accanto al bundle
Copy-Item "$root\whisper_server.py" "$base\whisper_server.py" -Force

# pulizia: cache pip + __pycache__ per ridurre la dimensione
& "$base\python.exe" -m pip cache purge 2>&1 | Out-Null
Get-ChildItem $base -Recurse -Directory -Filter "__pycache__" -ErrorAction SilentlyContinue | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue

Write-Output "DIM pywhisper MB: $([math]::Round((Get-ChildItem $base -Recurse -File|Measure-Object Length -Sum).Sum/1MB,1))"
Write-Output "=== PYWHISPER DONE ==="
