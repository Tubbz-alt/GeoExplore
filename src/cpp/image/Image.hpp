/**
 *    @file    Image.hpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_IMAGETYPE_HPP__
#define __SRC_CPP_IMAGE_IMAGETYPE_HPP__

/// GeoExplore Libraries
#include "../core/A_Size.hpp"
#include "MetadataContainerBase.hpp"


namespace GEO {
namespace IMG{

/**
 * @class Image_
*/
template <typename PixelType, typename ResourceType>
class Image_{

    public: 


        /// define our pixeltype
        typedef PixelType pixeltype;

        
        /// define the datatype
        typedef typename pixeltype::channeltype datatype;

        /**
         * @brief Constructor
        */
        Image_(){

        }


        /**
         * @brief Constructor given initial size.
         *
         * Create an image with a default image size
         *
         * @param[in] rows Image rows.
         * @param[in] cols Image cols.
        */
        Image_( const int& rows, const int& cols )
          : m_resource(rows,cols)
        {
        }


        /**
         * @brief Constructor given initial size.
         *
         * Create an image with the default size.
         *
         * @param[in] image_size Size of image.
         */
        Image_( const A_Size<int>& image_size )
          : m_resource( image_size)
        {
        }
        

        /**
         * @brief Image Constructor given default size and initial value.
         *
         * @param[in] rows Image rows.
         * @param[in] cols Image cols.
         * @param[in] pixel Initial pixel value.
         */
         Image_( const int& rows,
                 const int& cols,
                 const PixelType& pixel )
           : m_resource(rows, cols, pixel)
        {
        }
        

        /**
         * @brief Image Constructor given size and initial value.
         *
         * @param[in] size Image size.
         * @param[in] pixel Initial pixel value.
         */
        Image_( const A_Size<int>& size,
                const PixelType& pixel )
          : m_resource( size, pixel )
        {
        }


        /**
         * @brief Return the number of rows
         *
         * @return row count
        */
        int rows()const{
            return m_resource.rows();
        }

        /**
         * @brief Return the number of columns
         * 
         * @return column count
        */
        int cols()const{
            return m_resource.cols();
        }

        /**
         * @brief Return the number of channels
         * 
         * @return number of channels.
        */
        int channels()const{
            return m_resource.channels();
        }
        
        /**
         * @brief Get the pixel data at the specified index
         *
         * @param[in] index Image position (Row-Major)
         *
         * @returns Pixel value at Image[i]
        */
        PixelType operator[]( const int& idx ){
            return m_resource[idx];
        }
        
        /**
         * Get the pixel value
        */
        PixelType operator()( const int& row, const int& col )const{
            return m_resource(row,col);
        }

        /**
         * Get the pixel reference
        */
        PixelType& operator()( const int& row, const int& col ){
            return m_resource(row,col);
        }

        /**
         * @brief Set the resource information reference to the resource
         *
         * @param[in] resource Resource data to pull data from.
        */
        void setResource( ResourceType const& resource){
            m_resource = resource;
        }
        
        /**
         * @brief Get the resource information
        */
        ResourceType getResource()const{
            return m_resource;
        }


        private:

            /// internal pixel data
            ResourceType  m_resource;    
            
            /// Internal Metadata
            MetadataContainerBase::ptr_t m_metadata;

};  /// End of BaseImage Class

} /// End of namespace IMG
} /// End of namespace GEO

#endif
