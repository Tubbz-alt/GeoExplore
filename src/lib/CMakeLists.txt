#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#
#    Purpose:  Build script for the GeoExplore library.
#

#-----------------------------------------#
#-     Define Required CMake Version     -#
#-----------------------------------------#
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )


#----------------------------#
#-        Allow C++ 11x     -#
#----------------------------#
SET(CMAKE_CXX_FLAGS "-std=c++11")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib )


#---------------------------------#
#-     Set the Project Name      -#
#---------------------------------#
PROJECT( Lib-Geo-Explore )


#-----------------------#
#-     Find Boost      -#
#-----------------------#
find_package( Boost REQUIRED 
                COMPONENTS
                    FILESYSTEM
                    SYSTEM
            )

#------------------------------#
#-     Find GDAL Library      -#
#------------------------------#
find_package( GDAL REQUIRED )
include_directories( ${GDAL_INCLUDE_DIR} )

#--------------------------------#
#-     Find OpenCV Library      -#
#--------------------------------#
find_package( OpenCV REQUIRED )

#-----------------------#
#-     Find Boost      -#
#-----------------------#
find_package( Boost 
                COMPONENTS
                    system
                    filesystem
                REQUIRED )

#-----------------------------------------#
#-     Define Required Header Files      -#
#-----------------------------------------#

#   Core Module
set( GEOEXPLORE_CORE_HEADERS
    core/Enumerations.hpp
    core/Exceptions.hpp
    core/A_Size.hpp
)


#   Coordinate Module
set( GEOEXPLORE_COORDINATE_HEADERS
    coordinate/CoordinateBase.hpp
    coordinate/CoordinateGeographic.hpp
    coordinate/CoordinateUTM.hpp
)

#  DEM Module
set( GEOEXPLORE_DEM_HEADERS
    dem/A_DEM_IO_Driver_Base.hpp
    dem/A_DEM_IO_Driver_Flat.hpp
    dem/A_DEM_IO_Driver_SRTM.hpp
    dem/An_Elevation_Tile.hpp
    dem/DEM_Manager.hpp
)

#  Image Module
set( GEOEXPLORE_IMAGE_HEADERS
    image/BaseResource.hpp
    image/ChannelType.hpp
    image/DiskResource.hpp
    image/Image.hpp
    image/MemoryResource.hpp
    image/MetadataContainerBase.hpp
    image/MetadataContainer.hpp
    image/PixelBase.hpp
    image/PixelGray.hpp
    image/PixelRGB.hpp
)

#  IO Module
set( GEOEXPLORE_IO_HEADERS
    io/GDAL_Driver.hpp
    io/ImageDriverBase.hpp
    io/ImageIO.hpp
    io/OGR_Driver.hpp
    io/OpenCV_Driver.hpp
)

#   Math Module
set( GEOEXPLORE_MATH_HEADERS
    math/A_Rectangle.hpp
    math/A_Point.hpp
    math/A_Polygon.hpp
)


#  Thirdparty Module
set( GEOEXPLORE_THIRDPARTY_HEADERS
    thirdparty/pugixml/pugixml.hpp
    thirdparty/pugixml/pugiconfig.hpp
)


#   Utility Module
set( GEOEXPLORE_UTILITIES_HEADERS
    utilities/FilesystemUtilities.hpp
    utilities/StringUtilities.hpp
)

#  Combine modules
set( GEOEXPLORE_HEADERS
    ${GEOEXPLORE_CORE_HEADERS}
    ${GEOEXPLORE_COORDINATE_HEADERS}
    ${GEOEXPLORE_DEM_HEADERS}
    ${GEOEXPLORE_IMAGE_HEADERS}
    ${GEOEXPLORE_IO_HEADERS}
    ${GEOEXPLORE_MATH_HEADERS}
    ${GEOEXPLORE_THIRDPARTY_HEADERS}
    ${GEOEXPLORE_UTILITIES_HEADERS}
)


#----------------------------------------#
#-     Define Required Source Files     -#
#----------------------------------------#

#    Core Module
set( GEOEXPLORE_CORE_SOURCES
    core/Enumerations.cpp
    core/Exceptions.cpp
)

#    Coordinate Module
set( GEOEXPLORE_COORDINATE_SOURCES
    coordinate/CoordinateBase.cpp
)

#   Dem Sources
set( GEOEXPLORE_DEM_SOURCES
    dem/DEM_Manager.cpp
    dem/A_DEM_IO_Driver_FLAT.cpp
)


#   Image Module
set( GEOEXPLORE_IMAGE_SOURCES
    image/MetadataContainer.cpp
    image/MetadataContainerBase.cpp
)

#   IO Module
set( GEOEXPLORE_IO_SOURCES
    io/GDAL_Driver.cpp
    io/ImageDriverBase.cpp
    io/ImageIO.cpp
    io/NETPBM_Driver.cpp
    io/OGR_Driver.cpp
    io/OpenCV_Driver.cpp
)

#  Math Modules
set( GEOEXPLORE_MATH_SOURCES
)


#  Thirdparty Module
set( GEOEXPLORE_THIRDPARTY_SOURCES
    thirdparty/pugixml/pugixml.cpp
)


#   Utilities Module
set( GEOEXPLORE_UTILITIES_SOURCES
    utilities/FilesystemUtilities.cpp
    utilities/StringUtilities.cpp
)

#   Combine Modules
set( GEOEXPLORE_SOURCES
    ${GEOEXPLORE_CORE_SOURCES}
    ${GEOEXPLORE_COORDINATE_SOURCES}
    ${GEOEXPLORE_DEM_SOURCES}
    ${GEOEXPLORE_IMAGE_SOURCES}
    ${GEOEXPLORE_IO_SOURCES}
    ${GEOEXPLORE_MATH_SOURCES}
    ${GEOEXPLORE_THIRDPARTY_SOURCES}
    ${GEOEXPLORE_UTILITIES_SOURCES}
)

#-----------------------------------------#
#-      Generate the Shared Object       -#
#-----------------------------------------#
include_directories( ${PROJECT_BINARY_DIR}/include/ )

add_library( GeoExplore SHARED
             ${GEOEXPLORE_SOURCES}
             ${GEOEXPLORE_HEADERS}
)

target_link_libraries(
            GeoExplore
            ${Boost_LIBRARIES}
            ${GDAL_LIBRARY}
            ${OpenCV_LIBS}
            ${Boost_LIBRARIES}
)


