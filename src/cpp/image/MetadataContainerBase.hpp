/**
 * @file    MetadataContainerBase.hpp
 * @author  Marvin Smith
 * @date    5/9/2014
*/
#ifndef __SRC_CPP_IMAGE_METADATACONTAINERBASE_HPP__
#define __SRC_CPP_IMAGE_METADATACONTAINERBASE_HPP__

// C++ Standard Libraries
#include <memory>

namespace GEO{
namespace IMG{

/**
 * @class MetadataContainerBase
*/
class MetadataContainerBase{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MetadataContainerBase> ptr_t;

        /**
         * Default Constructor
        */
        MetadataContainerBase();


}; /// End MetadataContainerBase Class

} // End of IMG Namespace
} // End of GEO Namespace

#endif
