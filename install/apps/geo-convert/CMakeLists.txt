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

#-----------------------------------#
#-     Find GeoExplore Library     -#
#-----------------------------------#
find_library( GeoExplore_LIBRARY
                REQUIRED
                NAMES
                    GeoExplore
                HINTS
                    ${PROJECT_BINARY_DIR}/../../lib
)

#-------------------#
#-    Find Boost   -#
#-------------------#
find_package( Boost 
                COMPONENTS
                    thread
                    system
                    filesystem
                    regex
                REQUIRED
)

#-----------------------------------#
#-     Find C++ Thread Library     -#
#-----------------------------------#
find_package( Threads )

#------------------------------#
#-     Find GDAL Library      -#
#------------------------------#
find_package( GDAL REQUIRED )

#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( GEOCONVERT_HEADERS
    ../../../src/cpp/apps/geo-convert/Options.hpp
    ../../../src/cpp/apps/geo-convert/CoordinateConversion.hpp
    ../../../src/cpp/apps/geo-convert/Utilities.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEOCONVERT_SOURCES
    ../../../src/cpp/apps/geo-convert/main.cpp
    ../../../src/cpp/apps/geo-convert/Options.cpp
    ../../../src/cpp/apps/geo-convert/CoordinateConversion.cpp
    ../../../src/cpp/apps/geo-convert/Utilities.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories( "${PROJECT_BINARY_DIR}/../../include" )

add_executable( geo-convert 
                ${GEOCONVERT_SOURCES}
                ${GEOCONVERT_HEADERS}
)

target_link_libraries( geo-convert
                ${GeoExplore_LIBRARY}
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
)

