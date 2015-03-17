#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#
#    Purpose:  Build script for GeoExplore GUI
#

#  Define Required CMake Version
cmake_minimum_required( VERSION 2.8.9 FATAL_ERROR )

# Define the project name
project(Geo-Explore)

#  Allow C++ 11x
SET(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

#  Set the executable output path
#set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin )
#set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/../lib )

#----------------------------------#
#-       Find QT5 Libraries       -#
#----------------------------------#
if( DEFINED ENV{QT5_CMAKE_PATH} )
    set(Qt5_DIR $ENV{QT5_CMAKE_PATH})
endif()
find_package( Qt5
                COMPONENTS
                    OpenGL
                    Widgets
                    Core
            )
if( NOT Qt5_FOUND )
    MESSAGE( FATAL_ERROR "Qt5 was not found. Consider setting QT5_CMAKE_PATH to the Qt5Config.cmake directory.")
endif()

#  Tell CMake to use the necessary modules
set( QT_USE_QTOPENGL ON )

#  Tell CMake to run moc when necessary
set( CMAKE_AUTOMOC ON )

#  Include Qt5
#  Some builds of Qt5 apparently use different names for this variable
include_directories(${Qt5Core_INCLUDES}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Widgets_INCLUDES} 
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5OpenGL_INCLUDES} 
                    ${Qt5OpenGL_INCLUDE_DIRS}
                    )

#  Force position independent code (which should be a default
#  however Qt5 complains if this isn't here)
add_definitions(-fPIC)


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
include_directories(${Boost_INCLUDE_DIRS})

#-----------------------------------#
#-     Find C++ Thread Library     -#
#-----------------------------------#
find_package( Threads )

#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( GUI_HEADERS
    core/Global_Options.hpp
    gui/MainWindow.hpp
    gui/toolbar/ToolbarWidget.hpp
    gui/utils/coordinate/CoordinateConversionDialog.hpp
    gui/utils/coordinate/CoordinateConversionReference.hpp
    gui/utils/coordinate/CoordinateConversionWidget.hpp
    gui/utils/coordinate/CoordinateConversionGeographicPanelWidget.hpp
    gui/utils/coordinate/CoordinateConversionUTMPanelWidget.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GUI_SOURCES
    main.cpp
    core/Global_Options.cpp
    gui/MainWindow.cpp
    gui/toolbar/ToolbarWidget.cpp
    gui/utils/coordinate/CoordinateConversionDialog.cpp
    gui/utils/coordinate/CoordinateConversionGeographicPanelWidget.cpp
    gui/utils/coordinate/CoordinateConversionUTMPanelWidget.cpp
    gui/utils/coordinate/CoordinateConversionReference.cpp
    gui/utils/coordinate/CoordinateConversionWidget.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#

add_executable( geo-explore 
                ${GUI_SOURCES}
                ${GUI_HEADERS}
)

#  Allows functionality of QMake through CMake
qt5_use_modules( geo-explore 
                 Widgets
                 OpenGL
                 Core
                 )

target_link_libraries( geo-explore
                GeoExplore
                ${Qt5Widgets_LIBRARIES}
                ${Boost_LIBRARIES}
)



