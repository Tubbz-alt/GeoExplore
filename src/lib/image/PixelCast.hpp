/**
 * @file    PixelCast.hpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELCAST_HPP__
#define __SRC_CPP_IMAGE_PIXELCAST_HPP__

/// GeoExplore
#include "ChannelType.hpp"
#include "PixelBase.hpp"
#include "Pixel_Types.hpp"

/// C++ Standard Library
#include <type_traits>

namespace GEO{
namespace IMG{

/**
 * Convert Grayscale to Grayscale
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelGray<typename OutputPixelType::channeltype> >::value,PixelGray<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelGray<InputChannelType> const& pixel ){

    return PixelGray<typename OutputPixelType::channeltype>( range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0]));
}


/**
 * Convert Grayscale to RGB
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelRGB<typename OutputPixelType::channeltype> >::value,PixelRGB<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelGray<InputChannelType> const& pixel ){

    return PixelRGB<typename OutputPixelType::channeltype>( range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0]), 
                                                            range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0]),
                                                            range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0]));
}

/**
 * Convert Grayscale to RGBA
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelRGBA<typename OutputPixelType::channeltype> >::value,PixelRGBA<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelGray<InputChannelType> const& pixel ){

    return PixelRGBA<typename OutputPixelType::channeltype>( range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0]), 
                                                             range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0]),
                                                             range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0],
                                                             OutputPixelType::maxValue ));
}

/**
 * Convert RGB to RGBA
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelRGBA<typename OutputPixelType::channeltype> >::value,PixelRGBA<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelRGB<InputChannelType> const& pixel ){
   
    // return the PixelRGB
    return PixelRGBA<typename OutputPixelType::channeltype>( range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[0] ),
                                                             range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[1] ),
                                                             range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[2] ),
                                                             OutputPixelType::channeltype::maxValue );
}


/**
 * Convert RGB to RGB
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelRGB<typename OutputPixelType::channeltype> >::value,PixelRGB<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelRGB<InputChannelType> const& pixel ){
   
    // return the PixelRGB
    return PixelRGB<typename OutputPixelType::channeltype>( range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[0] ),
                                                            range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[1] ),
                                                            range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[2] ));
}
 
 /**
 * Convert RGB to Grayscale
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelGray<typename OutputPixelType::channeltype> >::value,PixelGray<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelRGB<InputChannelType> const& pixel ){
   
    // compute the average using accumulator type
    typename OutputPixelType::channeltype::accumulator_type sum =(range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0])  +
                                                                  range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[1])  +
                                                                  range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[2]));

    typename OutputPixelType::channeltype::type avg = sum / 3;

    // return the gray pixel
    return PixelGray<typename OutputPixelType::channeltype>( avg );
}   


/**
 * Convert RGBA to RGBA
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelRGBA<typename OutputPixelType::channeltype> >::value,PixelRGBA<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelRGBA<InputChannelType> const& pixel ){
   
    // return the PixelRGB
    return PixelRGBA<typename OutputPixelType::channeltype>( range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[0] ),
                                                             range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[1] ),
                                                             range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[2] ),
                                                             OutputPixelType::maxValue );
}


/**
 * Convert RGBA to RGB
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelRGB<typename OutputPixelType::channeltype> >::value,PixelRGB<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelRGBA<InputChannelType> const& pixel ){
   
    // return the PixelRGB
    return PixelRGB<typename OutputPixelType::channeltype>( range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[0] ),
                                                            range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[1] ),
                                                            range_cast<InputChannelType,typename OutputPixelType::channeltype>( pixel[2] ));
}
 
 /**
 * Convert RGBA to Grayscale
*/
template <typename OutputPixelType, typename InputChannelType>
typename std::enable_if<std::is_same<OutputPixelType, PixelGray<typename OutputPixelType::channeltype> >::value,PixelGray<typename OutputPixelType::channeltype> >::type
    pixel_cast( PixelRGBA<InputChannelType> const& pixel ){
   
    // compute the average using accumulator type
    typename OutputPixelType::channeltype::accumulator_type sum =(range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[0])  +
                                                                  range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[1])  +
                                                                  range_cast<InputChannelType,typename OutputPixelType::channeltype>(pixel[2]));

    typename OutputPixelType::channeltype::type avg = sum / 3;

    // return the gray pixel
    return PixelGray<typename OutputPixelType::channeltype>( avg );
}   

} // End of IMG Namespace
} // End of GEO Namespace


#endif
