/**
 * @file    MemoryResource.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IMAGE_MEMORYRESOURCE_HPP__
#define __SRC_CPP_IMAGE_MEMORYRESOURCE_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Exceptions.hpp>
#include <GeoExplore/image/BaseResource.hpp>

/// Boost C++ Library
#include <boost/shared_ptr.hpp>

namespace GEO{

/**
 * @class MemoryResource
*/
template <typename PixelType>
class MemoryResource : public BaseResource<PixelType> {

    public:
        
        /**
         * Default Constructor
        */
        MemoryResource() : m_data(nullptr), m_rows(0), m_cols(0){

        }

        /**
         * Get the pixel value
        */
        virtual PixelType operator[]( const int& idx )const{
            
            // make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return m_data[idx];
        }

        /**
         * Get the pixel reference
        */
        virtual PixelType& operator[]( const int& idx ){
            // make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return m_data[idx];
        }
        
        /**
         * Return the number of rows
         *
         * @return row count
        */
        virtual int rows()const{
            return m_rows;
        }

        /**
         * Return the number of columns
         *
         * @return column count
        */
        virtual int cols()const{
            return m_cols;
        }


    private:

        /// List of pixels
        boost::shared_ptr<PixelType[]> m_data;
        
        /// number of rows
        int m_rows;

        /// number of columns
        int m_cols;

}; /// End of MemoryResource Class

} /// End of GEO Namespace

#endif
