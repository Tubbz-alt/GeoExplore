/**
 * @file    PixelCast.hpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELCAST_HPP__
#define __SRC_CPP_IMAGE_PIXELCAST_HPP__

/// GeoExplore
#include <GeoExplore/image/ChannelType.hpp>
#include <GeoExplore/image/PixelBase.hpp>
#include <GeoExplore/image/PixelGray.hpp>
#include <GeoExplore/image/PixelRGB.hpp>


namespace GEO{

/**
 * Convert Grayscale to RGB
*/
template <typename OutputChannelType, typename InputChannelType>
PixelRGB<OutputChannelType> pixel_cast( PixelGray<InputChannelType> const& pixel ){
    return PixelRGB<OutputChannelType>( range_cast<InputChannelType,OutputChannelType>(pixel[0]), 
                                        range_cast<InputChannelType,OutputChannelType>(pixel[0]),
                                        range_cast<InputChannelType,OutputChannelType>(pixel[0]));
}

/**
 * Convert RGB to Grayscale
*/
template <typename OutputChannelType, typename InputChannelType>
PixelGray<OutputChannelType> pixel_cast( PixelRGB<InputChannelType> const& pixel ){

    // compute the average using accumulator type
    typename OutputChannelType::accumulator_type sum =(range_cast<InputChannelType,OutputChannelType>(pixel[0])  +
                                                       range_cast<InputChannelType,OutputChannelType>(pixel[1])  +
                                                       range_cast<InputChannelType,OutputChannelType>(pixel[2]));

    typename OutputChannelType::type avg = sum / 3;
    
    // return the grayscale pixel
    return PixelGray<OutputChannelType>(avg);
}
    

} /// End of GEO Namespace


#endif
