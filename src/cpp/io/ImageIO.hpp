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

/// C++ Standard Libraries
#include <iostream>


namespace GEO{
namespace IO{

/**
 * Driver Options
*/
enum class DriverOptions{
    NONE,
    READ_ONLY
}; /// End Driver Options Class

/**
 * Compute the image Driver
*/
GEO::ImageDriverType compute_driver( const boost::filesystem::path& pathname, const DriverOptions& options = DriverOptions::NONE );    


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
    GEO::ImageDriverType driver = compute_driver(pathname);

    
    /**
     * Since we are just loading pixel data, call the appropriate load_image_data function
     */
    if( driver == GEO::ImageDriverType::GDAL ){
        int rowSize;
        output_image.setResource( GEO::IO::GDAL::load_image<PixelType>(pathname));
    }
    else{
        throw std::runtime_error("Unknown driver.");
    }
    
}

/**
 * Read a Disk Image
*/
template <typename PixelType>
void read_image( boost::filesystem::path const& pathname, DiskImage<PixelType>& output_image ){

    std::cout << "Read Disk Image" << std::endl;
    // make sure the file exists
    if( boost::filesystem::exists( pathname ) == false ){
        throw std::runtime_error(std::string(std::string("error: File \"") + pathname.native() + std::string("\" does not exist.")).c_str());
    }

    // compute the required driver
    GEO::ImageDriverType driver = compute_driver( pathname, DriverOptions::READ_ONLY );
    
    // create the resource
    DiskResource<PixelType> resource;
    
    boost::shared_ptr<GEO::IO::ImageDriverBase> image_driver(nullptr);

    /**
     * Iterate through potential drivers
     */
    if( driver == ImageDriverType::OPENCV ){
        image_driver = boost::shared_ptr<GEO::IO::ImageDriverBase>(new GEO::IO::OPENCV::ImageDriverOpenCV());
    }
    else if( driver == ImageDriverType::GDAL ){
        image_driver = boost::shared_ptr<GEO::IO::ImageDriverBase>(new GEO::IO::GDAL::ImageDriverGDAL());
    }
    else{
        throw std::runtime_error("Unknown driver type.");
    }
    

    // set the resource
    resource.setDriver( image_driver );

    // set the driver
    output_image.setResource(resource);
}


/**
 * Write an image
*/
template <typename PixelType>
void write_image( Image<PixelType>& output_image, boost::filesystem::path const& pathname ){

    // determine the driver type
    GEO::ImageDriverType driver = compute_driver(pathname);

    /**
     * Select the driver's write function
    */
    if( driver == GEO::ImageDriverType::GDAL ){
        GEO::IO::GDAL::write_image<PixelType>( output_image, pathname );
    }
    else if( driver == GEO::ImageDriverType::NETPBM ){
        GEO::IO::NETPBM::write_image<PixelType>( output_image, pathname );
    }
    else if( driver == GEO::ImageDriverType::OPENCV ){
        GEO::IO::OPENCV::write_image<PixelType>( output_image, pathname );
    }
    else{
        throw std::runtime_error("Unknown driver.");
    }

}


} /// End of IO Namespace
} /// End of GEO Namespace

#endif
