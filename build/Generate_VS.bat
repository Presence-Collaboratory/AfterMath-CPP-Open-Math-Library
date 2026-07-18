@echo off
setlocal

echo Select Visual Studio version:
echo 1. Visual Studio 2019
echo 2. Visual Studio 2022
choice /c 12 /m "Your choice: "

if errorlevel 2 (
    set GENERATOR=Visual Studio 17 2022
) else (
    set GENERATOR=Visual Studio 16 2019
)

set SOURCE_DIR=..
set BUILD_DIR=generated

echo.
echo Generating %GENERATOR% solution...
cmake -G "%GENERATOR%" -A x64 -B %BUILD_DIR% -S %SOURCE_DIR%

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Generation failed.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Solution generated: %BUILD_DIR%\AfterMath.sln
pause
