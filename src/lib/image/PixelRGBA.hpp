/**
 *    @file    PixelRGB.hpp
 *    @author  Marvin Smith
 *    @date    3/20/2015
*/
#ifndef __SRC_CPP_IMAGE_PIXELRGBA_HPP__
#define __SRC_CPP_IMAGE_PIXELRGBA_HPP__

/// GeoExplore Libraries
#include "ChannelType.hpp"
#include "PixelBase.hpp"

namespace GEO{
namespace IMG{

/**
 * @class PixelRGBA
*/
template <typename ChannelType>
class PixelRGBA : public PixelBase<PixelRGBA<ChannelType>,ChannelType>{

    public:

        /// Define a channeltype
        typedef ChannelType channeltype;
        
        /// Define datatype
        typedef typename ChannelType::type datatype;

        /**
         * Constructor
        */
        PixelRGBA() 
            :  PixelBase<PixelRGBA<ChannelType>,ChannelType>(),
               m_data{ channeltype::minValue,
                       channeltype::minValue,
                       channeltype::minValue,
                       channeltype::maxValue } 
        {
        }

        
        /**
         * @brief Constructor given a single gray value. 
         * 
         * @param[in] gray_value Value to set all pixels to.
        */
        PixelRGBA( datatype const& gray_value ) 
          :   PixelBase<PixelRGBA<ChannelType>,ChannelType>(),
              m_data{ gray_value, 
                     gray_value, 
                     gray_value, 
                     channeltype::maxValue }
        {
        }
        
        
        /**
         * @brief Constructor
         * 
         * @param[in] red Red pixel value.
         * @param[in] green Green pixel value.
         * @param[in] blue Blue pixel value.
        */
        PixelRGBA( datatype const& red, 
                   datatype const& green, 
                   datatype const& blue ) 
          :   PixelBase<PixelRGBA<ChannelType>,ChannelType>(),
              m_data{ red, 
                     green, 
                     blue,
                     channeltype::maxValue}
        {
        }
        

        /**
         * @brief Constructor
         *
         * @param[in] red Red pixel value.
         * @param[in] green Green pixel value.
         * @param[in] blue Blue pixel value.
         * @param[in] alpha Alpha channel value.
        */
        PixelRGBA( datatype const& red,
                   datatype const& green,
                   datatype const& blue,
                   datatype const& alpha )
          :  PixelBase<PixelRGBA<ChannelType>,ChannelType>(),
             m_data{ red,
                     green,
                     blue, 
                     alpha }
        {
        }

        
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
         * @brief Get the green reference
         *
         * @return Reference to the green value.
        */
        virtual datatype& g(){ 
            return m_data[1]; 
        }

        
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
         * @brief Get the dimensions of the pixel.
        */
        virtual int Dims()const{ 
            return 4; 
        }


        /**
         * @brief Function Operator
         *
         * @param[in] idx Index of item to get.
         *
         * @return Pixel value at the index.
        */
        virtual datatype& operator[]( const int& idx){
            return m_data[idx];
        }
        

        /**
         * @brief Function Operator
         *
         * @param[in] idx Index of item to get.
         *
         * @return Value at the index.
        */
        virtual datatype operator[](const int& idx)const{
            return m_data[idx];
        }
        

        /**
         * @brief Compare Pixels
         *
         * @param[in] rhs Other pixel to compare.
         *
         * @return True if they are equivalent.
        */
        virtual bool operator == (const PixelRGBA<ChannelType>& rhs )const{
            return ( ( m_data[0] == rhs.m_data[0] ) &&
                     ( m_data[1] == rhs.m_data[1] ) && 
                     ( m_data[2] == rhs.m_data[2] ) &&
                     ( m_data[3] == rhs.m_data[3] ) );
        }

        
        /**
         * @brief Addition Operator
         *
         * @param[in] other Other pixel to add.
         *
         * @return Sum of this pixel and the other.
         */
        PixelRGBA<ChannelType> operator + ( const PixelRGBA<ChannelType>& other )const
        {
            return PixelRGBA<ChannelType>( m_data[0] + other.m_data[0],
                                           m_data[1] + other.m_data[1],
                                           m_data[2] + other.m_data[2],
                                           ChannelType::maxValue );
        }
        
        
        /**
         * @brief Subtraction Operator
         *
         * @param[in] other Other pixel to subtraction.
         *
         * @return Difference of this pixel and the other.
         */
        PixelRGBA<ChannelType> operator - ( const PixelRGBA<ChannelType>& other )const
        {
            return PixelRGBA<ChannelType>( m_data[0] - other.m_data[0],
                                           m_data[1] - other.m_data[1],
                                           m_data[2] - other.m_data[2],
                                           ChannelType::maxValue );
        }


