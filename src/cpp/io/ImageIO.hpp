/**
 * @file    ImageIO.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IO_IMAGEIO_HPP__
#define __SRC_CPP_IO_IMAGEIO_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>
#include <GeoExplore/image/Image.hpp>
#include <GeoExplore/io/GDAL_Driver.hpp>
#include <GeoExplore/io/NETPBM_Driver.hpp>
#include <GeoExplore/io/OpenCV_Driver.hpp>

/// Boost C++ Libraries
#include <boost/filesystem.hpp>


namespace GEO{
namespace IO{

/**
 * Compute the image Driver
*/
GEO::ImageDriver compute_driver( const boost::filesystem::path& pathname );    


/**
 * Read an Image
*/
template<typename PixelType>
void read_image( boost::filesystem::path const& pathname, Image<PixelType>& output_image ){

    /// make sure the file exists
    if( boost::filesystem::exists( pathname ) == false ){
        throw std::runtime_error(std::string(std::string("error: File \"") + pathname.native() + std::string("\" does not exist.")).c_str());
    }

    /// decide which driver to use depending on the filename
    GEO::ImageDriver driver = compute_driver(pathname);

    
    /**
     * Since we are just loading pixel data, call the appropriate load_image_data function
     */
    if( driver == GEO::ImageDriver::GDAL ){
        int rowSize;
        output_image.setResource( GEO::IO::GDAL::load_image<PixelType>(pathname));
    }
    else{
        throw std::runtime_error("Unknown driver.");
    }
    
} 

/**
 * Write an image
*/
template <typename PixelType>
void write_image( Image<PixelType>& output_image, boost::filesystem::path const& pathname ){

    // determine the driver type
    GEO::ImageDriver driver = compute_driver(pathname);

    /**
     * Select the driver's write function
    */
    if( driver == GEO::ImageDriver::GDAL ){
        GEO::IO::GDAL::write_image<PixelType>( output_image, pathname );
    }
    else if( driver == GEO::ImageDriver::NETPBM ){
        GEO::IO::NETPBM::write_image<PixelType>( output_image, pathname );
    }
    else if( driver == GEO::ImageDriver::OPENCV ){
        GEO::IO::OPENCV::write_image<PixelType>( output_image, pathname );
    }
    else{
        throw std::runtime_error("Unknown driver.");
    }

}


} /// End of IO Namespace
} /// End of GEO Namespace

#endif
