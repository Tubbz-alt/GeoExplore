/**
 * @file    MetadataContainer.cpp
 * @author  Marvin Smith
 * @date    5/9/2014
*/
#include "MetadataContainer.hpp"

namespace GEO{
namespace IMG{

/**
 * Default Constructor
*/
MetadataContainer::MetadataContainer(){


}

/**
 * Add Metadata Entry
*/
void MetadataContainer::Add_Metadata_Entry( const std::string& key,
                                            const std::string& value )
{
    m_metadata_list.push_back(MetadataItem(key,value));
}

} /// End of IMG Namespace
} /// End of GEO Namespace

