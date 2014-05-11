/**
 * @file    ImageIO.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include "ImageIO.hpp"

namespace GEO{

/**
 * Compute the driver given an image pathname
*/
GEO::ImageDriver compute_driver( const boost::filesystem::path& pathname ){
    
    /**
     * Open the file to get the magic number
    */
    std::string magic_number = getMagicNumber( pathname ); 


    /**
     * Test the extension to estimate the driver
    */
    std::string ext = pathname.extension().native();

    /// GDAL Driver
    return GEO::ImageDriver::GDAL;

}




} /// End of GEO Namespace
