/**
 *    @file    PixelBase.hpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELBASE_HPP__
#define __SRC_CPP_IMAGE_PIXELBASE_HPP__

namespace GEO{

/**
 *    @class PixelBase
 *    @brief  Base class for pixels.
 *     In GeoExplore,  images have pixels, whose datatypes are
 *     defined as a channel.  Use OpenCV or NASA Vision Workbench 
 *     as a reference. 
*/
template <typename DerivedType, typename ChannelType>
class PixelBase {

    public:
        
        /// Define a channeltype
        typedef ChannelType channeltype;

        /**
         * Default Constructor
        */
        PixelBase(){}


}; /// End of PixelBase Class


} /// End of GEO Namespace


#endif
