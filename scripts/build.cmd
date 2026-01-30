@echo off
setlocal ENABLEEXTENSIONS

set BUILD_TYPE=%1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Debug

set SCRIPT_DIR=%~dp0
for %%I in ("%SCRIPT_DIR%..") do set LAB4_ROOT=%%~fI

echo ========================================
echo  Building lab4 (Windows)
echo ========================================
echo Build type: %BUILD_TYPE%
echo Project dir: %LAB4_ROOT%
echo.

mkdir "%LAB4_ROOT%\build" 2>nul
cd "%LAB4_ROOT%\build"

cmake -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -G "MinGW Makefiles" ..
mingw32-make

echo.
echo ========================================
echo  Build completed successfully
echo  Executable: %LAB4_ROOT%\build\lab4_main.exe
echo ========================================
pause
