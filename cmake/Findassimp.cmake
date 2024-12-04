# - Try to find glog
# Once done, this will define
#
#  assimp_FOUND - system has assimp installed
#  assimp_INCLUDE_DIRS - the assimp include directories
#  assimp_LIBRARIES - link these to use assimp
#
# The user may wish to set, in the CMake GUI or otherwise, this variable:
#  assimp_DIR - path to start searching for the module

SET(assimp_DIR
        "${assimp_DIR}"
        CACHE
        PATH
        "Where to start looking for this component.")

UNSET(assimp_INCLUDE_DIR CACHE)
UNSET(assimp_LIBRARY CACHE)

IF (WIN32)
    FIND_PATH(assimp_INCLUDE_DIR
            NAMES
            assimp/BaseImporter.h
            PATHS
            "."
            HINTS
            ${assimp_DIR}
            PATH_SUFFIXES
            include)

    FIND_LIBRARY(assimp_LIBRARY
            NAMES
            assimp-vc142-mt
            PATHS
            "."
            HINTS
            ${assimp_DIR}
            PATH_SUFFIXES
            lib64
            lib)
    
ELSE ()
    FIND_PATH(assimp_INCLUDE_DIR
            NAMES
            assimp/BaseImporter.h
            PATHS
            "/usr"
            "/usr/local"
            HINTS
            ${assimp_DIR}
            PATH_SUFFIXES
            include)

    FIND_LIBRARY(assimp_LIBRARY
            NAMES
            assimp
            PATHS
            "/usr"
            "/usr/lib"
            "/usr/lib64"
            "/usr/local/lib"
            "/usr/local/lib64"
            HINTS
            ${assimp_DIR}
            PATH_SUFFIXES
            lib64
            lib
            x86_64-linux-gnu)
ENDIF ()

MARK_AS_ADVANCED(assimp_INCLUDE_DIR
        assimp_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(assimp
        DEFAULT_MSG
        assimp_INCLUDE_DIR
        assimp_LIBRARY)

IF (assimp_FOUND)
    SET(assimp_INCLUDE_DIRS
            "${assimp_INCLUDE_DIR}")
    # Add any dependencies here
    SET(assimp_LIBRARIES
            "${assimp_LIBRARY}")
    # Add any dependencies here
    MARK_AS_ADVANCED(assimp_DIR)
ENDIF ()
