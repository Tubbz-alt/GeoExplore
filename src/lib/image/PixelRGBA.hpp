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
            : m_data{ channeltype::minValue,
                      channeltype::minValue,
                      channeltype::minValue,
                      channeltype::minValue }, 
              PixelBase<PixelRGBA<ChannelType>,ChannelType>()
        {
        }

        
        /**
         * @brief Constructor given a single gray value. 
         * 
         * @param[in] gray_value Value to set all pixels to.
        */
        PixelRGBA( datatype const& gray_value ) 
          :  m_data{ gray_value, 
                     gray_value, 
                     gray_value, 
                     channeltype::maxValue },
             PixelBase<PixelRGBA<ChannelType>,ChannelType>(){}               
        
        
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
          :  m_data{ red, 
                     green, 
                     blue,
                     channeltype::maxValue},
              PixelBase<PixelRGBA<ChannelType>,ChannelType>()
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
          :  m_data{ red,
                     green,
                     blue, 
                     alpha },
             PixelBase<PixelRGBA<ChannelType>,ChannelType>()
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

        /// return the dimensionality
        virtual int dims()const{ 
            return 3; 
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


    private:

        /// Data
        datatype m_data[4];


}; /// End of class PixelRGBA

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
