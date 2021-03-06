/**
 *    @file    Image.hpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_IMAGETYPE_HPP__
#define __SRC_CPP_IMAGE_IMAGETYPE_HPP__

/// GeoExplore Libraries
#include <GeoExplore/image/BaseResource.hpp>
#include <GeoExplore/image/DiskResource.hpp>
#include <GeoExplore/image/MemoryResource.hpp>
#include <GeoExplore/image/MetadataContainerBase.hpp>


namespace GEO {

/**
 * @class Image
*/
template <typename PixelType, typename ResourceType>
class Image_{

    public: 

        /// define our pixeltype
        typedef PixelType pixeltype;

        
        /// define the datatype
        typedef typename pixeltype::channeltype datatype;

        /**
         * Default Constructor
        */
        Image_(){

        }

        /**
         * Create an image with a default image size
        */
        Image_( const int& rows, const int& cols ) : m_resource(rows,cols){

        }

        /**
         * Return the number of rows
         * @return row count
        */
        int rows()const{
            return m_resource.rows();
        }

        /**
         * Return the number of columns
         * @return column count
        */
        int cols()const{
            return m_resource.cols();
        }

        /**
         * Return the number of channels
        */
        int channels()const{
            return m_resource.channels();
        }
        
        /**
         * Get the pixel data
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
         * Set the resource information reference to the resource
        */
        void setResource( ResourceType const& resource){
            m_resource = resource;
        }
        
        /**
         * Get the resource information
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

/// Common Image Aliases
template <typename PixelType> using Image     = Image_<PixelType,MemoryResource<PixelType> >;
template <typename PixelType> using DiskImage = Image_<PixelType,DiskResource<PixelType> >;

} /// End of namespace GEO

#endif
