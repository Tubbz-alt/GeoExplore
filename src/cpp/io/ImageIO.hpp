/**
 * @file    ImageIO.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IO_IMAGEIO_HPP__
#define __SRC_CPP_IO_IMAGEIO_HPP__

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
        
        output_image.resource() = GEO::IO::GDAL::load_image<PixelType>(pathname);
    }
    else{
        throw std::runtime_error("Unknown driver.");
    }
    
} 

} /// End of IO Namespace
} /// End of GEO Namespace

#endif
