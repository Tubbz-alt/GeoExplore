/**
 * @file    MetadataItem.hpp
 * @author  Marvin Smith
 * @date    4/3/2015
*/
#ifndef __GEOEXPLORE_LIB_IMAGE_METADATAITEM_HPP__
#define __GEOEXPLORE_LIB_IMAGE_METADATAITEM_HPP__

// C++ Standard Library
#include <string>
#include <type_traits>

// GeoExplore Libraries
#include "../utilities/StringUtilities.hpp"

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
        
        
        /**
         * @brief MetadataItem Constructor given key/value pair.
         *
         * @param[in] key Key value.
         * @param[in] value Value tag.
        */
        MetadataItem( std::string const&  key, 
                      double      const&  value );

        
        /**
         * @brief Get the Key Value
         *
         * @return Key Value.
         */
        inline std::string Key()const{
            return m_key;
        }


        /**
         * @brief Get the Value.
         *
         * @return Value.
         */
        template <typename ValueType>
        typename std::enable_if<std::is_same<ValueType,std::string>::value, std::string>::type
            Value()const{
            return m_value;
        }
        
        
        /**
         * @brief Get the Value.
         *
         * @return Value.
         */
        template <typename ValueType>
        typename std::enable_if<std::is_arithmetic<ValueType>::value,ValueType>::type
            Value()const{
            return str2num<ValueType>(m_value);
        }
        

    private:
        
        /// Key
        std::string m_key;

        /// Value
        std::string m_value;

}; // End of MetadataItem Class


} // End of IMG Namespace
} // End of GEO Namespace

#endif
