# Find ANTLR
# ANTLR_FOUND - system has ANTLR lib
# ANTLR_BINARY - the ANTLR binary
# ANTLR_INCLUDE_DIR - the ANTLR include directory
# ANTLR_LIBRARIES - Libraries needed to use ANTLR

find_path(ANTLR_INCLUDE_DIR NAMES antlr3.h antlr3/antlr3.h 
        PATHS ${PROJECT_SOURCE_DIR} 
        PATH_SUFFIXES "" "dependencies" 
        NO_DEFAULT_PATH )
find_library(ANTLR_LIBRARIES NAMES antlr3c antlr3c-static libantlr3c
        PATHS ${PROJECT_SOURCE_DIR} 
        PATH_SUFFIXES "" "lib" "lib64" 
        NO_DEFAULT_PATH )

message(STATUS "Found ANTLR libs: ${ANTLR_LIBRARIES}")

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ANTLR DEFAULT_MSG ANTLR_INCLUDE_DIR ANTLR_LIBRARIES)

mark_as_advanced(ANTLR_INCLUDE_DIR ANTLR_LIBRARIES)

