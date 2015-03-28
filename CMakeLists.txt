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


#----------------------------------------#
#-     Add 3rd Party Cmake Modules      -#
#----------------------------------------#
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#-------------------------------#
#-     Set the Project Name    -#
#-------------------------------#
PROJECT( Geo-Explore )


#---------------------#
#-    Find Eigen3    -#
#---------------------#
FIND_PACKAGE( Eigen3 )



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
if( NOT ${Boost_FOUND} )
    MESSAGE( FATAL_ERROR "Unable to find Boost Libraries.")
endif()


#------------------------------------#
#-     Build GeoExplore Project     -#
#------------------------------------#
add_subdirectory(src)

