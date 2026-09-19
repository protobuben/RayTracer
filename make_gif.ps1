# make_gif.ps1 - run from the repo root (where main.cpp lives)
# usage:  .\make_gif.ps1            (uses every logical core)
#         .\make_gif.ps1 -Workers 4

param([int]$Workers = [int]$env:NUMBER_OF_PROCESSORS)

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
Remove-Item -Recurse -Force frames -ErrorAction SilentlyContinue
New-Item -ItemType Directory -Force -Path frames, logs | Out-Null

Write-Host "rendering frames on $Workers workers..."
$t0 = Get-Date

$procs = @()
for ($k = 0; $k -lt $Workers; $k++) {
    $procs += Start-Process -FilePath ".\sweep.exe" `
                            -ArgumentList $k, $Workers `
                            -NoNewWindow -PassThru `
                            -RedirectStandardError "logs\w$k.log"
}
$procs | Wait-Process

$failed = @($procs | Where-Object { $_.ExitCode -ne 0 })
if ($failed.Count -gt 0) {
    Write-Error "$($failed.Count) worker(s) failed - see logs\w*.log"
}

$elapsed = [math]::Round(((Get-Date) - $t0).TotalSeconds, 1)
$frames  = (Get-ChildItem frames\*.ppm).Count
Write-Host "$frames frames rendered in $elapsed s"

# --- ping-pong ---------------------------------------------------------
# done here, once, after every worker has joined
for ($i = $frames - 2; $i -ge 1; $i--) {
    $j = 2 * $frames - 2 - $i
    Copy-Item ("frames\f{0:d3}.ppm" -f $i) ("frames\f{0:d3}.ppm" -f $j) -Force
}
$n = (Get-ChildItem frames\*.ppm).Count
Write-Host "mirrored to $n frames"

# every frame must have the same dimensions or the filter graph blows up with
# "Internal bug, should not have happened" instead of naming the odd frame
$dims = Get-ChildItem frames\*.ppm | ForEach-Object {
    $hdr = (Get-Content $_.FullName -TotalCount 2)[1]
    [pscustomobject]@{ File = $_.Name; Dim = $hdr.Trim() }
}
$bad = $dims | Where-Object { $_.Dim -ne $dims[0].Dim }
if ($bad) {
    $bad | ForEach-Object { Write-Host "  $($_.File): $($_.Dim)  (expected $($dims[0].Dim))" }
    Write-Error "frame size is not constant across the sequence"
}

# --- encode ------------------------------------------------------------
$outDir = Join-Path $PWD "renders"
$out    = Join-Path $outDir "demo.gif"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

Push-Location frames

Write-Host "building palette..."
ffmpeg -y -loglevel error -framerate 25 -i f%03d.ppm `
       -vf palettegen=stats_mode=diff palette.png
if ($LASTEXITCODE -ne 0) { Pop-Location; Write-Error "palettegen failed" }

Write-Host "encoding gif..."
ffmpeg -y -loglevel error -framerate 25 -i f%03d.ppm -i palette.png `
       -lavfi paletteuse=dither=bayer:bayer_scale=3 -loop 0 $out
if ($LASTEXITCODE -ne 0) { Pop-Location; Write-Error "gif encode failed (frames kept for inspection)" }

Pop-Location

# --- clean up ----------------------------------------------------------
Remove-Item -Recurse -Force frames

$size = [math]::Round((Get-Item $out).Length / 1MB, 2)
Write-Host "wrote $out ($size MB)"