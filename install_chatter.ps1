$ErrorActionPreference = "Continue"
$venv = "C:\Users\IU8LMC\decodius\build\chatterenv"
& "C:\Python311\python.exe" -m venv $venv
$vpy = Join-Path $venv "Scripts\python.exe"
& $vpy -m pip install -q --upgrade pip
Write-Output "=== installo torch cu124 (da cache se presente) ==="
& $vpy -m pip install "torch==2.6.0+cu124" "torchaudio==2.6.0+cu124" --index-url https://download.pytorch.org/whl/cu124 2>&1 | Select-Object -Last 4
Write-Output "=== installo chatterbox-tts ==="
& $vpy -m pip install chatterbox-tts 2>&1 | Select-Object -Last 6
Write-Output "=== verifica ==="
& $vpy -c "import torch; print('torch', torch.__version__, 'cuda', torch.cuda.is_available()); from chatterbox.mtl_tts import ChatterboxMultilingualTTS; print('chatterbox OK')" 2>&1 | Select-Object -Last 5
Write-Output "=== DONE ==="
