@echo off
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul
set CMAKE=C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe
set NINJA=C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe
cd /d C:\Users\IU8LMC\decodius
rmdir /s /q build 2>nul
"%CMAKE%" -G Ninja -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="%NINJA%" -DCMAKE_PREFIX_PATH="C:/Qt/6.8.0/msvc2022_64"
if errorlevel 1 ( echo ===CONFIG_FAILED=== & exit /b 1 )
echo ===CONFIG_OK===
"%CMAKE%" --build build
if errorlevel 1 ( echo ===BUILD_FAILED=== & exit /b 1 )
echo ===BUILD_OK===
