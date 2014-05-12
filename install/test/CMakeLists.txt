#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#
#    Purpose:  Build script for GeoExplore unit tests
#

#  Define minimum required cmake
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

#  Allow C++ 11x
SET( CMAKE_CXX_FLAGS "-std=c++0x")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

#-----------------------------------#
#-     Find GeoExplore Library     -#
#-----------------------------------#
find_library( GeoExplore_LIBRARY
                REQUIRED
                NAMES
                    GeoExplore
                HINTS
                    ${PROJECT_BINARY_DIR}/../lib
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

#--------------------#
#-     Find GDAL    -#
#--------------------#
find_package( GDAL REQUIRED )

#----------------------------------------#
#-     Define Required Header Files     -#
#----------------------------------------#
set( UNIT_TEST_HEADERS
    ../../tests/cpp/googletest/include/gtest/gtest.h
)

#---------------------------------------#
#-    Define Required Source Files     -#
#---------------------------------------#
set( UNIT_TEST_SOURCES
    ../../tests/cpp/googletest/src/gtest_main.cc
    ../../tests/cpp/googletest/src/gtest-all.cc
    ../../tests/cpp/coordinate/TEST_CoordinateBase.cpp
    ../../tests/cpp/coordinate/TEST_CoordinateConversion.cpp
    ../../tests/cpp/coordinate/TEST_CoordinateUTM.cpp
    ../../tests/cpp/image/TEST_ChannelType.cpp
    ../../tests/cpp/image/TEST_Image.cpp
    ../../tests/cpp/image/TEST_MemoryResource.cpp
    ../../tests/cpp/image/TEST_PixelTypes.cpp
    ../../tests/cpp/io/TEST_GDAL_Driver.cpp
    ../../tests/cpp/io/TEST_OGR_Driver.cpp
    ../../tests/cpp/utilities/TEST_FilesystemUtilities.cpp
    ../../tests/cpp/utilities/TEST_StringUtilities.cpp
)

#-------------------------------#
#-    Create the executable    -#
#-------------------------------#
include_directories( "${PROJECT_BINARY_DIR}/../include" ../../tests/cpp/googletest ../../tests/cpp/googletest/include )

add_executable( geoexplore-unit-test
                ${UNIT_TEST_HEADERS}
                ${UNIT_TEST_SOURCES}
)

target_link_libraries( geoexplore-unit-test
                       ${GeoExplore_LIBRARY}
                       ${CMAKE_THREAD_LIBS_INIT}
                       ${Boost_LIBRARIES}
                       ${GDAL_LIBRARY}
)

