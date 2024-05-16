@echo off

SET BUILD_TYPE=Debug
if "%~1" neq "" ( 
    SET BUILD_TYPE=%~1
)

cmake -S . -B cmake.build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -Dglfw3_DIR=3rd/glfw-3.4 -Dglad_DIR=3rd/glad-4.6 -DCMAKE_INSTALL_PREFIX=install
