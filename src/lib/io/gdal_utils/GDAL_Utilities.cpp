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




} // End of GDAL Namespace
} // End of IO   Namespace
} // End of GEO  Namespace

