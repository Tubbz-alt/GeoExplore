/**
 *    @file    Image.hpp
 *    @author  Marvin Smith
 *    @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_IMAGETYPE_HPP__
#define __SRC_CPP_IMAGE_IMAGETYPE_HPP__

/// GeoExplore Libraries
#include <GeoExplore/image/BaseResource.hpp>
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


        private:

            /// internal pixel data
            BaseResource<PixelType> m_resource;    
            
            /// Internal Metadata
            MetadataContainerBase::ptr_t m_metadata;

};  /// End of BaseImage Class

} /// End of namespace GEO

#endif
