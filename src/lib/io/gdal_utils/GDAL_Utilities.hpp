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


namespace GEO{
namespace IO{
namespace GDAL{


/**
 * @brief Get GDAL Short Driver Name from Filename.
 *
 * @param[in] filename Filename to fetch the GDAL driver.
*/
std::string Get_Short_Driver_From_Filename( const boost::filesystem::path& filename );




} // End of GDAL Namespace
} // End of IO   Namespace
} // End of GEO  Namespace

#endif
