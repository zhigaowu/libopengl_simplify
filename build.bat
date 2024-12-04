@echo off

SET BUILD_TYPE=Debug
if "%~1" neq "" ( 
    SET BUILD_TYPE=%~1
)

cmake -S . -B build -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -Dglfw3_DIR=3rd/glfw-3.4 -Dglad_DIR=3rd/glad-4.6 -Dassimp_DIR=3rd/assimp-5.4.3 -DCMAKE_INSTALL_PREFIX=install
