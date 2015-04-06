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


/*********************************************/
/*              Clear the Container          */
/*********************************************/
void MetadataContainer::Clear()
{
    m_metadata_list.clear();
}

} /// End of IMG Namespace
} /// End of GEO Namespace

