/**
 * @file    GDAL_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include "GDAL_Utilities.hpp"
#include "../../utilities/FilesystemUtilities.hpp"
#include "../../utilities/StringUtilities.hpp"

namespace GEO{
namespace IO{
namespace GDAL{

/**
 * Get the Short GDAL Driver from the filename
*/
std::string Get_Short_Driver_From_Filename( const FS::FilesystemPath& filename ){

    // Get the File Type
    FS::FileType file_type = FS::Get_File_Type( filename );
    
    // png images
    if( file_type == FS::FileType::PNG ){
        return "PNG";
    }
    
    // ntf images
    if( file_type == FS::FileType::NITF ){
        return "NITF";
    }
    
    // jpeg images
    if( file_type == FS::FileType::JPEG ){
        return "JPEG";
    }

    // Tiff
    if( file_type == FS::FileType::TIFF ){
        return "GTiff";
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



/**************************************************************************/
/*        Construct an OGR Spatial Reference from Image Metadata.         */
/**************************************************************************/
bool GDAL_Process_OGR_From_Metadata( IMG::MetadataContainer::ptr_t image_metadata,
                                     OGRSpatialReference&          oSRS,
                                     double*&                      adfGeoTransform )
{

    return false;
}


} // End of GDAL Namespace
} // End of IO   Namespace
} // End of GEO  Namespace

