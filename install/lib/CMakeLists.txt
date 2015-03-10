#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/14/2014
#
#    Purpose:  Build script for the GeoExplore library.
#

#  Define Required CMake Version
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

#  Allow C++ 11x
SET(CMAKE_CXX_FLAGS "-std=c++11")

#  Set the executable output path
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib )

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
    ../src/cpp/core/Enumerations.hpp
    ../src/cpp/core/Exceptions.hpp
    ../src/cpp/core/A_Size.hpp
)


#   Coordinate Module
set( GEOEXPLORE_COORDINATE_HEADERS
    ../src/cpp/coordinate/CoordinateBase.hpp
    ../src/cpp/coordinate/CoordinateGeographic.hpp
    ../src/cpp/coordinate/CoordinateUTM.hpp
)

#  DEM Module
set( GEOEXPLORE_DEM_HEADERS
    ../src/cpp/dem/A_DEM_IO_Driver_Base.hpp
    ../src/cpp/dem/A_DEM_IO_Driver_Flat.hpp
    ../src/cpp/dem/A_DEM_IO_Driver_SRTM.hpp
    ../src/cpp/dem/An_Elevation_Tile.hpp
    ../src/cpp/dem/DEM_Manager.hpp
)

#  Image Module
set( GEOEXPLORE_IMAGE_HEADERS
    ../src/cpp/image/BaseResource.hpp
    ../src/cpp/image/ChannelType.hpp
    ../src/cpp/image/DiskResource.hpp
    ../src/cpp/image/Image.hpp
    ../src/cpp/image/MemoryResource.hpp
    ../src/cpp/image/MetadataContainerBase.hpp
    ../src/cpp/image/MetadataContainer.hpp
    ../src/cpp/image/PixelBase.hpp
    ../src/cpp/image/PixelGray.hpp
    ../src/cpp/image/PixelRGB.hpp
)

#  IO Module
set( GEOEXPLORE_IO_HEADERS
    ../src/cpp/io/GDAL_Driver.hpp
    ../src/cpp/io/ImageDriverBase.hpp
    ../src/cpp/io/ImageIO.hpp
    ../src/cpp/io/OGR_Driver.hpp
    ../src/cpp/io/OpenCV_Driver.hpp
)

#   Math Module
set( GEOEXPLORE_MATH_HEADERS
    ../src/cpp/math/A_Rectangle.hpp
    ../src/cpp/math/A_Point.hpp
    ../src/cpp/math/A_Polygon.hpp
)


#  Thirdparty Module
set( GEOEXPLORE_THIRDPARTY_HEADERS
    ../src/cpp/thirdparty/pugixml/pugixml.hpp
    ../src/cpp/thirdparty/pugixml/pugiconfig.hpp
)


#   Utility Module
set( GEOEXPLORE_UTILITIES_HEADERS
    ../src/cpp/utilities/FilesystemUtilities.hpp
    ../src/cpp/utilities/StringUtilities.hpp
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
    ../src/cpp/core/Enumerations.cpp
    ../src/cpp/core/Exceptions.cpp
)

#    Coordinate Module
set( GEOEXPLORE_COORDINATE_SOURCES
    ../src/cpp/coordinate/CoordinateBase.cpp
)

#   Dem Sources
set( GEOEXPLORE_DEM_SOURCES
    ../src/cpp/dem/DEM_Manager.cpp
)


#   Image Module
set( GEOEXPLORE_IMAGE_SOURCES
    ../src/cpp/image/MetadataContainer.cpp
    ../src/cpp/image/MetadataContainerBase.cpp
)

#   IO Module
set( GEOEXPLORE_IO_SOURCES
    ../src/cpp/io/GDAL_Driver.cpp
    ../src/cpp/io/ImageDriverBase.cpp
    ../src/cpp/io/ImageIO.cpp
    ../src/cpp/io/NETPBM_Driver.cpp
    ../src/cpp/io/OGR_Driver.cpp
    ../src/cpp/io/OpenCV_Driver.cpp
)

#  Math Modules
set( GEOEXPLORE_MATH_SOURCES
)


#  Thirdparty Module
set( GEOEXPLORE_THIRDPARTY_SOURCES
    ../src/cpp/thirdparty/pugixml/pugixml.cpp
)


#   Utilities Module
set( GEOEXPLORE_UTILITIES_SOURCES
    ../src/cpp/utilities/FilesystemUtilities.cpp
    ../src/cpp/utilities/StringUtilities.cpp
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


