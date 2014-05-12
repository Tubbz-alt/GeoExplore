/**
 * @file    ImageIO.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include "ImageIO.hpp"

/// GeoExplore Libraries
#include <GeoExplore/utilities/FilesystemUtilities.hpp>


namespace GEO{

/**
 * Compute the driver given an image pathname
*/
GEO::ImageDriver compute_driver( const boost::filesystem::path& pathname ){
    
    // get the file type
    GEO::FS::FileType ftype = GEO::FS::getFileType(pathname);

    // parse available options for drivers


    /**
     * Test the extension to estimate the driver
    */
    std::string ext = pathname.extension().native();

    /// GDAL Driver
    return GEO::ImageDriver::GDAL;

}




} /// End of GEO Namespace
