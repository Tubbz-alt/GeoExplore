/**
 * @file GDAL_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#ifndef __GEOEXPLORE_LIB_IO_GDAL_UTILS_GDAL_UTILITIES_HPP__
#define __GEOEXPLORE_LIB_IO_GDAL_UTILS_GDAL_UTILITIES_HPP__

// GDAL Libraries
#include <cpl_conv.h>
#include <cpl_string.h>
#include <gdal.h>
#include <gdal_priv.h>
#include <ogr_spatialref.h>


// GeoExplore Libraries
#include "../../coordinate/CoordinateUTM.hpp"
#include "../../core/Enumerations.hpp"
#include "../../filesystem.hpp"
#include "../../image/ChannelType.hpp"
#include "../../math/A_Point.hpp"
#include "../../math/A_Rectangle.hpp"

namespace GEO{
namespace IO{
namespace GDAL{


/**
 * @brief Convert generic ChannelType to a GDAL Type.
*/
template<typename CType>
GDALDataType ctype2gdaltype(){
    if( std::is_same<CType,IMG::ChannelTypeUInt8>::value ){
        return GDT_Byte;
    }
    if( std::is_same<CType,IMG::ChannelTypeUInt12>::value ){
        return GDT_UInt16;
    }
    if( std::is_same<CType,IMG::ChannelTypeUInt14>::value ){
        return GDT_UInt16;
    }
    if( std::is_same<CType,IMG::ChannelTypeUInt16>::value ){
        return GDT_UInt16;
    }
    if( std::is_same<CType,IMG::ChannelTypeUInt32>::value ){
        return GDT_UInt32;
    }
    if( std::is_same<CType,IMG::ChannelTypeDouble>::value ){
        return GDT_Float64;
    }
    if( std::is_same<CType,IMG::ChannelTypeDoubleFree>::value ){
        return GDT_Float64;
    }

    return GDT_Unknown;
}


/**
 * @brief Get GDAL Short Driver Name from Filename.
 *
 * @param[in] filename Filename to fetch the GDAL driver.
*/
std::string Get_Short_Driver_From_Filename( const FS::FilesystemPath& filename );


/**
 * @brief Project Coordinate
*/
MATH::A_Point2d GDAL_Pixel_To_World( MATH::A_Point2d const& pixel, 
                                     const double* adfGeoTransform );


/**
 * @brief Convert GDAL Datum String to Datum Types
*/
Datum GDAL_Datum_String_To_DatumType( std::string const& datum_string );


/** 
 * @brief Add the Grid Zone to the Rectangle
 *
 * @param[out] rectangle Rectangle to modify.
 * @param[in] coord Coordinate to use to fetch.
 */
template <typename CoordinateType>
typename std::enable_if<std::is_same<CoordinateType,CRD::CoordinateUTM_d>::value,CRD::CoordinateUTM_d>::type
     Add_Zone_To_Rectangle( MATH::A_Rectangle<CRD::CoordinateUTM_d>& rectangle, 
                            CoordinateType const& coordinate )
{
    // Set the grid zone
    rectangle.Get_Min_Corner().zone() = coordinate.zone();
    rectangle.Get_Min_Corner().Is_Northern_Hemisphere() = coordinate.Is_Northern_Hemisphere();
    return coordinate;

}


/** 
 * @brief Add the Grid Zone to the Rectangle
 *
 * @param[out] rectangle Rectangle to modify.
 * @param[in] coord Coordinate to use to fetch.
 */
template <typename CoordinateType>
typename std::enable_if<!std::is_same<CoordinateType,CRD::CoordinateUTM_d>::value,CoordinateType>::type
     Add_Zone_To_Rectangle( MATH::A_Rectangle<CoordinateType>& rectangle, 
                            CoordinateType const& coordinate )
{
    return coordinate;
}


} // End of GDAL Namespace
} // End of IO   Namespace
} // End of GEO  Namespace

#endif
