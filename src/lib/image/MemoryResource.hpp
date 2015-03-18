/**
 * @file    MemoryResource.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_IMAGE_MEMORYRESOURCE_HPP__
#define __SRC_CPP_IMAGE_MEMORYRESOURCE_HPP__

/// GeoExplore Libraries
#include "../core/A_Size.hpp"
#include "../core/Exceptions.hpp"
#include "BaseResource.hpp"
#include "Image.hpp"


/// C++ Standard Library
#include <cstddef>
#include <memory>

namespace GEO{
namespace IMG{

/**
 * @class MemoryResource
*/
template <typename PixelType>
class MemoryResource : public BaseResource<PixelType> {

    public:
        
        /**
         * @brief Constructor
        */
        MemoryResource()
            : m_data(nullptr), 
              m_rows(0), 
              m_cols(0)
        {
        }
        

        /**
         * @brief Constructor given default size info.
        */
        MemoryResource( const int& rows, const int& cols ) 
          : m_data(new std::vector<PixelType>(rows*cols)),
            m_rows(rows), 
            m_cols(cols)
        {
        }


        /**
         * @brief Constructor given size info
         * 
         * @param[in] size.
         */
        MemoryResource( const A_Size<int>& size )
          : m_data( new std::vector<PixelType>( size.Width() * size.Height() )),
            m_rows(size.Height()),
            m_cols(size.Width())
        {
        }


        /**
         * @brief Constructor given default size and pixel value.
         *
         * @param[in] rows Image resource rows.
         * @param[in] cols Image resource cols.
         * @param[in] pixel Initial pixel value.
        */
        MemoryResource( const int& rows, 
                        const int& cols, 
                        PixelType const& pixel )
          : m_data(new std::vector<PixelType>(rows*cols, pixel)),
            m_rows(rows),
            m_cols(cols)
        {
        }


        /**
         * @brief Constructor given default size and pixel value
         *
         * @param[in] image_size Size in pixels.
         * @param[in] pixel Initial pixel value.
         */
        MemoryResource( const A_Size<int>& image_size,
                        const PixelType&   pixel )
            : m_data(new std::vector<PixelType>(image_size.Width() * image_size.Height())),
              m_rows(image_size.Height()),
              m_cols(image_size.Width())
        {
        }


        /**
         * @brief Get the pixel value
         *
         * @param[in] idx Image pixel location (row-major).
         *
         * @return Pixel at index.
        */
        virtual PixelType operator[]( const int& idx )const
        {
            // make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return (*m_data)[idx];
        }


        /**
         * @brief Get the pixel reference
         *
         * @param[in] idx Index to image position.
         *
         * @return Image pixel reference.
        */
        virtual PixelType& operator[]( const int& idx ){
            
            // make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return (*m_data)[idx];
        }
        
        /**
         * Get the pixel value
        */
        virtual PixelType operator()( const int& x, const int& y )const{
            
            /// make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return (*m_data)[m_cols*y + x];
        }
        
        /**
         * Get the pixel reference
        */
        virtual PixelType& operator()( const int& x, const int& y ){
            
            /// make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return (*m_data)[m_cols*y + x];
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
         * Return the number of channels
        */
        virtual int channels()const{
            return PixelType().dims();
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
            output.m_data = std::shared_ptr<std::vector<PixelType> >(new std::vector<PixelType>(output.m_rows*output.m_cols));

            for( size_t i=0; i<(rows()*cols()); i++ ){
                (*output.m_data)[i] = (*m_data)[i];
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
        void setPixelData( std::shared_ptr<std::vector<PixelType> > const& data, const int& rows, const int& cols ){
            m_rows = rows;
            m_cols = cols;
            m_data = data;
        }
        
        /**
         * Get pixel data
        */
        std::shared_ptr<std::vector<PixelType> > getPixelData()const{
            return m_data;
        }

    private:

        /// List of pixels
        std::shared_ptr<std::vector<PixelType> >  m_data;

        /// number of rows
        int m_rows;

        /// number of columns
        int m_cols;

}; /// End of MemoryResource Class

// Define our typedef alias'
template <typename PixelType> using Image = Image_<PixelType,GEO::IMG::MemoryResource<PixelType> >;

} /// End of IMG Namespace
} /// End of GEO Namespace

#endif
