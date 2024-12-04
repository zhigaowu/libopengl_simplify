#! /bin/bash

BUILD_TYPE=Debug
if [ $# -gt 0 ]; 
then
    BUILD_TYPE=$1
fi

PLATFORM_TYPE="Unix"
if [ "$(uname)" != "Linux" ]; 
then
    PLATFORM_TYPE="MinGW"
fi

cmake -S . -B build -G "$PLATFORM_TYPE Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -Dglfw3_DIR=3rd/glfw-3.4 -Dglad_DIR=3rd/glad-4.6 -Dassimp_DIR=3rd/assimp-5.4.3 -DCMAKE_INSTALL_PREFIX=install
