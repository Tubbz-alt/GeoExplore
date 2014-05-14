/**
 * @file    PixelGray.hpp
 * @author  Marvin Smith
 * @date    5/7/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELGRAY_HPP__
#define __SRC_CPP_IMAGE_PIXELGRAY_HPP__

/// GeoExplore Libraries
#include <GeoExplore/image/ChannelType.hpp>
#include <GeoExplore/image/PixelBase.hpp>


namespace GEO{

/**
 * @class PixelGray
*/
template <typename ChannelType>
class PixelGray : public PixelBase<PixelGray<ChannelType>,ChannelType>{

    public:
        
        /// Define a channeltype
        typedef ChannelType channeltype;
        
        /// Define datatype
        typedef typename ChannelType::type datatype;
    
        /**
         * Default Constructor
        */
        PixelGray() : m_data{channeltype::minValue}, 
                     PixelBase<PixelGray<ChannelType>,ChannelType>(){}
        
        /**
         * Parameterized Constructor
        */
        PixelGray( datatype const& b ) : 
                           m_data{ b }, 
                           PixelBase<PixelGray<ChannelType>,ChannelType>(){} 
        

        /**
         * Get the red value
        */
        virtual datatype val()const{ 
            return m_data; 
        }

        /**
         * Get the red reference
        */
        virtual datatype& val(){ 
            return m_data; 
        }
    
        /// return the dimensionality
        virtual int dims()const{ return 1; }
        
        /**
         * Accessor operator
        */
        virtual datatype& operator[]( const int& idx){
            return m_data;
        }
        
        /**
         * Accessor Operator
        */
        virtual datatype operator[](const int& idx)const{
            return m_data;
        }

        /**
         * Compare Pixel
        */
        virtual bool operator == ( const PixelGray<ChannelType>& rhs )const{
            return (m_data == rhs.m_data);
        }


    private:

        /// Data
        datatype m_data;


}; /// End of PixelGray Class

/// Common Typedefs
typedef PixelGray<ChannelTypeDouble>  PixelGrayDouble;
typedef PixelGray<ChannelTypeDouble>  PixelGray_Double;
typedef PixelGray<ChannelTypeDouble>  PixelGray_d;

typedef PixelGray<ChannelTypeUInt8>   PixelGrayUInt8;
typedef PixelGray<ChannelTypeUInt8>   PixelGray_UInt8;
typedef PixelGray<ChannelTypeUInt8>   PixelGray_u8;

typedef PixelGray<ChannelTypeUInt12>  PixelGrayUInt12;
typedef PixelGray<ChannelTypeUInt12>  PixelGray_UInt12;
typedef PixelGray<ChannelTypeUInt12>  PixelGray_u12;

typedef PixelGray<ChannelTypeUInt14>  PixelGrayUInt14;
typedef PixelGray<ChannelTypeUInt14>  PixelGray_UInt14;
typedef PixelGray<ChannelTypeUInt14>  PixelGray_u14;

typedef PixelGray<ChannelTypeUInt16>  PixelGrayUInt16;
typedef PixelGray<ChannelTypeUInt16>  PixelGray_UInt16;
typedef PixelGray<ChannelTypeUInt16>  PixelGray_u16;

typedef PixelGray<ChannelTypeUInt32>  PixelGrayUInt32;
typedef PixelGray<ChannelTypeUInt32>  PixelGray_UInt32;
typedef PixelGray<ChannelTypeUInt32>  PixelGray_u32;


} /// End of GEO Namespace

#endif
