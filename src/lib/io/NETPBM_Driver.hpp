/**
 * @file    NETPBM_Driver.hpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#ifndef __SRC_CPP_IO_NETPBMDRIVER_HPP__
#define __SRC_CPP_IO_NETPBMDRIVER_HPP__

/// C++ Standard Libraries
#include <iostream>

/// Boost C++ Libraries
#include <boost/filesystem.hpp>

/// GeoExplore Libraries
#include "../image/BaseResource.hpp"
#include "../image/ChannelType.hpp"
#include "../image/Image.hpp"
#include "../image/PixelBase.hpp"
#include "../image/PixelCast.hpp"
#include "../image/PixelGray.hpp"
#include "../image/PixelRGB.hpp"


namespace GEO{
namespace IO{
namespace NETPBM{

/**
 * @brief Write PGM Image
 * @param[in] data Image Resource Data
 * @param[in] filename Pathname to write to.
 */
template <typename PixelType>
void write_pgm_image( IMG::BaseResource<PixelType> const& data, 
                      boost::filesystem::path const& filename ){

    // open file
    FILE *fp = fopen( filename.c_str(), "wb" ); // open in binary mode

    // write data out
    fprintf( fp, "P5\n%d %d\n255\n", data.Cols(), data.Rows());
    
    unsigned char info;
    for( int y=0; y<data.Rows(); y++ ){
    for( int x=0; x<data.Cols(); x++ ){

        // create the RGB Pixel to convert.  This needs to convert any pixel type regardless of pixel type or channel type
        IMG::PixelGray_u8 output = IMG::pixel_cast<IMG::PixelGray_u8>(data[y*data.Cols() + x]);

        // write rgb to file
        info = output[0];

        fwrite( &info, 1, 1, fp);
    }}
    
    fclose(fp);

}


/**
 * @brief Write PPM Image
 *
 * @param[in] data Image pixel data.
 * @param[in] filename Image filename to write to.
 */
template <typename PixelType>
void write_ppm_image( IMG::BaseResource<PixelType> const& data, 
                      boost::filesystem::path const& filename ){
    
    // open file
    FILE *fp = fopen( filename.c_str(), "wb" ); // open in binary mode

    // write data out
    fprintf( fp, "P6\n%d %d\n255\n", data.Cols(), data.Rows());
    
    unsigned char color[3];
    for( int y=0; y<data.Rows(); y++ ){
    for( int x=0; x<data.Cols(); x++ ){

        // create the RGB Pixel to convert.  This needs to convert any pixel type regardless of pixel type or channel type
        IMG::PixelRGB_u8 output = IMG::pixel_cast<IMG::PixelRGB_u8>(data[y*data.Cols() + x]);

        // write rgb to file
        color[0] = output[0];
        color[1] = output[1];
        color[2] = output[2];

        fwrite( color, 1, 3, fp);
    }}
    
    fclose(fp);

}

/**
 * Write an RGB Image to NETPBM File
*/
template<typename PixelType, typename ResourceType>
void write_image( IMG::Image_<PixelType, ResourceType>const&  output_image, boost::filesystem::path const& pathname ){

    // select pgm or ppm
    if( pathname.extension().native() == ".ppm" ){
       
       // write the image
       write_ppm_image( output_image.getResource(), pathname );
        
    }
    else if( pathname.extension().native() == ".pgm" ){
        
       // output must be in PixelGray_u8
       write_pgm_image( output_image.getResource(), pathname );
    
    }
    else{
        throw GEO::GeneralException(std::string("Unknown extension (")+pathname.extension().native()+")", std::string(__FILE__), __LINE__);
    }

}


} /// End of NETPBM Namespace
} /// End of IO Namespace
} /// End of GEO Namespace


#endif
