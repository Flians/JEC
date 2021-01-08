# Try to find the CaDiCaL librairies
# CADICAL_FOUND - system has openmst lib
# CADICAL_INCLUDE_DIR - the openmst include directory
# CADICAL_LIBRARIES - Libraries needed to use openmst

if (CADICAL_INCLUDE_DIR AND CADICAL_LIBRARY)
		# Already in cache, be silent
		set(CADICAL_FIND_QUIETLY TRUE)
endif (CADICAL_INCLUDE_DIR AND CADICAL_LIBRARY)

find_path(CADICAL_C_INCLUDE_DIR 
        NAMES CaDiCaL/ccadical.h
        PATHS ${PROJECT_SOURCE_DIR}
        PATH_SUFFIXES "" "dependencies" 
        NO_DEFAULT_PATH )
find_path(CADICAL_CXX_INCLUDE_DIR 
        NAMES CaDiCaL/cadical.hpp
        PATHS ${PROJECT_SOURCE_DIR} 
        PATH_SUFFIXES "" "dependencies" 
        NO_DEFAULT_PATH )
find_library(CADICAL_LIBRARY 
        NAMES cadical
        PATHS ${PROJECT_SOURCE_DIR}
        PATH_SUFFIXES "" "lib" "lib64" 
        NO_DEFAULT_PATH )
        
MESSAGE(STATUS "CaDiCaL libs: " ${CADICAL_LIBRARY} )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(cadical DEFAULT_MSG CADICAL_C_INCLUDE_DIR CADICAL_LIBRARY)

mark_as_advanced(CADICAL_C_INCLUDE_DIR CADICAL_CXX_INCLUDE_DIR CADICAL_LIBRARY)
