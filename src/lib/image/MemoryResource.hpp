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
        
        /// Pointer Type
        typedef std::shared_ptr<MemoryResource<PixelType>> ptr_t;

        /// Pixel Type
        typedef PixelType pixel_type;

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
         * @brief Get the pixel value at the specified row and column.
         *
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         * 
         * @return Pixel value at the position.
        */
        virtual PixelType operator()( const int& row, 
                                      const int& col )const
        {
            
            /// make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return (*m_data)[m_cols*row + col];
        }

        
        /**
         * Get the pixel reference
        */
        virtual PixelType& operator()( const int& row, 
                                       const int& col )
        {
            
            /// make sure the image has memory initialized
            if( m_data == nullptr ){
                throw MemoryResourceNotInitializedException(__FILE__,__LINE__);
            }
            return (*m_data)[m_cols*row + col];
        }

        /**
         * Return the number of rows
         *
         * @return row count
        */
        virtual int Rows()const{
            return m_rows;
        }

        /**
         * Return the number of columns
         *
         * @return column count
        */
        virtual int Cols()const{
            return m_cols;
        }
        

        /**
         * @brief Return the number of channels in resource.
         *
         * @return Number of channels for resource pixeltype.
        */
        virtual int Channels()const{
            return PixelType().Dims();
        }


        /**
         * @brief Clone (Deep Copy)
        */
        MemoryResource<PixelType> Clone()const{
            
            /// Create the output
            MemoryResource<PixelType> output;

            // copy row and columns
            output.m_rows = Rows();
            output.m_cols = Cols();

            // copy the data
            output.m_data = std::shared_ptr<std::vector<PixelType> >(new std::vector<PixelType>(output.m_rows*output.m_cols));

            for( size_t i=0; i<(Rows()*Cols()); i++ ){
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
                this->m_rows = rhs.Rows();
                this->m_cols = rhs.Cols();

                // copy the memory pointer
                this->m_data = rhs.m_data;

            }

            // return yourself
            return (*this);
        }
        

        /**
         * Assign Pixel Data
        */
        void Set_Pixel_Data( std::shared_ptr<std::vector<PixelType> > const& data, 
                             const int& rows, 
                             const int& cols )
        {
            m_rows = rows;
            m_cols = cols;
            m_data = data;
        }

        
        /**
         * Get pixel data
        */
        std::shared_ptr<std::vector<PixelType> > Get_Pixel_Data()const{
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