        /**
         * @brief return a black pixel.
         *
         * @return black pixel.
        */
        static PixelRGBA<ChannelType> Black(){
            return PixelRGBA<ChannelType>( ChannelType::minValue,
                                           ChannelType::minValue,
                                           ChannelType::minValue,
                                           ChannelType::maxValue );
        }
        

        /**
         * @brief Return a Red Pixel.
         *
         * @return Red Pixel.
        */
        static PixelRGBA<ChannelType> Red()
        {
            return PixelRGBA<ChannelType>( ChannelType::maxValue,
                                           ChannelType::minValue,
                                           ChannelType::minValue,
                                           ChannelType::maxValue);
        }


        /**
         * @brief Return a Green Pixel.
         *
         * @return Green Pixel.
        */
        static PixelRGBA<ChannelType> Green()
        {
            return PixelRGBA<ChannelType>( ChannelType::minValue,
                                           ChannelType::maxValue,
                                           ChannelType::minValue,
                                           ChannelType::maxValue);
        }

        /**
         * @brief Return a Blue Pixel.
         *
         * @return Blue Pixel.
        */
        static PixelRGBA<ChannelType> Blue()
        {
            return  PixelRGBA<ChannelType>( ChannelType::minValue,
                                            ChannelType::minValue,
                                            ChannelType::maxValue,
                                            ChannelType::maxValue);
        }


        /**
         * @brief Return a white pixel
         *
         * @return White pixel
         */
        static PixelRGBA<ChannelType> White(){
            return PixelRGBA<ChannelType>( ChannelType::maxValue,
                                           ChannelType::maxValue,
                                           ChannelType::maxValue,
                                           ChannelType::maxValue );
        }


    private:

        /// Data
        datatype m_data[4];


}; /// End of class PixelRGBA

typedef PixelRGBA<ChannelTypeDoubleFree> PixelRGBADoubleFree;
typedef PixelRGBA<ChannelTypeDoubleFree> PixelRGBA_df;

typedef PixelRGBA<ChannelTypeDouble>  PixelRGBADouble;
typedef PixelRGBA<ChannelTypeDouble>  PixelRGBA_Double;
typedef PixelRGBA<ChannelTypeDouble>  PixelRGBA_d;

typedef PixelRGBA<ChannelTypeUInt8>   PixelRGBAUInt8;
typedef PixelRGBA<ChannelTypeUInt8>   PixelRGBA_UInt8;
typedef PixelRGBA<ChannelTypeUInt8>   PixelRGBA_u8;

typedef PixelRGBA<ChannelTypeUInt12>  PixelRGBAUInt12;
typedef PixelRGBA<ChannelTypeUInt12>  PixelRGBA_UInt12;
typedef PixelRGBA<ChannelTypeUInt12>  PixelRGBA_u12;

typedef PixelRGBA<ChannelTypeUInt14>  PixelRGBAUInt14;
typedef PixelRGBA<ChannelTypeUInt14>  PixelRGBA_UInt14;
typedef PixelRGBA<ChannelTypeUInt14>  PixelRGBA_u14;

typedef PixelRGBA<ChannelTypeUInt16>  PixelRGBAUInt16;
typedef PixelRGBA<ChannelTypeUInt16>  PixelRGBA_UInt16;
typedef PixelRGBA<ChannelTypeUInt16>  PixelRGBA_u16;

typedef PixelRGBA<ChannelTypeUInt32>  PixelRGBAUInt32;
typedef PixelRGBA<ChannelTypeUInt32>  PixelRGBA_UInt32;
typedef PixelRGBA<ChannelTypeUInt32>  PixelRGBA_u32;

} // End of IMG Namespace
} // End of GEO Namespace

#endif
