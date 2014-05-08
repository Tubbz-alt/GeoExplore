/**
 *    @file    PixelRGB.hpp
 *    @author  Marvin Smith
 *    @date    5/7/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELRGB_HPP__
#define __SRC_CPP_IMAGE_PIXELRGB_HPP__

/// GeoExplore Libraries
#include <GeoExplore/image/ChannelType.hpp>
#include <GeoExplore/image/PixelBase.hpp>

namespace GEO{


/**
 * @class PixelRGB
*/
template <typename ChannelType>
class PixelRGB : public PixelBase<PixelRGB<ChannelType>,ChannelType>{

    public:

        /// Define a channeltype
        typedef ChannelType channeltype;
        
        /// Define datatype
        typedef typename ChannelType::type datatype;

        /**
         * Default Constructor
        */
        PixelRGB() : m_data{channeltype::minValue,channeltype::minValue,channeltype::minValue}, 
                     PixelBase<PixelRGB<ChannelType>,ChannelType>(){}
        
        /**
         * Parameterized Constructor
        */
        PixelRGB( datatype const& b ) : 
                        m_data{ b, b, b}, 
                        PixelBase<PixelRGB<ChannelType>,ChannelType>(){}               
        /**
         * Parameterized Constructor
        */
        PixelRGB( datatype const& r, 
                  datatype const& g, 
                  datatype const& b ) : m_data{ r, g, b},
                                        PixelBase<PixelRGB<ChannelType>,ChannelType>(){}
        
        /**
         * Get the red value
        */
        virtual datatype r()const{ 
            return m_data[0]; 
        }

        /**
         * Get the red reference
        */
        virtual datatype& r(){ 
            return m_data[0]; 
        }

        /**
         * Get the green value
        */
        virtual datatype g()const{ 
            return m_data[1]; 
        }

        /**
         * Get the green reference
        */
        virtual datatype& g(){ return m_data[1]; }
        
        /**
         * Get the blue value
        */
        virtual datatype  b()const{ 
            return m_data[2]; 
        }

        /**
         * Get the blue reference
        */
        virtual datatype& b(){ 
            return m_data[2]; 
        }


    private:

        /// Data
        datatype m_data[3];


}; /// End of class PixelRGB

typedef PixelRGB<ChannelTypeDouble>  PixelRGBDouble;
typedef PixelRGB<ChannelTypeDouble>  PixelRGB_Double;

typedef PixelRGB<ChannelTypeUInt8>   PixelRGBUInt8;
typedef PixelRGB<ChannelTypeUInt8>   PixelRGB_UInt8;

typedef PixelRGB<ChannelTypeUInt12>  PixelRGBUInt12;
typedef PixelRGB<ChannelTypeUInt12>  PixelRGB_UInt12;

typedef PixelRGB<ChannelTypeUInt14>  PixelRGBUInt14;
typedef PixelRGB<ChannelTypeUInt14>  PixelRGB_UInt14;

typedef PixelRGB<ChannelTypeUInt16>  PixelRGBUInt16;
typedef PixelRGB<ChannelTypeUInt16>  PixelRGB_UInt16;

typedef PixelRGB<ChannelTypeUInt32>  PixelRGBUInt32;
typedef PixelRGB<ChannelTypeUInt32>  PixelRGB_UInt32;

} /// End of GEO Namespace

#endif
