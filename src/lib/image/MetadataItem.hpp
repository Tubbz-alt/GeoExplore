/**
 * @file    MetadataItem.hpp
 * @author  Marvin Smith
 * @date    4/3/2015
*/
#ifndef __GEOEXPLORE_LIB_IMAGE_METADATAITEM_HPP__
#define __GEOEXPLORE_LIB_IMAGE_METADATAITEM_HPP__

// C++ Standard Library
#include <string>

namespace GEO{
namespace IMG{


/**
 * @class MetadataItem
 *
 * @brief Contains a single metadata key/value pair.
*/
class MetadataItem{

    public:
        
        /**
         * @brief MetadataItem Constructor
         */
        MetadataItem();


        /**
         * @brief MetadataItem Constructor given key/value pair.
         *
         * @param[in] key Key value.
         * @param[in] value Value tag.
        */
        MetadataItem( std::string const& key, 
                      std::string const& value );



    private:
        
        /// Key
        std::string m_key;

        /// Value
        std::string m_value;

}; // End of MetadataItem Class


} // End of IMG Namespace
} // End of GEO Namespace

#endif
