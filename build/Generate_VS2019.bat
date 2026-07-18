@echo off
setlocal

set SOURCE_DIR=..
set BUILD_DIR=generated

echo ============================================
echo Generating Visual Studio 2019 solution...
echo Source: %SOURCE_DIR%
echo Build:  %BUILD_DIR%
echo ============================================

cmake -G "Visual Studio 16 2019" -A x64 -B %BUILD_DIR% -S %SOURCE_DIR%

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: CMake generation failed!
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Solution generated successfully: %BUILD_DIR%\AfterMath.sln
pause
