#    File:    CMakeLists.txt
#    Author:  Josh Gleason
#    Date:    5/17/2014
#    
#    Purpose:  Build script for the Terrain-Explore utility
#

# Define the project name
project(terrain-explore)


#  Set the executable output path
#set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin )
#set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/../../lib )

#  Set list of directories to search for cmake modules
set( CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake
)


#-----------------------------------#
#-     Find C++ Thread Library     -#
#-----------------------------------#
find_package( Threads )

#--------------------------#
#-  Find Qt5 Libraries    -#
#--------------------------#
if( DEFINED ENV{QT5_CMAKE_PATH} )
    set(Qt5_DIR $ENV{QT5_CMAKE_PATH})
endif()
find_package( Qt5
                COMPONENTS
                    Gui
                    OpenGL
                    Widgets
                    Core
)
if( NOT Qt5_FOUND )
    MESSAGE("Qt5 was not found. Consider setting QT5_CMAKE_PATH to the Qt5Config.cmake directory.")
    return()
endif()

#  Tell CMake to use the necessary modules
set( QT_USE_QTOPENGL ON )

#  Tell CMake to always look for includes in the MOC path
set( CMAKE_AUTOMOC ON )

#  Force position independent code (which should be a default
#  however Qt5 complains if this isn't here)
add_definitions(-fPIC)

#-----------------#
#-  Find Lib Z   -#
#-----------------#
find_package( ZLIB REQUIRED )

#------------------------------------#
#-  Find OpenGL Libraries (Drivers) -#
#------------------------------------#
find_package( OpenGL REQUIRED )

#-------------------------------------------#
#-  Find OpenGL Extension Wrangler (GLEW)  -#
#-------------------------------------------#
find_package( GLEW REQUIRED )

#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( TERRAINEXPLORE_HEADERS
    Options.hpp
    TerrainViewer.hpp
    glincludes.hpp
)

#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( TERRAINEXPLORE_SOURCES 
    main.cpp
    Options.cpp
    TerrainViewer.cpp
)

#----------------------------------#
#-      Process All Includes      -#
#----------------------------------#

#  Boost Includes
include_directories( ${Boost_INCLUDE_DIRS} )

#  Glew Includes
include_directories( ${GLEW_INCLUDE_DIR})


#  Include Qt5
#  Some builds of Qt5 apparently use different names for this variable
include_directories(${Qt5Widgets_INCLUDES}
                    ${Qt5OpenGL_INCLUDES}
)
include_directories(${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5OpenGL_INCLUDE_DIRS}
)


#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
add_executable( terrain-explore
                ${TERRAINEXPLORE_SOURCES}
                ${TERRAINEXPLORE_HEADERS}
                ${TERRAINEXPLORE_HEADERS_MOC}
)

#  Allows functionality of QMake through CMake
qt5_use_modules( terrain-explore 
                 Widgets
                 OpenGL
                 Core
)

target_link_libraries( terrain-explore 
                GeoExplore
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${Qt5Widgets_LIBRARY}
                ${Qt5OpenGL_LIBRARY}
                ${OPENGL_LIBRARIES}
                ${GLEW_LIBRARY}
                ${ZLIB_LIBRARY}
)

