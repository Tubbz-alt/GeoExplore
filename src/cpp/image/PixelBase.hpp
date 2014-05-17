/**
 *    @file    PixelBase.hpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELBASE_HPP__
#define __SRC_CPP_IMAGE_PIXELBASE_HPP__

/// C++ Standard Library
#include <stdexcept>

/// GeoExplore Libraries
#include <GeoExplore/core/Exceptions.hpp>

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
        
        /**
         * Return channel value
        */
        virtual typename channeltype::type operator[](const int& idx)const{
            throw NotImplementedException("PixelBase operator[]", __FILE__, __LINE__);
            typename channeltype::type value;
            return value;
        }
        
        /**
         * Return the channel reference
        */
        virtual typename channeltype::type& operator[](const int& idx){
            throw NotImplementedException("PixelBase &operator[]", __FILE__, __LINE__ );
        }

        /// Dimensionality
        virtual int dims()const{ 
            throw GeneralException("error: PixelBase has no dimensionality.", __FILE__, __LINE__);
        }

        /**
         * Compare the pixel
        */
        virtual bool operator == ( const PixelBase<DerivedType,ChannelType>& rhs )const{
            throw NotImplementedException("PixelBase Comparison Operator (==)", __FILE__,__LINE__);
            return false;
        }

}; /// End of PixelBase Class


} /// End of GEO Namespace


#endif
