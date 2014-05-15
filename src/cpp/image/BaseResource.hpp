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


/**
 * @class BaseResource
*/
template <typename PixelType>
class BaseResource{

    public:
        

        /**
         * Return the pixel value
        */
        virtual PixelType operator[]( const int& idx )const = 0;

        /**
         * Return the pixel reference
        */
        virtual PixelType& operator[]( const int& idx ) = 0;
        
        /**
         * Return the pixel value
        */
        virtual PixelType  operator()( const int& x, const int& y ) const = 0;

        /**
         * Return the pixel reference
        */
        virtual PixelType& operator()( const int& x, const int& y ) = 0;
        
        /**
         * Return the number of image rows
        */
        virtual int rows()const = 0;

        /**
         * Return the number of image columns
         * @return column count
        */
        virtual int cols()const = 0;
        
        /**
         * Return the number of pixel channels
        */
        virtual int channels()const = 0;

}; /// End of BaseResource Class

} /// End of GEO Namespace

#endif
