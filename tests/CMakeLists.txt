cmake_minimum_required(VERSION 3.22)

PROJECT(tests VERSION 1.0.0 LANGUAGES CXX C)

# 打印项目信息
MESSAGE(STATUS "===== ${PROJECT_NAME} ====")
MESSAGE(STATUS "--------------------------------------------------")
MESSAGE(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# 打印编译标志
PRINT_CPLUS_FLAGS()

# 打印空行，结束项目信息
MESSAGE(STATUS "--------------------------------------------------")

# 将所有 src/*.cpp 文件列出来
FILE(GLOB SIMPLIFY_SOURCES ${CMAKE_SOURCE_DIR}/src/glfw/*.cpp ${CMAKE_SOURCE_DIR}/src/core/*.cpp)
FILE(GLOB MAIN_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 所有的源文件+头文件需要在这个地方添加
ADD_EXECUTABLE(tests ${glad_SOURCES} ${SIMPLIFY_SOURCES} ${MAIN_SOURCES})

IF (MSVC)
    # Tell MSVC to use main instead of WinMain
    SET_TARGET_PROPERTIES(${GUI_ONLY_BINARIES} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
ELSEIF (CMAKE_C_SIMULATE_ID STREQUAL "MSVC")
    # Tell Clang using MS CRT to use main instead of WinMain
    SET_TARGET_PROPERTIES(${GUI_ONLY_BINARIES} PROPERTIES
                          LINK_FLAGS "-Wl,/entry:mainCRTStartup")
ENDIF()

TARGET_INCLUDE_DIRECTORIES(tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

TARGET_LINK_LIBRARIES(tests PRIVATE ${glfw3_LIBRARIES})

IF (NOT MSVC)
    TARGET_LINK_LIBRARIES(tests PRIVATE pthread)
ENDIF()

install(TARGETS tests
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/install COMPONENT tests)

