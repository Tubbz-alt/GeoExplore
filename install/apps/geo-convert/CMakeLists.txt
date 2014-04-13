#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#    
#    Purpose:  Build script for the Geo-Convert utility
#
#  Define Required CMake Version
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

#  Allow C++ 11x
SET(CMAKE_CXX_FLAGS "-std=c++0x")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/../../lib )


#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( GEOCONVERT_HEADERS
    ../../../src/apps/geo-convert/Options.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEOCONVERT_SOURCES
    ../../../src/apps/geo-convert/main.cpp
    ../../../src/apps/geo-convert/Options.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories( "${PROJECT_BINARY_DIR}/../../include" )

add_executable( geo-convert 
                ${GEOCONVERT_SOURCES}
                ${GEOCONVERT_HEADERS}
)

