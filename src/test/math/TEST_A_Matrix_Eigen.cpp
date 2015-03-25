/**
 * @file    TEST_A_Matrix_Eigen.cpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/math/A_Matrix_Eigen.hpp"

using namespace GEO;

/**
 * Test Matrix Constructors
*/
TEST( A_Matrix_Eigen, Constructor )
{

    // Create matrix
    MATH::A_Matrix_Eigen matrix01;
    ASSERT_EQ( matrix01.Rows(), 0 );
    ASSERT_EQ( matrix01.Cols(), 0 );

    // Create another matrix
    MATH::A_Matrix_Eigen matrix02(1, 4);
    ASSERT_EQ( matrix02.Rows(), 1 );
    ASSERT_EQ( matrix02.Cols(), 4 );

}


/** 
 * Test Matrix Multiplication
*/
TEST( A_Matrix_Eigen, Multiplication_Operator ){

    // Create the first
    FAIL();

}

