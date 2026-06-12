@echo off
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul
set CMAKE=C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe
"%CMAKE%" --build C:\Users\IU8LMC\decodius\build
if errorlevel 1 ( echo ===BUILD_FAILED=== & exit /b 1 )
echo ===BUILD_OK===
