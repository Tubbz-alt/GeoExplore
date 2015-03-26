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

    // Define EPS
    const double eps = 0.00001;

    // Create the first set of matrices
    MATH::A_Matrix_Eigen matrix01(3,3);
    MATH::A_Matrix_Eigen matrix02(3,3);
    int counter = 1;
    for( int i=0; i<3; i++ )
    for( int j=0; j<3; j++ ){
        matrix01(i,j) = counter;
        matrix02(i,j) = counter;
        counter++;
    }

    // Multiply
    MATH::A_Matrix_Eigen matrix_result_01 = matrix01 * matrix02;

    ASSERT_NEAR( matrix_result_01(0,0), 30, eps );
    ASSERT_NEAR( matrix_result_01(0,1), 36, eps );
    ASSERT_NEAR( matrix_result_01(0,2), 42, eps );
    ASSERT_NEAR( matrix_result_01(1,0), 66, eps );
    ASSERT_NEAR( matrix_result_01(1,1), 81, eps );
    ASSERT_NEAR( matrix_result_01(1,2), 96, eps );
    ASSERT_NEAR( matrix_result_01(2,0),102, eps );
    ASSERT_NEAR( matrix_result_01(2,1),126, eps );
    ASSERT_NEAR( matrix_result_01(2,2),150, eps );

}

