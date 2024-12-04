cmake_minimum_required(VERSION 3.22)

PROJECT(libopengl_simplify LANGUAGES CXX C)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 设置 CMAKE_BUILD_TYPE
IF ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    SET(CMAKE_BUILD_TYPE "Debug")
ENDIF()

#设置Release版本的编译参数
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

# 编译器参数
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
    IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        ADD_COMPILE_OPTIONS(-g)
    ENDIF()
    IF ("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 9)
        SET(GCC8OL TRUE)
    ENDIF()
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # note: not working for current version because C++17 support is poor
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -inline-forceinline")
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
    IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        ADD_COMPILE_OPTIONS(-g)
    ELSEIF ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        # C99 是允许使用的，但 Clang 依然可能会给出警告，因此屏蔽
        ADD_COMPILE_OPTIONS(-Wno-c99-extensions)
    ENDIF()
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
    IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        ADD_COMPILE_OPTIONS(-g)
    ELSEIF ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        # C99 是允许使用的，但 Clang 依然可能会给出警告，因此屏蔽
        ADD_COMPILE_OPTIONS(-Wno-c99-extensions)
    ENDIF()
ELSE()
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()

# 通用外部库依赖导入函数
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/PrintFlags.cmake)

# glfw3
FIND_PACKAGE(glfw3 REQUIRED)
PRINT_PACKAGE_INFO("glfw3" "${glfw3_INCLUDE_DIRS}" "${glfw3_LIBRARIES}")

# assimp
FIND_PACKAGE(assimp REQUIRED)
PRINT_PACKAGE_INFO("assimp" "${assimp_INCLUDE_DIRS}" "${assimp_LIBRARIES}")

# glog
FIND_PACKAGE(glad REQUIRED)
PRINT_PACKAGE_INFO("glad" "${glad_INCLUDE_DIRS}" "${glad_SOURCES}")

# include 3rd headers
INCLUDE_DIRECTORIES(
    ${glfw3_INCLUDE_DIRS} 
    ${assimp_INCLUDE_DIR}
    ${glad_INCLUDE_DIRS} 
    ${CMAKE_SOURCE_DIR}/3rd/glm/include 
    ${CMAKE_SOURCE_DIR}/3rd/stb/include)

ADD_SUBDIRECTORY(tests)


