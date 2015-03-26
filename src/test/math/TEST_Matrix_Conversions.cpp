/**
 * @file    TEST_Matrix_Conversions.cpp
 * @author  Marvin Smith
 * @date    3/25/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/math/Matrix_Conversions.hpp"

using namespace GEO;

/** 
 * Test Converting Matricies to Poitns
*/
TEST( Matrix_Utilities, Convert_Matrix3x1_To_Point2 ){

    // Create matrix
    MATH::A_Matrix matrix01(3,1);
    matrix01(0,0) = 2;
    matrix01(1,0) = 1;
    matrix01(2,0) =-1;

    // Convert to points
    MATH::A_Point2d point01 = MATH::Convert_Matrix3x1_To_Point2<double>( matrix01 );
    MATH::A_Point2i point02 = MATH::Convert_Matrix3x1_To_Point2<int>( matrix01 );

    ASSERT_NEAR( point01[0], 2, 0.0001 );
    ASSERT_NEAR( point01[1], 1, 0.0001 );

    ASSERT_EQ( point02[0], 2 );
    ASSERT_EQ( point02[1], 1 );
}
