#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#
#    Purpose:  Build script for GeoExplore GUI
#

# Define the project name
project(Geo-Explore)


#  Set the executable output path
#set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin )
#set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/../lib )

#  Set list of directories to search for cmake modules
set( CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake
)


# Configure C++11
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

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

#----------------------------------#
#-       Find QT5 Libraries       -#
#----------------------------------#

find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

add_definitions( ${QT_DEFINITIONS} )

include_directories( ${CMAKE_BINARY_DIR} )
 
  
# Next, using precompiler, compiler and linker
   
# using Qt meta-system (precompiler)
QT4_WRAP_CPP( MOC_SRCS ${GUI_HEADERS} )



#--------------------------------------#
#-      Add Remaining Includes        -#
#--------------------------------------#

#  boost
include_directories(${Boost_INCLUDE_DIRS})

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories(../../lib)

add_executable( geo-explore 
                ${GUI_SOURCES}
                ${GUI_HEADERS}
                ${MOC_SRCS}
)

target_link_libraries( geo-explore
                GeoExplore
                ${QT_LIBRARIES}
                ${Boost_LIBRARIES}
)



