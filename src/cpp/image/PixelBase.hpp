/**
 *    @file    PixelBase.hpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELBASE_HPP__
#define __SRC_CPP_IMAGE_PIXELBASE_HPP__

#include <stdexcept>

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
        
        virtual typename channeltype::type operator[](const int& idx)const{
            throw std::runtime_error("error: PixelBase operator[] not implemented.");
            typename channeltype::type value;
            return value;
        }
        
        virtual typename channeltype::type& operator[](const int& idx){
            throw std::runtime_error("error: PixelBase operator[] not implemented.");
        }

        /// Dimensionality
        virtual int dims()const{ 
            throw std::runtime_error("error: PixelBase has no dimensionality.");
        }

}; /// End of PixelBase Class


} /// End of GEO Namespace


#endif
