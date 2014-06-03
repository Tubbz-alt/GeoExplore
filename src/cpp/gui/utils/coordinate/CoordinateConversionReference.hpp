/**
 * @file    CoordinateConversionReference.hpp
 * @author  Marvin Smith
 * @date    5/31/2014
*/
#ifndef __COORDINATECONVERSIONREFERENCE_HPP__
#define __COORDINATECONVERSIONREFERENCE_HPP__

// C++ Standard Library
#include <string>
#include <vector>

// GeoExplore Library
#include <GeoExplore.hpp>

namespace GEO{
namespace GUI{

/**
 * @class A_CoordinateReference
*/
class A_CoordinateReference{

    public:
        
        /**
         * @brief A_CoordinateReference
        */
        A_CoordinateReference();
        
        /**
         * @brief A_CoordinateReference Constructor
        */
        A_CoordinateReference( const CoordinateType& coordinate_type,
                               const std::string& coordinate_type_name );

        /**
         * Get the coordinate type
        */
        CoordinateType Get_Coordinate_Type()const;

        /**
         * @brief Get the Coordinate Type Name
        */
        std::string Get_Coordinate_Type_Name()const;

    private:   
        
        /// Coordinate Type
        CoordinateType m_coordinate_type;
        
        /// Coordinate Type Name
        std::string m_coordinate_type_name;

}; /// End of The_CoordinateReference

/**
 * @class CoordinateConversionReference
*/
class The_CoordinateConversionReference{

    public:
        
        /**
         * @brief Get the Coordinate Type Name
        */
        std::string Get_Coordinate_Type_Name( const int& index )const;
        
        /**
         * @brief Get the coordinate type
        */
        CoordinateType Get_Coordinate_Type( const int& index )const;

        /**
         * @brief Get the Reference Size
        */
        size_t Get_Size()const;

        /**
         * @brief Get Instance
         */
        static The_CoordinateConversionReference& getInstance();

    private:
        
        /**
         * @brief Constructor
        */
        The_CoordinateConversionReference();

        /**
         * @brief Disabled Copy Constructor
        */
        The_CoordinateConversionReference( The_CoordinateConversionReference const& ) = delete;
        
        /**
         * @brief Assignment Operator
        */
        void operator = ( The_CoordinateConversionReference const& ) = delete;

        /// Coordinates
        std::vector<A_CoordinateReference> m_references;

}; /// End of The_CoordinateConversionReference Class


} // End of GUI Namespace
} // End of GEO Namespace

#endif
