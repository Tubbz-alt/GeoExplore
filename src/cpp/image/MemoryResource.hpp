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

/// C++ Standard Library
#include <memory>

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
         * Parameterized Constructor
        */
        MemoryResource( const int& rows, const int& cols ) : m_data(new PixelType[rows*cols]),
                                                             m_rows(rows), m_cols(cols){}

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
         * Get the pixel value
        */
        virtual PixelType operator()( const int& x, const int& y )const{
            
            /// make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return m_data[m_cols*y + x];
        }
        
        /**
         * Get the pixel reference
        */
        virtual PixelType& operator()( const int& x, const int& y ){
            
            /// make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return m_data[m_cols*y + x];
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
        
        /**
         * Clone (Deep Copy)
        */
        MemoryResource<PixelType> clone()const{
            
            /// Create the output
            MemoryResource<PixelType> output;

            // copy row and columns
            output.m_rows = rows();
            output.m_cols = cols();

            // copy the data
            output.m_data = boost::shared_ptr<PixelType[]>(new PixelType[output.m_rows*output.m_cols]);

            for( size_t i=0; i<(rows()*cols()); i++ ){
                output.m_data[i] = m_data[i];
            }

            // return the data
            return output;
        }

        /**
         * Shallow Copy
        */
        MemoryResource<PixelType>& operator= ( const MemoryResource<PixelType>& rhs ){
            
            // protect against self-assignment
            if( this != &rhs ){

                // set the rows and column counts
                this->m_rows = rhs.rows();
                this->m_cols = rhs.cols();

                // copy the memory pointer
                this->m_data = rhs.m_data;

            }

            // return yourself
            return (*this);
        }
        
        /**
         * Assign Pixel Data
        */
        void setPixelData( boost::shared_ptr<PixelType[]> data, const int& rows, const int& cols ){
            m_rows = rows;
            m_cols = cols;
            m_data = data;
        }
        
        /**
         * Get pixel data
        */
        boost::shared_ptr<PixelType[]> getPixelData()const{
            return m_data;
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
