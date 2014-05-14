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
#include <GeoExplore/image/ChannelType.hpp>
#include <GeoExplore/image/Image.hpp>
#include <GeoExplore/image/PixelBase.hpp>
#include <GeoExplore/image/PixelGray.hpp>
#include <GeoExplore/image/PixelRGB.hpp>


namespace GEO{
namespace IO{
namespace NETPBM{

/**
 * Write an RGB Image to PPM File
*/
template<typename PixelType>
void write_image( Image<PixelType>const&  output_image, boost::filesystem::path const& pathname ){

    // select pgm or ppm
    if( pathname.extension().native() == ".ppm" ){
        
        // output must be in PixelRGBu8
        //boost::shared_ptr<PixelRGB<ChannelTypeUInt8> > pixel_data;
        
    }
    else if( pathname.extension().native() == ".pgm" ){
        
        // output must be in PixelGray_u8
        //boost::shared_ptr<PixelGray<ChannelTypeUInt8> > pixel_data = output_image.getResource().getPixelData();

    }
    else{
        throw GEO::GeneralException(std::string("Unknown extension (")+pathname.extension().native()+")", std::string(__FILE__), __LINE__);
    }

}


} /// End of NETPBM Namespace
} /// End of IO Namespace
} /// End of GEO Namespace


#endif
