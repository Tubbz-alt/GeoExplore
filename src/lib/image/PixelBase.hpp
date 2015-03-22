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
#include "../core/Exceptions.hpp"

namespace GEO{
namespace IMG{

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
         * @brief Return channel value at specified index.
         *
         * @param[in] idx Index to get.
        */
        virtual typename channeltype::type operator[](const int& idx)const{
            
            throw NotImplementedException("PixelBase operator[]", __FILE__, __LINE__);
            typename channeltype::type value;
            return value;
        }
        

        /**
         * @brief Return the channel reference.
        */
        virtual typename channeltype::type& operator[](const int& idx){
            throw NotImplementedException("PixelBase &operator[]", __FILE__, __LINE__ );
        }

        
        /**
         * @brief Fetch the dimensionality.
         *
         * @return number of channels or dimensions in pixel.
         */
        virtual int Dims()const{ 
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

} // End of IMG Namespace
} // End of GEO Namespace


#endif
