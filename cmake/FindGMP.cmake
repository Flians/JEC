# Try to find the GMP librairies
# GMP_FOUND - system has GMP lib
# GMP_C_INCLUDE_DIR, GMP_CXX_INCLUDE_DIR - the GMP include directory
# GMP_LIBRARIES - Libraries needed to use GMP

if (GMP_INCLUDE_DIR AND GMP_LIBRARIES)
		# Already in cache, be silent
		set(GMP_FIND_QUIETLY TRUE)
endif (GMP_INCLUDE_DIR AND GMP_LIBRARIES)

find_path(GMP_INCLUDE_DIR 
		NAMES gmp.h gmpxx.h
		PATHS ${PROJECT_SOURCE_DIR} 
		PATH_SUFFIXES "" "dependencies" "dependencies/gmp"
		NO_DEFAULT_PATH )

MESSAGE(STATUS "GMP include: " ${GMP_INCLUDE_DIR} )

find_library(GMP_LIBRARIES 
		NAMES gmp libgmp
		PATHS ${PROJECT_SOURCE_DIR}
		PATH_SUFFIXES "" "lib" "lib64" 
		NO_DEFAULT_PATH )

find_library(GMPXX_LIBRARIES 
		NAMES gmpxx libgmpxx
		PATHS ${PROJECT_SOURCE_DIR}
		PATH_SUFFIXES "" "lib" "lib64" 
		NO_DEFAULT_PATH )

MESSAGE(STATUS "GMP libs: " ${GMP_LIBRARIES} " " ${GMPXX_LIBRARIES} )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMP DEFAULT_MSG GMP_INCLUDE_DIR GMP_LIBRARIES)

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARIES GMPXX_LIBRARIES)
