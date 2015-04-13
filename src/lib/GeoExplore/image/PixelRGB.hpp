/**
 *    @file    PixelRGB.hpp
 *    @author  Marvin Smith
 *    @date    5/7/2014
*/
#ifndef __SRC_CPP_IMAGE_PIXELRGB_HPP__
#define __SRC_CPP_IMAGE_PIXELRGB_HPP__

/// GeoExplore Libraries
#include "ChannelType.hpp"
#include "PixelBase.hpp"

namespace GEO{
namespace IMG{

/**
 * @class PixelRGB
 *
 * @brief RGB Pixel Type.
*/
template <typename ChannelType>
class PixelRGB : public PixelBase<PixelRGB<ChannelType>,ChannelType>{

    public:

        /// Define a channeltype
        typedef ChannelType channeltype;
        
        /// Define datatype
        typedef typename ChannelType::type datatype;

        /**
         * @brief Constructor
        */
        PixelRGB() 
          :  PixelBase<PixelRGB<ChannelType>,ChannelType>(),
             m_data{ channeltype::minValue,
                     channeltype::minValue,
                     channeltype::minValue }
        {
        }
        

        /**
         * @brief Constructor
         *
         * @param[in] gray_value Grayscale value to set.
        */
        PixelRGB( datatype const& gray_value ) 
          :  PixelBase<PixelRGB<ChannelType>,ChannelType>(),
             m_data{ gray_value,
                     gray_value,
                     gray_value }
        {
        }
        
        
        /**
         * @brief Constructor
         *
         * @param[in] red Red pixel value.
         * @param[in] green Green pixel value.
         * @param[in] blue Blue pixel value.
        */
        PixelRGB( datatype const& red, 
                  datatype const& green, 
                  datatype const& blue ) 
           :  PixelBase<PixelRGB<ChannelType>,ChannelType>(),
              m_data{ red, 
                      green, 
                      blue }
        {
        }


        /**
         * @brief Get the red value.
         *
         * @return value of the red or 0 position.
        */
        virtual datatype r()const{ 
            return m_data[0]; 
        }

        /**
         * @brief Get the red reference
         *
         * @return Reference to value of the red position.
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

        /**
         * @brief Get the number of channels or dimensions in pixel.
         *
         * @return Dimensionality.
        */
        virtual int Dims()const{ 
            return 3; 
        }

        /**
         * Accessor operator
        */
        virtual datatype& operator[]( const int& idx){
            return m_data[idx];
        }
        
        /**
         * Accessor Operator
        */
        virtual datatype operator[](const int& idx)const{
            return m_data[idx];
        }
        
        /**
         * Compare Pixels
        */
        virtual bool operator == (const PixelRGB<ChannelType>& rhs )const{
            return ( ( m_data[0] == rhs.m_data[0] ) &&
                     ( m_data[1] == rhs.m_data[1] ) && 
                     ( m_data[2] == rhs.m_data[2] ) );
        }

        
        /**
         * @brief Addition Operator
         *
         * @param[in] other Other pixel to add.
         *
         * @return Sum of this pixel and the other.
        */
        PixelRGB<ChannelType> operator + ( const PixelRGB<ChannelType>& other )const
        {
            return PixelRGB<ChannelType>( m_data[0] + other.m_data[0],
                                          m_data[1] + other.m_data[1],
                                          m_data[2] + other.m_data[2] );
        }


        /**
         * @brief Subtraction Operator
         *
         * @param[in] other Other pixel to subtract.
         *
         * @return Difference of this pixel and the other.
        */
        PixelRGB<ChannelType> operator - ( const PixelRGB<ChannelType>& other )const
        {
            return PixelRGB<ChannelType>( m_data[0] - other.m_data[0],
                                          m_data[1] - other.m_data[1],
                                          m_data[2] - other.m_data[2] );
        }


        /**
         * @brief Return a black pixel
         *
         * @return Black pixel
         */
        static PixelRGB<ChannelType> Black(){
            return PixelRGB<ChannelType>( channeltype::minValue,
                                          channeltype::minValue,
                                          channeltype::minValue );
        }
        
        
        /**
         * @brief Return a whiite pixel
         *
         * @return White pixel
         */
        static PixelRGB<ChannelType> White(){
            return PixelRGB<ChannelType>( channeltype::maxValue,
                                          channeltype::maxValue,
                                          channeltype::maxValue );
        }
        
        
        /**
         * @brief Return a Red Pixel
         *
         * @return Red Pixel.
        */
        static PixelRGB<ChannelType> Red(){
            return PixelRGB<ChannelType>( channeltype::maxValue,
                                          channeltype::minValue,
                                          channeltype::minValue );
        }
        
        
        /**
         * @brief Return a Green Pixel
         *
         * @return Green Pixel.
        */
        static PixelRGB<ChannelType> Green(){
            return PixelRGB<ChannelType>( channeltype::minValue,
                                          channeltype::maxValue,
                                          channeltype::minValue );
        }


        /**
         * @brief Return a Blue Pixel.
         *
         * @return Blue Pixel.
        */
        static PixelRGB<ChannelType> Blue(){
            return PixelRGB<ChannelType>( channeltype::minValue,
                                          channeltype::minValue,
                                          channeltype::maxValue );
        }

        
        /**
         * @brief Print Pretty String
         *
         * @return Pretty String
        */
        std::string ToPrettyString()const{
            std::stringstream sin;
            sin << "PixelRGB<" << channeltype::ToPrettyString() << ">( ";
            sin << (int)m_data[0] << ", ";
            sin << (int)m_data[1] << ", "; 
            sin << (int)m_data[2] << ")";
            return sin.str();
        }

    private:

        /// Data
        datatype m_data[3];


}; /// End of class PixelRGB

typedef PixelRGB<ChannelTypeDoubleFree> PixelRGBDoubleFree;
typedef PixelRGB<ChannelTypeDoubleFree> PixelRGB_df;

typedef PixelRGB<ChannelTypeDouble>  PixelRGBDouble;
typedef PixelRGB<ChannelTypeDouble>  PixelRGB_Double;
typedef PixelRGB<ChannelTypeDouble>  PixelRGB_d;

typedef PixelRGB<ChannelTypeUInt8>   PixelRGBUInt8;
typedef PixelRGB<ChannelTypeUInt8>   PixelRGB_UInt8;
typedef PixelRGB<ChannelTypeUInt8>   PixelRGB_u8;

typedef PixelRGB<ChannelTypeUInt12>  PixelRGBUInt12;
typedef PixelRGB<ChannelTypeUInt12>  PixelRGB_UInt12;
typedef PixelRGB<ChannelTypeUInt12>  PixelRGB_u12;

typedef PixelRGB<ChannelTypeUInt14>  PixelRGBUInt14;
typedef PixelRGB<ChannelTypeUInt14>  PixelRGB_UInt14;
typedef PixelRGB<ChannelTypeUInt14>  PixelRGB_u14;

typedef PixelRGB<ChannelTypeUInt16>  PixelRGBUInt16;
typedef PixelRGB<ChannelTypeUInt16>  PixelRGB_UInt16;
typedef PixelRGB<ChannelTypeUInt16>  PixelRGB_u16;

typedef PixelRGB<ChannelTypeUInt32>  PixelRGBUInt32;
typedef PixelRGB<ChannelTypeUInt32>  PixelRGB_UInt32;
typedef PixelRGB<ChannelTypeUInt32>  PixelRGB_u32;

} // End of IMG Namespace
} // End of GEO Namespace

#endif
