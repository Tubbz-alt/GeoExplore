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
include_directories( "${PROJECT_BINARY_DIR}/../include" )

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

