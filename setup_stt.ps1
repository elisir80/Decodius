# ============================================================================
#  Decodius - Attivazione dei comandi vocali (STT: Python portatile + faster-whisper)
#  Scarica a richiesta un Python embeddable 3.12 con faster-whisper e il modello
#  "small" in <cartella app>\pywhisper, cosi' Decodius capisce i comandi a voce,
#  offline, senza Python di sistema. ~700 MB di download la prima volta (Internet).
#  Stesso schema di make_pywhisper.ps1, ma eseguibile sull'app installata.
# ============================================================================
$ErrorActionPreference = "Stop"

# --- Auto-elevazione: serve scrivere nella cartella d'installazione ----------
$me = [Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()
if (-not $me.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Start-Process powershell -Verb RunAs -ArgumentList @(
        "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", "`"$PSCommandPath`"")
    exit
}

function Info($m){ Write-Host "  $m" -ForegroundColor Cyan }
function Ok($m){   Write-Host "  [OK] $m" -ForegroundColor Green }
function Warn($m){ Write-Host "  [!] $m" -ForegroundColor Yellow }
function Err($m){  Write-Host "  [X] $m" -ForegroundColor Red }

Write-Host ""
Write-Host "  =================================================" -ForegroundColor White
Write-Host "   DECODIUS - Attivazione comandi vocali (STT)" -ForegroundColor White
Write-Host "  =================================================" -ForegroundColor White
Write-Host ""

$base = Join-Path $PSScriptRoot "pywhisper"

# Gia' installato e funzionante?
if ((Test-Path "$base\pythonw.exe") -and (Test-Path "$base\model\model.bin")) {
    Ok "I comandi vocali risultano gia' attivi in:"
    Info "$base"
    $ans = Read-Host "  Reinstallare da zero? (s/N)"
    if ($ans -notmatch '^[sS]') {
        Write-Host ""; Ok "Niente da fare. Avvia Decodius e usa il microfono."
        Read-Host "  Premi INVIO per chiudere"; exit 0
    }
    Remove-Item $base -Recurse -Force
}

Info "Preparo un Python portatile per la voce (non tocca il tuo sistema)."
Info "Scarico ~700 MB: la prima attivazione puo' richiedere qualche minuto."
Write-Host ""

try {
    New-Item -ItemType Directory -Force -Path $base | Out-Null

    # 1) Python embeddable 3.12
    Info "1/5  Scarico Python embeddable 3.12..."
    $zip = "$env:TEMP\pyembed_whisper.zip"
    Invoke-WebRequest "https://www.python.org/ftp/python/3.12.8/python-3.12.8-embed-amd64.zip" -OutFile $zip -UseBasicParsing
    Expand-Archive -Path $zip -DestinationPath $base -Force
    Remove-Item $zip -Force -ErrorAction SilentlyContinue
    if (-not (Test-Path "$base\pythonw.exe")) { throw "Python portatile non estratto." }

    # abilita site-packages (decommenta 'import site' nel ._pth)
    $pth = Get-ChildItem "$base\python*._pth" | Select-Object -First 1
    (Get-Content $pth.FullName) -replace '#\s*import site', 'import site' | Set-Content $pth.FullName

    # 2) pip
    Info "2/5  Installo pip..."
    Invoke-WebRequest "https://bootstrap.pypa.io/get-pip.py" -OutFile "$base\get-pip.py" -UseBasicParsing
    & "$base\python.exe" "$base\get-pip.py" --no-warn-script-location 2>&1 | Select-Object -Last 1

    # 3) librerie STT (wheel precompilate)
    Info "3/5  Installo faster-whisper + sounddevice + numpy..."
    & "$base\python.exe" -m pip install --no-warn-script-location numpy sounddevice faster-whisper 2>&1 | Select-Object -Last 3
    & "$base\python.exe" -c "import numpy, sounddevice, faster_whisper"
    if ($LASTEXITCODE -ne 0) { throw "Import delle librerie STT non riuscito." }

    # 4) modello vocale "small"
    Info "4/5  Scarico il modello vocale 'small' (~480 MB)..."
    & "$base\python.exe" -c "from huggingface_hub import snapshot_download; snapshot_download('Systran/faster-whisper-small', local_dir=r'$base\model')"
    if (-not (Test-Path "$base\model\model.bin")) { throw "Modello vocale non scaricato." }

    # 5) server STT + pulizia
    Info "5/5  Finalizzo..."
    Copy-Item (Join-Path $PSScriptRoot "whisper_server.py") "$base\whisper_server.py" -Force
    & "$base\python.exe" -m pip cache purge 2>&1 | Out-Null
    Get-ChildItem $base -Recurse -Directory -Filter "__pycache__" -ErrorAction SilentlyContinue |
        Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
}
catch {
    Err "Attivazione non riuscita: $($_.Exception.Message)"
    Err "Controlla la connessione a Internet e riprova questo setup."
    Read-Host "`n  Premi INVIO per chiudere"; exit 1
}

$mb = [math]::Round((Get-ChildItem $base -Recurse -File | Measure-Object Length -Sum).Sum/1MB, 0)
Write-Host ""
Write-Host "  =================================================" -ForegroundColor Green
Write-Host "   FATTO! Comandi vocali attivi ($mb MB)." -ForegroundColor Green
Write-Host "   Avvia (o riavvia) Decodius e usa il microfono." -ForegroundColor Green
Write-Host "  =================================================" -ForegroundColor Green
Write-Host ""
Read-Host "  Premi INVIO per chiudere"
