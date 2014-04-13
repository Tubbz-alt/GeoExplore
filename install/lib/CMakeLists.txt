#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#
#    Purpose:  Build script for the GeoExplore library.
#

#  Define Required CMake Version
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

#  Allow C++ 11x
SET(CMAKE_CXX_FLAGS "-std=c++0x")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib )

#-----------------------------------------#
#-     Define Required Header Files      -#
#-----------------------------------------#

#   Core Module
set( GEOEXPLORE_CORE_HEADERS
    ../src/core/Enumerations.hpp
)


#   Coordinate Module
set( GEOEXPLORE_COORDINATE_HEADERS
    ../src/coordinate/CoordinateBase.hpp
)

#  Combine modules
set( GEOEXPLORE_HEADERS
    ${GEOEXPLORE_CORE_HEADERS}
    ${GEOEXPLORE_COORDINATE_HEADERS}
)


#----------------------------------------#
#-     Define Required Source Files     -#
#----------------------------------------#

#    Coordinate Module
set( GEOEXPLORE_COORDINATE_SOURCES
    ../src/coordinate/CoordinateBase.cpp
)


#   Combine Modules
set( GEOEXPLORE_SOURCES
    ${GEOEXPLORE_COORDINATE_SOURCES}
)

#-----------------------------------------#
#-      Generate the Shared Object       -#
#-----------------------------------------#
include_directories( ${PROJECT_BINARY_DIR}/include/ )

add_library( GeoExplore SHARED
             ${GEOEXPLORE_SOURCES}
             ${GEOEXPLORE_HEADERS}
)


