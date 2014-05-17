/**
 * @file    ImageIO.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include "ImageIO.hpp"

/// GeoExplore Libraries
#include <GeoExplore/utilities/FilesystemUtilities.hpp>


namespace GEO{
namespace IO{

/**
 * Compute the driver given an image pathname
*/
GEO::ImageDriver compute_driver( const boost::filesystem::path& pathname ){
    
    // get the file type
    GEO::FS::FileType ftype = GEO::FS::getFileType(pathname);

    // opencv drivers
    if( ftype == GEO::FS::FileType::JPEG ){
        return GEO::ImageDriver::OPENCV;
    }
    if( ftype == GEO::FS::FileType::PNG ){
        return GEO::ImageDriver::OPENCV;
    }

    /// GDAL Driver
    return GEO::ImageDriver::GDAL;

}



} /// End of IO Namespace
} /// End of GEO Namespace
