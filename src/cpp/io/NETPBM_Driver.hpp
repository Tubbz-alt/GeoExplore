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
#include <GeoExplore/image/BaseResource.hpp>
#include <GeoExplore/image/ChannelType.hpp>
#include <GeoExplore/image/Image.hpp>
#include <GeoExplore/image/PixelBase.hpp>
#include <GeoExplore/image/PixelCast.hpp>
#include <GeoExplore/image/PixelGray.hpp>
#include <GeoExplore/image/PixelRGB.hpp>


namespace GEO{
namespace IO{
namespace NETPBM{

/**
 * Write PGM Image
 */
template <typename PixelType>
void write_pgm_image( BaseResource<PixelType> const& data, 
                      boost::filesystem::path const& filename ){

    std::cout << "Write PGM Image" << std::endl;

}


/**
 * Write PPM Image
 */
template <typename PixelType>
void write_ppm_image( BaseResource<PixelType> const& data, 
                      boost::filesystem::path const& filename ){
    
    // create some variables
    int i, j;

    // open file
    FILE *fp = fopen( filename.c_str(), "wb" ); // open in binary mode

    // write data out
    fprintf( fp, "P6\n%d %d\n255\n", data.cols(), data.rows());
    
    unsigned char color[3];
    for( int y=0; y<data.rows(); y++ ){
    for( int x=0; x<data.cols(); x++ ){

        // create the RGB Pixel to convert
        PixelRGB_u8 output = pixel_cast<PixelRGB_u8>(data[y*data.cols() + x]);
        color[0] = output[0];
        color[1] = output[1];
        color[2] = output[2];

        fwrite( color, 1, 3, fp);
    }}
    
    fclose(fp);

}

/**
 * Write an RGB Image to PPM File
*/
template<typename PixelType>
void write_image( Image<PixelType>const&  output_image, boost::filesystem::path const& pathname ){

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
