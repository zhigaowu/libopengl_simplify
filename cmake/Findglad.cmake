# - Try to find glog
# Once done, this will define
#
#  glad_FOUND - system has glad installed
#  glad_INCLUDE_DIRS - the glad include directories
#  glad_SOURCES - link these to use glad
#
# The user may wish to set, in the CMake GUI or otherwise, this variable:
#  glad_DIR - path to start searching for the module

SET(glad_DIR
        "${glad_DIR}"
        CACHE
        PATH
        "Where to start looking for this component.")

UNSET(glad_INCLUDE_DIR CACHE)
UNSET(glad_SOURCE CACHE)

FIND_PATH(glad_INCLUDE_DIR
        NAMES
        glad/glad.h
        PATHS
        "."
        HINTS
        ${glad_DIR}
        PATH_SUFFIXES
        include)

FIND_FILE(glad_SOURCE
        NAMES
        glad.c
        PATHS
        "."
        HINTS
        ${glad_DIR}
        PATH_SUFFIXES
        src)

MARK_AS_ADVANCED(glad_INCLUDE_DIR
        glad_SOURCE)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(glad
        DEFAULT_MSG
        glad_INCLUDE_DIR
        glad_SOURCE)

IF (glad_FOUND)
    SET(glad_INCLUDE_DIRS
            "${glad_INCLUDE_DIR}")
    # Add any dependencies here
    SET(glad_SOURCES
            "${glad_SOURCE}")
    # Add any dependencies here
    MARK_AS_ADVANCED(glad_DIR)
ENDIF ()
