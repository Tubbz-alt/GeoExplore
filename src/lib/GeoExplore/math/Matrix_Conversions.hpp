/**
 * @file    Matrix_Conversions.hpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#ifndef __GEOEXPLORE_LIB_MATH_MATRIX_CONVERSIONS_HPP__
#define __GEOEXPLORE_LIB_MATH_MATRIX_CONVERSIONS_HPP__

// GeoExplore Libraries
#include "A_Matrix.hpp"
#include "A_Point.hpp"

namespace GEO{
namespace MATH{

/**
 * Convert a Matrix to a Point
*/
template <typename DataType>
A_Point2<DataType> Convert_Matrix3x1_To_Point2( A_Matrix const& matrix )
{
    // Create output
    return A_Point2<DataType>( matrix(0,0), matrix(1,0));

}



} // End of MATH Namespace
} // End of GEO  Namespace

#endif
