/**
 * @file    PixelGray.hpp
 * @author  Marvin Smith
 * @date    5/7/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELGRAY_HPP__
#define __SRC_CPP_IMAGE_PIXELGRAY_HPP__

/// GeoExplore Libraries
#include "ChannelType.hpp"
#include "PixelBase.hpp"


namespace GEO{
namespace IMG{

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
         * @brief Constructor
        */
        PixelGray() 
          :  PixelBase<PixelGray<ChannelType>,ChannelType>(),
             m_data{ channeltype::minValue }
        {
        }
        

        /**
         * @brief Constructor
         *
         * @param[in] gray_value Grayscale values to set.
        */
        PixelGray( datatype const& gray_value ) 
          :  PixelBase<PixelGray<ChannelType>,ChannelType>(),
             m_data{ gray_value } 
        {
        } 
        

        /**
         * @brief Get the gray value.
         *
         * @return Grayscale value.
        */
        virtual datatype val()const{ 
            return m_data; 
        }


        /**
         * @brief Get the grayscale reference.
         *
         * @return Reference to grayscale value.
        */
        virtual datatype& val(){ 
            return m_data; 
        }
    

        /**
         * @brief Get the dimensionality.
         *
         * @return The number of channels or dimensions in channel.
        */
        virtual int Dims()const{ 
            return 1; 
        }
        

        /**
         * @brief Pixel accessor operator.
         *
         * @param[in] idx Index to reference.
         *
         * @return grayscale reference value.
        */
        virtual datatype& operator[]( const int& idx){
            return m_data;
        }
        

        /**
         * @brief Pixel accessor operator.
         *
         * @param[in] idx Index to reference.
         *
         * @return Value of grayscale value.
        */
        virtual datatype operator[](const int& idx)const{
            return m_data;
        }

        /**
         * @brief Compare Pixels
         *
         * @param[in] rhs Pixel to compare.
         *
         * @return True if they are the same, false otherwise.
        */
        virtual bool operator == ( const PixelGray<ChannelType>& rhs )const
        {
            return (m_data == rhs.m_data);
        }


        /**
         * @brief Addition Operator
         *
         * @param[in] other Other pixel to add.
         *
         * @return Sum of this pixel and the other.
        */
        PixelGray<ChannelType> operator + ( const PixelGray<ChannelType>& other )const
        {
            return PixelGray<ChannelType>( m_data + other.m_data);
        }
        
        
        /**
         * @brief Subtraction Operator
         *
         * @param[in] other Other pixel to subtraction.
         *
         * @return Difference of this pixel and the other.
        */
        PixelGray<ChannelType> operator - ( const PixelGray<ChannelType>& other )const
        {
            return PixelGray<ChannelType>( m_data - other.m_data);
        }


        /**
         * @brief Return a black pixel.
         *
         * @return Black pixel
        */
        static PixelGray<ChannelType> Black(){
            return PixelGray<ChannelType>( channeltype::minValue );
        }
        
        /**
         * @brief Return a White pixel.
         *
         * @return White pixel.
        */
        static PixelGray<ChannelType> White(){
            return PixelGray<ChannelType>( channeltype::maxValue );
        }


    private:

        /// Data
        datatype m_data;


}; /// End of PixelGray Class

/// Common Typedefs
typedef PixelGray<ChannelTypeDoubleFree> PixelGrayDoubleFree;
typedef PixelGray<ChannelTypeDoubleFree> PixelGray_df;

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

} // End of IMG Namespace
} // End of GEO Namespace

#endif
