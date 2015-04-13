/**
 * @file    BaseResource.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IMAGE_BASERESOURCE_HPP__
#define __SRC_CPP_IMAGE_BASERESOURCE_HPP__

/// C++ Standard Libraries
#include <memory>

namespace GEO{
namespace IMG{


/**
 * @class BaseResource
 *
 * @brief Base pixel resource driver type.
*/
template <typename PixelType>
class BaseResource{

    public:
        
        /// PixelType
        typedef PixelType pixel_type;


        /// Pointer Type
        typedef std::shared_ptr<BaseResource<PixelType>> ptr_t;


        /**
         * @brief Return the pixel value.
         * 
         * @param[in] idx Index to fetch.
         *
         * @return Pixel value at the position.
        */
        virtual PixelType operator[]( const int& idx )const = 0;


        /**
         * @brief Return the pixel reference.
         *
         * @param[in] idx Index to fetch.
         *
         * @return Reference to pixel at index.
        */
        virtual PixelType& operator[]( const int& idx ) = 0;
        

        /**
         * @brief Return the pixel value.
         *
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         *
         * @return Pixel value at index position.
        */
        virtual PixelType  operator()( const int& row,      
                                       const int& col ) const = 0;


        /**
         * @brief Return the pixel reference.
         *
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         * 
         * @return Reference to pixel at position.
        */
        virtual PixelType& operator()( const int& row,
                                       const int& col ) = 0;
        

        /**
         * @brief Return the number of image rows.
         *
         * @return Image row count.
        */
        virtual int Rows()const = 0;


        /**
         * @brief Return the number of image columns.
         *
         * @return column count
        */
        virtual int Cols()const = 0;
        

        /**
         * @brief Return the number of pixel channels.
         *
         * @return Channel count.
        */
        virtual int Channels()const = 0;


}; // End of BaseResource Class

} // End of IMG Namespace
} // End of GEO Namespace

#endif
