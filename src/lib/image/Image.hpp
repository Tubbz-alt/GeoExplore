/**
 *    @file    Image.hpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_IMAGETYPE_HPP__
#define __SRC_CPP_IMAGE_IMAGETYPE_HPP__

/// GeoExplore Libraries
#include "../core/A_Size.hpp"
#include "../math/A_Point.hpp"
#include "MetadataContainerBase.hpp"


namespace GEO{
namespace IMG{

/**
 * @class Image_
*/
template <typename PixelType, typename ResourceType>
class Image_{

    public: 
        
        /// Pointer Type
        typedef std::shared_ptr<Image_<PixelType,ResourceType>> ptr_t;

        /// define our pixeltype
        typedef PixelType pixeltype;

        
        /// define the datatype
        typedef typename pixeltype::channeltype datatype;

        /**
         * @brief Constructor
        */
        Image_()
        {
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
        int Rows()const{
            return m_resource.Rows();
        }

        /**
         * @brief Return the number of columns
         * 
         * @return column count
        */
        int Cols()const{
            return m_resource.Cols();
        }

        /**
         * @brief Return the number of channels
         * 
         * @return number of channels.
        */
        int Channels()const{
            return m_resource.Channels();
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
         * @brief Get the pixel value.
         * 
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         *
         * @return Pixel value at location.
        */
        PixelType operator()( const int& row, 
                              const int& col )const
        {
            return m_resource(row,col);
        }


        /**
         * @brief Get the pixel reference.
         *
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         * 
         * @return Reference to pixel data value.
        */
        PixelType& operator()( const int& row, 
                               const int& col )
        {
            return m_resource(row,col);
        }
        
        
        /**
         * @brief Get the pixel value.
         * 
         * @param[in] point Position to fetch.
         *
         * @return Pixel value at location.
        */
        PixelType operator()( MATH::A_Point2i const& point )const
        {
            return m_resource(point.y(), point.x());
        }


        /**
         * @brief Get the pixel reference.
         *
         * @param[in] point Position to fetch.
         * 
         * @return Reference to pixel data value.
        */
        PixelType& operator()( MATH::A_Point2i const& point ){
            return m_resource(point.y(), point.x());
        }


        /**
         * @brief Set the resource information reference to the resource
         *
         * @param[in] resource Resource data to pull data from.
        */
        void Set_Resource( typename ResourceType::ptr_t const& resource)
        {
            if( resource != nullptr ){
                m_resource = *resource;
            }
        }
        
        /**
         * @brief Get the resource information
        */
        ResourceType Get_Resource()const{
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
