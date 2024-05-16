# - Try to find glog
# Once done, this will define
#
#  glfw3_FOUND - system has glfw3 installed
#  glfw3_INCLUDE_DIRS - the glfw3 include directories
#  glfw3_LIBRARIES - link these to use glfw3
#
# The user may wish to set, in the CMake GUI or otherwise, this variable:
#  glfw3_DIR - path to start searching for the module

SET(glfw3_DIR
        "${glfw3_DIR}"
        CACHE
        PATH
        "Where to start looking for this component.")

UNSET(glfw3_INCLUDE_DIR CACHE)
UNSET(glfw3_LIBRARY CACHE)

IF (WIN32)
    FIND_PATH(glfw3_INCLUDE_DIR
            NAMES
            GLFW/glfw3.h
            PATHS
            "."
            HINTS
            ${glfw3_DIR}
            PATH_SUFFIXES
            include)

    FIND_LIBRARY(glfw3_LIBRARY
            NAMES
            glfw3
            PATHS
            "."
            HINTS
            ${glfw3_DIR}
            PATH_SUFFIXES
            lib64
            lib)
    
ELSE ()
    FIND_PATH(glfw3_INCLUDE_DIR
            NAMES
            GLFW/glfw3.h
            PATHS
            "/usr"
            "/usr/local"
            HINTS
            ${glfw3_DIR}
            PATH_SUFFIXES
            include)

    FIND_LIBRARY(glfw3_LIBRARY
            NAMES
            glfw3
            PATHS
            "/usr"
            "/usr/lib"
            "/usr/lib64"
            "/usr/local/lib"
            "/usr/local/lib64"
            HINTS
            ${glfw3_DIR}
            PATH_SUFFIXES
            lib64
            lib
            x86_64-linux-gnu)
ENDIF ()

MARK_AS_ADVANCED(glfw3_INCLUDE_DIR
        glfw3_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(glfw3
        DEFAULT_MSG
        glfw3_INCLUDE_DIR
        glfw3_LIBRARY)

IF (glfw3_FOUND)
    SET(glfw3_INCLUDE_DIRS
            "${glfw3_INCLUDE_DIR}")
    # Add any dependencies here
    SET(glfw3_LIBRARIES
            "${glfw3_LIBRARY}")
    # Add any dependencies here
    MARK_AS_ADVANCED(glfw3_DIR)
ENDIF ()
