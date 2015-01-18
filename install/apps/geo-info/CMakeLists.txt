#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/17/2014
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
include_directories( ${Boost_INCLUDE_DIRS} )

#--------------------------------#
#-     Find OpenCV Library      -#
#--------------------------------#
find_package( OpenCV REQUIRED )

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
set( GEOINFO_HEADERS
    ../../../src/cpp/apps/geo-info/Options.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEOINFO_SOURCES
    ../../../src/cpp/apps/geo-info/main.cpp
    ../../../src/cpp/apps/geo-info/Options.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories( "${PROJECT_BINARY_DIR}/../../include" )

add_executable( geo-info 
                ${GEOINFO_SOURCES}
                ${GEOINFO_HEADERS}
)

target_link_libraries( geo-info
                ${GeoExplore_LIBRARY}
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
                ${OpenCV_LIBS}
)

