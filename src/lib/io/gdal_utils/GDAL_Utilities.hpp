/**
 * @file GDAL_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#ifndef __GEOEXPLORE_LIB_IO_GDAL_UTILS_GDAL_UTILITIES_HPP__
#define __GEOEXPLORE_LIB_IO_GDAL_UTILS_GDAL_UTILITIES_HPP__

// Boost C++ Libraries
#include <boost/filesystem.hpp>


// GDAL Libraries
#include <cpl_conv.h>
#include <cpl_string.h>
#include <gdal.h>
#include <gdal_priv.h>
#include <ogr_spatialref.h>


// IPL Libraries
#include "../../core/Enumerations.hpp"
#include "../../math/A_Point.hpp"

namespace GEO{
namespace IO{
namespace GDAL{


/**
 * @brief Get GDAL Short Driver Name from Filename.
 *
 * @param[in] filename Filename to fetch the GDAL driver.
*/
std::string Get_Short_Driver_From_Filename( const boost::filesystem::path& filename );


/**
 * @brief Project Coordinate
*/
MATH::A_Point2d GDAL_Pixel_To_World( MATH::A_Point2d const& pixel, 
                                     const double* adfGeoTransform );


/**
 * @brief Convert GDAL Datum String to Datum Types
*/
Datum GDAL_Datum_String_To_DatumType( std::string const& datum_string );


} // End of GDAL Namespace
} // End of IO   Namespace
} // End of GEO  Namespace

#endif
