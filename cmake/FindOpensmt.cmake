# Try to find the openmst librairies
# OPENSMT_FOUND - system has openmst lib
# OPENSMT_INCLUDE_DIR - the openmst include directory
# OPENSMT_LIBRARIES - Libraries needed to use openmst

if (OPENSMT_INCLUDE_DIR AND OPENSMT_LIBRARY)
		# Already in cache, be silent
		set(Opensmt_FIND_QUIETLY TRUE)
endif (OPENSMT_INCLUDE_DIR AND OPENSMT_LIBRARY)

find_path(OPENSMT_INCLUDE_DIR 
        NAMES "opensmt/opensmt2.h"
        PATHS ${PROJECT_SOURCE_DIR}
        PATH_SUFFIXES "" "dependencies" 
        NO_DEFAULT_PATH )
find_library(OPENSMT_LIBRARY 
        NAMES opensmt2
        PATHS ${PROJECT_SOURCE_DIR}
        PATH_SUFFIXES "" "lib" "lib64" 
        NO_DEFAULT_PATH )
        
MESSAGE(STATUS "opensmt libs: " ${OPENSMT_LIBRARY} )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(opensmt DEFAULT_MSG OPENSMT_INCLUDE_DIR OPENSMT_LIBRARY)

mark_as_advanced(OPENSMT_INCLUDE_DIR OPENSMT_LIBRARY)
