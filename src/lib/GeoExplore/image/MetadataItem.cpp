/**
 * @file    MetadataItem.cpp
 * @author  Marvin Smith
 * @date    4/3/2015
*/
#include "MetadataItem.hpp"

// GeoExplore Libraries
#include "../utilities/StringUtilities.hpp"

namespace GEO{
namespace IMG{

/**
 * Constructor
*/
MetadataItem::MetadataItem()
  : m_key(""),
    m_value("")
{
}


/****************************************/
/*            Constructor               */
/****************************************/
MetadataItem::MetadataItem( std::string const& key, 
                            std::string const& value )
  : m_key(key),
    m_value(value)
{
}


/****************************************/
/*            Constructor               */
/****************************************/
MetadataItem::MetadataItem( std::string const& key, 
                            double      const& value )
  : m_key(key),
    m_value(num2str(value, 16))
{
}



} // End of IMG Namespace
} // End of GEO Namespace

