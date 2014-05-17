/**
 * @file    MetadataContainerBase.hpp
 * @author  Marvin Smith
 * @date    5/9/2014
*/
#ifndef __SRC_CPP_IMAGE_METADATACONTAINERBASE_HPP__
#define __SRC_CPP_IMAGE_METADATACONTAINERBASE_HPP__

/// Boost C++ Library
#include <boost/shared_ptr.hpp>

namespace GEO{

/**
 * @class MetadataContainerBase
*/
class MetadataContainerBase{

    public:
        
        /// Pointer Type
        typedef boost::shared_ptr<MetadataContainerBase> ptr_t;

        /**
         * Default Constructor
        */
        MetadataContainerBase();


}; /// End MetadataContainerBase Class

} /// End of GEO Namespace

#endif
