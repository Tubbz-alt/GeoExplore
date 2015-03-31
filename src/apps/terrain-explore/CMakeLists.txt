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

#  Set C++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

#  Set list of directories to search for cmake modules
set( CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake
)


#-----------------------------------#
#-     Find C++ Thread Library     -#
#-----------------------------------#
find_package( Threads )


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


#--------------------------#
#-  Find Qt4 Libraries    -#
#--------------------------#
set(QT_USE_QTOPENGL TRUE)

find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

add_definitions( ${QT_DEFINITIONS} )

include_directories( ${CMAKE_BINARY_DIR} )

QT4_WRAP_CPP( MOC_SRCS ${TERRAINEXPLORE_HEADERS} )


#----------------------------------#
#-      Process All Includes      -#
#----------------------------------#

#  Boost Includes
include_directories( ${Boost_INCLUDE_DIRS} )

#  Glew Includes
include_directories( ${GLEW_INCLUDE_DIR})


#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
add_executable( terrain-explore
                ${TERRAINEXPLORE_SOURCES}
                ${TERRAINEXPLORE_HEADERS}
                ${MOC_SRCS}
)

target_link_libraries( terrain-explore 
                GeoExplore
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${QT_LIBRARIES}
                ${OPENGL_LIBRARIES}
                ${GLEW_LIBRARY}
                ${ZLIB_LIBRARY}
)

