# - Try to find glog
# Once done, this will define
#
#  FreeType_FOUND - system has FreeType installed
#  FreeType_INCLUDE_DIRS - the FreeType include directories
#  FreeType_LIBRARIES - link these to use FreeType
#
# The user may wish to set, in the CMake GUI or otherwise, this variable:
#  FreeType_DIR - path to start searching for the module

SET(FreeType_DIR
        "${FreeType_DIR}"
        CACHE
        PATH
        "Where to start looking for this component.")

UNSET(FreeType_INCLUDE_DIR CACHE)
UNSET(FreeType_LIBRARY CACHE)

IF (WIN32)
    FIND_PATH(FreeType_INCLUDE_DIR
            NAMES
            ft2build.h
            PATHS
            "."
            HINTS
            ${FreeType_DIR}
            PATH_SUFFIXES
            include)

    FIND_LIBRARY(FreeType_LIBRARY
            NAMES
            freetype
            PATHS
            "."
            HINTS
            ${FreeType_DIR}
            PATH_SUFFIXES
            lib64
            lib)
    
ELSE ()
    FIND_PATH(FreeType_INCLUDE_DIR
            NAMES
            ft2build.h
            PATHS
            "/usr"
            "/usr/local"
            HINTS
            ${FreeType_DIR}
            PATH_SUFFIXES
            include)

    FIND_LIBRARY(FreeType_LIBRARY
            NAMES
            freetype
            PATHS
            "/usr"
            "/usr/lib"
            "/usr/lib64"
            "/usr/local/lib"
            "/usr/local/lib64"
            HINTS
            ${FreeType_DIR}
            PATH_SUFFIXES
            lib64
            lib
            x86_64-linux-gnu)
ENDIF ()

MARK_AS_ADVANCED(FreeType_INCLUDE_DIR
        FreeType_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FreeType
        DEFAULT_MSG
        FreeType_INCLUDE_DIR
        FreeType_LIBRARY)

IF (FreeType_FOUND)
    SET(FreeType_INCLUDE_DIRS
            "${FreeType_INCLUDE_DIR}")
    # Add any dependencies here
    SET(FreeType_LIBRARIES
            "${FreeType_LIBRARY}")
    # Add any dependencies here
    MARK_AS_ADVANCED(FreeType_DIR)
ENDIF ()
