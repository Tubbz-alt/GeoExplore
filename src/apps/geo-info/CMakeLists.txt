#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/17/2014
#
#    Purpose: Build the Geo-Info Application
#


#----------------------------------#
#-      Set the Project Name      -#
#----------------------------------#
PROJECT( Geo-Info )

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
set( GEOINFO_HEADERS
    Options.hpp
)


#------------------------------------------#
#-      Define Required Source Files      -#
#------------------------------------------#
set( GEOINFO_SOURCES
    main.cpp
    Options.cpp
)

#---------------------------------#
#-     Build the Application     -#
#---------------------------------#
include_directories( ../../lib )

add_executable( geo-info 
                ${GEOINFO_SOURCES}
                ${GEOINFO_HEADERS}
)

target_link_libraries( geo-info
                GeoExplore
                ${CMAKE_THREAD_LIBS_INIT}
                ${Boost_LIBRARIES}
                ${GDAL_LIBRARY}
                ${OpenCV_LIBS}
)

