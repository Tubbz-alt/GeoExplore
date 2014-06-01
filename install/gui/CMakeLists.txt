#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#
#    Purpose:  Build script for GeoExplore GUI
#

#  Define Required CMake Version
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

# Define the project name
project(geo-explore)

#  Allow C++ 11x
SET(CMAKE_CXX_FLAGS "-std=c++0x")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/../lib )

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


#----------------------------------#
#-       Find QT5 Libraries       -#
#----------------------------------#
find_package( Qt5Widgets REQUIRED )
#find_package( QtDeclarative )

#  Tell CMake to run moc when necessary
set( CMAKE_AUTOMOC ON )

#  Tell CMake to always look for includes in the MOC path
set( CMAKE_INCLUDE_CURRENT_DIR ON )

#  Include Qt5
#  Some builds of Qt5 apparently use different names for this variable
include_directories(${Qt5Widgets_INCLUDES})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

#  Force position independent code (which should be a default
#  however Qt5 complains if this isn't here)
add_definitions(-fPIC)

#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( GUI_HEADERS
    ../../src/cpp/gui/MainWindow.hpp
    ../../src/cpp/gui/toolbar/ToolbarWidget.hpp
    ../../src/cpp/gui/utils/coordinate/CoordinateConversionDialog.hpp
    ../../src/cpp/gui/utils/coordinate/CoordinateConversionWidget.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GUI_SOURCES
    ../../src/cpp/gui/main.cpp
    ../../src/cpp/gui/MainWindow.cpp
    ../../src/cpp/gui/toolbar/ToolbarWidget.cpp
    ../../src/cpp/gui/utils/coordinate/CoordinateConversionDialog.cpp
    ../../src/cpp/gui/utils/coordinate/CoordinateConversionWidget.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories( "${PROJECT_BINARY_DIR}/../include" )

add_executable( geo-explore 
                ${GUI_SOURCES}
                ${GUI_HEADERS}
)

target_link_libraries( geo-explore
                ${GeoExplore_LIBRARY}
                ${Qt5Widgets_LIBRARIES}
                ${Boost_LIBRARIES}
)



