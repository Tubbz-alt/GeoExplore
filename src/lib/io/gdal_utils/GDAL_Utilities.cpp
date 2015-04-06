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
                                     A_Size<int>const&             image_size,
                                     OGRSpatialReference&          oSRS,
                                     double*&                      adfGeoTransform )
{
    // Temp Variables
    Status status;
    std::string value_str;
    int zone, isNorth;

    // If Metadata is null, then return false
    if( image_metadata == nullptr ){
        return false;
    }

    // Check if we are geographic
    if( image_metadata->Query_Metadata("IS_GEOGRAPHIC", value_str) == true &&
        value_str == "TRUE" )
    {
    }

    // Check if we are projected
    else if( image_metadata->Query_Metadata("IS_PROJECTED", value_str) == true &&
        value_str == "TRUE" )
    {
        // Check if UTM
        if( image_metadata->Query_Metadata("IS_UTM", value_str) == true &&
            value_str == "TRUE" )
        {
            // Get zone
            if( image_metadata->Query_Metadata("UTM_ZONE", zone) == true &&
                image_metadata->Query_Metadata("UTM_IS_NORTHERN", value_str) == true )
            {
                // Set the zone
                if( value_str == "TRUE" || value_str == "true" ){ isNorth = true; }
                else{ isNorth = false; }
                
                oSRS.SetUTM( zone, isNorth);
            }

        }

    }
    
    // Otherwise, error
    else{
        return false;
    }
    
    // Set the Geog CS
    oSRS.SetWellKnownGeogCS( "WGS84" );
    
    // Find the corners
    double tl_x, tl_y, tr_x, tr_y, bl_x, bl_y, br_x, br_y;
    if( image_metadata->Query_Metadata("CORNER_COORDINATE_TL_X", tl_x) == false ){ return false; }
    if( image_metadata->Query_Metadata("CORNER_COORDINATE_TL_Y", tl_y) == false ){ return false; }
    if( image_metadata->Query_Metadata("CORNER_COORDINATE_TR_X", tr_x) == false ){ return false; }
    if( image_metadata->Query_Metadata("CORNER_COORDINATE_TR_Y", tr_y) == false ){ return false; }
    if( image_metadata->Query_Metadata("CORNER_COORDINATE_BL_X", bl_x) == false ){ return false; }
    if( image_metadata->Query_Metadata("CORNER_COORDINATE_BL_Y", bl_y) == false ){ return false; }
    if( image_metadata->Query_Metadata("CORNER_COORDINATE_BR_X", br_x) == false ){ return false; }
    if( image_metadata->Query_Metadata("CORNER_COORDINATE_BR_Y", br_y) == false ){ return false; }

    // Compute the ADF Geo Transform
    int w = image_size.Width();
    int h = image_size.Height();
    std::vector<MATH::A_Point2d> pixels, coordinates;
    pixels.push_back(MATH::A_Point2d(0,0));  coordinates.push_back( MATH::A_Point2d(tl_x, tl_y));
    pixels.push_back(MATH::A_Point2d(w,0));  coordinates.push_back( MATH::A_Point2d(tr_x, tr_y));
    pixels.push_back(MATH::A_Point2d(0,h));  coordinates.push_back( MATH::A_Point2d(bl_x, bl_y));
    pixels.push_back(MATH::A_Point2d(w,h));  coordinates.push_back( MATH::A_Point2d(br_x, br_y));

    // Construct the ADF Geo Transform
    status = Compute_Geo_Transform( pixels, coordinates, adfGeoTransform );
    if( status.Get_Status_Type() != StatusType::SUCCESS ){ return false; }

    // Return Success
    return true;
}


} // End of GDAL Namespace
} // End of IO   Namespace
} // End of GEO  Namespace

