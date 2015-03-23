#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/22/2015
#
#    Purpose:  Build the Geo-Dem-Utility Application
#


#------------------------------#
#-    Set the Project Name    -#
#------------------------------#
PROJECT( Geo-DEM-Utility )

#  Set C++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall")


#------------------------------#
#-     Find GDAL Library      -#
#------------------------------#
find_package( GDAL REQUIRED )
include_directories( ${GDAL_INCLUDE_DIR} )


#------------------------------------------#
#-      Define Required Header Files      -#
#------------------------------------------#
set( GEO_DEM_UTILITY_HEADERS
    GDU_Options.hpp
    GDU_Utilities.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEO_DEM_UTILITY_SOURCES
    geo-dem-utility.cpp
    GDU_Options.cpp
    GDU_Utilities.cpp
)


#----------------------------------#
#-     Build the Application      -#
#----------------------------------#
include_directories(../../lib)

add_executable( geo-dem-utility
                ${GEO_DEM_UTILITY_SOURCES}
                ${GEO_DEM_UTILITY_HEADERS}
)

target_link_libraries( geo-dem-utility
                GeoExplore
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
                ${OpenCV_LIBS}
)

