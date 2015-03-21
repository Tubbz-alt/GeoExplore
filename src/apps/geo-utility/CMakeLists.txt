#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    8/3/2014
#    
#    Purpose:  Build script for the Geo-Utility
#

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/../lib )


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
    Globals.hpp
    Options.hpp
    Utilities.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEOUTILITY_SOURCES
    geo-utility.cpp
    Options.cpp
    Utilities.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories( ../../lib )

add_executable( geo-utility
                ${GEOUTILITY_SOURCES}
                ${GEOUTILITY_HEADERS}
)

target_link_libraries( geo-utility
                GeoExplore
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
                ${OpenCV_LIBS}
)

