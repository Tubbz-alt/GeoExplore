#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/15/2015
#
#    Purpose:  Build the GeoExplore Project
#


#  Define the required CMake Version
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

#----------------------------#
#-        Allow C++ 11x     -#
#----------------------------#
SET(CMAKE_CXX_FLAGS "-std=c++11")


#-------------------------------#
#-     Set the Project Name    -#
#-------------------------------#
PROJECT( Geo-Explore )


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
if( NOT ${Boost_FOUND} )
    MESSAGE( FATAL_ERROR "Unable to find Boost Libraries.")
endif()
MESSAGE("Boost Include Directory: ${Boost_INCLUDE_DIRS}")


#------------------------------------#
#-     Build GeoExplore Project     -#
#------------------------------------#
add_subdirectory(src)

