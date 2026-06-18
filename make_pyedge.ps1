$ErrorActionPreference="Stop"
$base=$env:PYEDGE_DIR
if ([string]::IsNullOrWhiteSpace($base)) {
    $base="C:\Users\IU8LMC\decodius\build\pyedge"
}
if (Test-Path $base) { Remove-Item $base -Recurse -Force }
New-Item -ItemType Directory -Force -Path $base | Out-Null
$zip="$env:TEMP\pyembed.zip"
Write-Output "scarico python embeddable 3.12..."
Invoke-WebRequest "https://www.python.org/ftp/python/3.12.8/python-3.12.8-embed-amd64.zip" -OutFile $zip
Expand-Archive -Path $zip -DestinationPath $base -Force
Write-Output "pythonw presente: $(Test-Path "$base\pythonw.exe")"
# abilita site-packages (decommenta 'import site' nel ._pth)
$pth = Get-ChildItem "$base\python*._pth" | Select-Object -First 1
(Get-Content $pth.FullName) -replace '#\s*import site','import site' | Set-Content $pth.FullName
# get-pip
Invoke-WebRequest "https://bootstrap.pypa.io/get-pip.py" -OutFile "$base\get-pip.py"
& "$base\python.exe" "$base\get-pip.py" --no-warn-script-location 2>&1 | Select-Object -Last 2
& "$base\python.exe" -m pip install edge-tts --no-warn-script-location 2>&1 | Select-Object -Last 3
Write-Output "=== verifica edge-tts ==="
& "$base\python.exe" -c "import edge_tts; print('edge-tts OK')"
Write-Output "DIM pyedge MB: $([math]::Round((Get-ChildItem $base -Recurse -File|Measure-Object Length -Sum).Sum/1MB,1))"
Write-Output "=== PYEDGE DONE ==="
