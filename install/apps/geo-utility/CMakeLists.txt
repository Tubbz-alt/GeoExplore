#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    8/3/2014
#    
#    Purpose:  Build script for the Geo-Utility
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
include_directories( ${Boost_INCLUDE_DIR} )

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
set( GEOUTILITY_HEADERS
    ../../../src/cpp/apps/geo-utility/Globals.hpp
    ../../../src/cpp/apps/geo-utility/Options.hpp
    ../../../src/cpp/apps/geo-utility/Utilities.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEOUTILITY_SOURCES
    ../../../src/cpp/apps/geo-utility/geo-utility.cpp
    ../../../src/cpp/apps/geo-utility/Options.cpp
    ../../../src/cpp/apps/geo-utility/Utilities.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories( "${PROJECT_BINARY_DIR}/../../include" )

add_executable( geo-utility
                ${GEOUTILITY_SOURCES}
                ${GEOUTILITY_HEADERS}
)

target_link_libraries( geo-utility
                ${GeoExplore_LIBRARY}
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
                ${OpenCV_LIBS}
)

