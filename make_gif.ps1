# make_gif.ps1 - run from the repo root (where main.cpp lives)
# usage:  .\make_gif.ps1

$ErrorActionPreference = "Stop"

# --- sanity checks so failures are obvious, not silent -----------------
if (-not (Test-Path "main.cpp")) {
    Write-Error "main.cpp not found. cd into the repo folder first."
}
if (-not (Get-Command ffmpeg -ErrorAction SilentlyContinue)) {
    Write-Error "ffmpeg not on PATH. Run: winget install Gyan.FFmpeg  (then reopen PowerShell)"
}

# --- build -------------------------------------------------------------
Write-Host "building..."
g++ -O2 -std=c++17 main.cpp -o sweep.exe
if ($LASTEXITCODE -ne 0) { Write-Error "compile failed" }

# --- render ------------------------------------------------------------
Write-Host "rendering frames..."
.\sweep.exe
if ($LASTEXITCODE -ne 0) { Write-Error "render failed" }

$n = (Get-ChildItem frames\*.ppm).Count
Write-Host "$n frames rendered"

# --- encode ------------------------------------------------------------
Push-Location frames

Write-Host "building palette..."
ffmpeg -y -loglevel error -framerate 25 -i f%03d.ppm `
       -vf palettegen=stats_mode=diff palette.png

Write-Host "encoding gif..."
ffmpeg -y -loglevel error -framerate 25 -i f%03d.ppm -i palette.png `
       -lavfi paletteuse=dither=bayer:bayer_scale=3 -loop 0 ..\renders\demo.gif

Pop-Location

# --- clean up ----------------------------------------------------------
Remove-Item -Recurse -Force frames

$size = [math]::Round((Get-Item demo.gif).Length / 1MB, 2)
Write-Host "wrote demo.gif ($size MB)"
