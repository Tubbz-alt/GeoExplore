/**
 * @file    MetadataContainer.hpp
 * @author  Marvin Smith
 * @date    5/9/2014
*/
#ifndef __SRC_CPP_IMAGE_METADATACONTAINER_HPP__
#define __SRC_CPP_IMAGE_METADATACONTAINER_HPP__

// GeoExplore Libraries
#include "MetadataContainerBase.hpp"
#include "MetadataItem.hpp"

// C++ Standard Libraries
#include <memory>
#include <vector>

namespace GEO{
namespace IMG{

/**
 * @class MetadataContainer
*/
class MetadataContainer : public MetadataContainerBase{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MetadataContainer> ptr_t;

        /** 
         * Default Constructor
        */
        MetadataContainer();
    
        
        /**
         * @brief Add a single metadata entry.
         */
        void Add_Metadata_Entry( const std::string& key,
                                 const std::string& value );

    private:
        
        /// Metadata Container
        std::vector<MetadataItem> m_metadata_list;

}; /// End of MetadataContainer Class

} // End of Namespace IMG
} // End of Namespace GEO

#endif
