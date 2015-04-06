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
         *
         * @param[in] key Key to add.
         * @param[in] value Value to add.
         */
         template <typename ValueType>
        void Add_Metadata_Entry( const std::string& key,
                                 const ValueType&   value )
        {
            m_metadata_list.push_back(MetadataItem(key,value));
        }


        /**
         * @brief Query for a Metadata Key/Value Pair.
         *
         * @param[in]  key Desired key to query.
         * @param[out] value Value if present.
         *
         * @return True if found, false otherwise.
         */
        template <typename ValueType>
        bool Query_Metadata( const std::string& key,
                             ValueType&         value )const
        {
            // Iterate over key pairs
            for( int i=0; i<(int)m_metadata_list.size(); i++ )
            {
                if( m_metadata_list[i].Key() == key ){
                    value = m_metadata_list[i].Value<ValueType>();
                    return true;
                }
            }
            return false;
        }


        /**
         * @brief Get the Metadata List.
         *
         * @return Metadata List.
         */
        inline std::vector<MetadataItem> Get_Metadata_List()const{
            return m_metadata_list;
        }

    private:
        
        /// Metadata Container
        std::vector<MetadataItem> m_metadata_list;

}; /// End of MetadataContainer Class

} // End of Namespace IMG
} // End of Namespace GEO

#endif
