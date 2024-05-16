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

cmake -S . -B cmake.build -G "$PLATFORM_TYPE Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -Dglfw3_DIR=3rd/glfw-3.4 -Dglad_DIR=3rd/glad-4.6 -DCMAKE_INSTALL_PREFIX=install
