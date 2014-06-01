/**
 * @file    CoordinateConversionReference.cpp
 * @author  Marvin Smith
 * @date    5/31/2014
*/
#include "CoordinateConversionReference.hpp"

namespace GEO{
namespace GUI{

/**
 * Coordinate Reference Constructor
*/
A_CoordinateReference::A_CoordinateReference() :
                       m_coordinate_type_name("")
{
}

/**
 * Coordinate Reference Constructor
*/
A_CoordinateReference::A_CoordinateReference( const std::string& coordinate_type_name ) :
                       m_coordinate_type_name(coordinate_type_name)
{


}

/**
 * Get the Coordinate Type Name
*/
std::string A_CoordinateReference::Get_Coordinate_Type_Name()const{
    return m_coordinate_type_name;
}

/**
 * Get the Size
*/
size_t The_CoordinateConversionReference::Get_Size()const{
    return m_references.size();
}

/**
 * Get the Coordinate Type Name
*/
std::string The_CoordinateConversionReference::Get_Coordinate_Type_Name( const int& index )const{
    return m_references[index].Get_Coordinate_Type_Name();
}

/**
 * Get Instance of the reference
*/
The_CoordinateConversionReference& The_CoordinateConversionReference::getInstance(){
    static The_CoordinateConversionReference instance;
    return instance;
}

/**
 * Constructor for the ConversionReference
*/
The_CoordinateConversionReference::The_CoordinateConversionReference(){
    
    // initialize
    m_references.push_back( A_CoordinateReference("Geodetic"));
    m_references.push_back( A_CoordinateReference("Universal Transverse Mercator"));

}

} // End of GUI Namespace
} // End of GEO Namespace

