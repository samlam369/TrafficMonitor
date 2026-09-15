param([string]$VcVarsPath)
$ErrorActionPreference = 'Stop'
$repo = Split-Path $PSScriptRoot -Parent
if (-not $VcVarsPath) {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
    if (Test-Path -LiteralPath $vswhere) {
        $installation = & $vswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
        if ($installation) { $VcVarsPath = Join-Path $installation 'VC/Auxiliary/Build/vcvars64.bat' }
    }
}
if (-not $VcVarsPath -or -not (Test-Path -LiteralPath $VcVarsPath)) {
    throw 'Pass -VcVarsPath pointing to the Visual Studio vcvars64.bat file.'
}
$build = Join-Path ([IO.Path]::GetTempPath()) ('trafficmonitor-layout-' + [guid]::NewGuid())
New-Item -ItemType Directory -Path $build | Out-Null
$source = Join-Path $repo 'tests/taskbar-layout.cpp'
# Fixed batch activates MSVC; quoted arguments keep paths separate from code.
$batch = Join-Path $build 'run.cmd'
@'
@echo off
call "%~1" >nul
if errorlevel 1 exit /b %errorlevel%
cl /nologo /std:c++17 /EHsc /W4 /WX /Od /UNDEBUG "%~2" /Fe:layout-tests.exe /Fo:layout-tests.obj
if errorlevel 1 exit /b %errorlevel%
"%~dp0layout-tests.exe"
exit /b %errorlevel%
'@ | Set-Content -LiteralPath $batch -Encoding ascii
Push-Location $build
try {
    & $batch $VcVarsPath $source
    if ($LASTEXITCODE -ne 0) { throw "Layout tests failed: $LASTEXITCODE" }
} finally {
    Pop-Location
}
Write-Host "Test build: $build"
