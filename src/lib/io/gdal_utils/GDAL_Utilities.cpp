/**
 * @file    GDAL_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include "GDAL_Utilities.hpp"
#include "../../utilities/StringUtilities.hpp"

namespace GEO{
namespace IO{
namespace GDAL{

/**
 * Get the Short GDAL Driver from the filename
*/
std::string Get_Short_Driver_From_Filename( const boost::filesystem::path& filename ){

    // pull the extension
    std::string ext = filename.extension().native();
    std::string extl = string_toLower(ext);

    // png images
    if( extl == ".png" ){
        return "PNG";
    }
    
    // ntf images
    if( extl == ".ntf" || extl == ".ntif" ){
        return "NITF";
    }
    
    // jpeg images
    if( extl == ".jpg" || extl == "jpeg" ){
        return "JPEG";
    }

    return "";
}

/**
 * @brief Coordinate
*/
MATH::A_Point2d GDAL_Pixel_To_World( MATH::A_Point2d const& pixel, 
                                     const double* adfGeoTransform )
{

    // Create output point
    MATH::A_Point2d output;
    output.x() = adfGeoTransform[0] + adfGeoTransform[1] * pixel.x() + adfGeoTransform[2] * pixel.y();
    output.y() = adfGeoTransform[3] + adfGeoTransform[4] * pixel.x() + adfGeoTransform[5] * pixel.y();

    return output;
}


/**
 * Convert GDAL Datum String to Datum Types
*/
Datum GDAL_Datum_String_To_DatumType( std::string const& datum_string ){

    // Check if datum string is wgs84
    if( datum_string == "WGS_1984" ){
        return Datum::WGS84;
    }

    // return unknown
    return Datum::UNKNOWN;
}


} // End of GDAL Namespace
} // End of IO   Namespace
} // End of GEO  Namespace

