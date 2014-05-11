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


        private:

            /// internal pixel data
            ResourceType m_resource;    
            
            /// Internal Metadata
            MetadataContainerBase::ptr_t m_metadata;

};  /// End of BaseImage Class

/// Common Image Aliases
template <typename PixelType> using Image     = Image_<PixelType,MemoryResource<PixelType> >;
template <typename PixelType> using DiskImage = Image_<PixelType,DiskResource<PixelType> >;

} /// End of namespace GEO

#endif
