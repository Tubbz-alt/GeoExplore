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
 * Test the Operators
*/
TEST( A_Matrix_Eigen, Accessors ){

    MATH::A_Matrix_Eigen matrix(3,3);

    // Test the setters
    int counter = 0;
    for( int i=0; i<3; i++ ){
    for( int j=0; j<3; j++ ){
        matrix(i,j) = counter++;
    }}

    // Check values
    for( int i=0; i<9; i++ )
        ASSERT_NEAR( matrix[i], i, 0.0001 );
    
    // Set new values
    for( int i=0; i<9; i++ )
        matrix[i] = -i;


    counter = 0;
    for( int i=0; i<3; i++ )
    for( int j=0; j<3; j++ )
        ASSERT_NEAR( matrix(i,j), counter--, 0.0001 );

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

/******************************************************/
/*             Test the Transpose Function            */
/******************************************************/
TEST( A_Matrix_Eigen, Transpose )
{

    // Eps
    const double eps = 0.0001;

    // Test 01 ( Empty Matrix )
    MATH::A_Matrix_Eigen test01;
    MATH::A_Matrix_Eigen trans01 = test01.Transpose();
    ASSERT_EQ( trans01.Rows(), 0 );
    ASSERT_EQ( trans01.Cols(), 0 );

    // Test 02 ( NxN matrix )
    MATH::A_Matrix_Eigen test02(3,3);
    for( int i=0; i<9; i++ ){ test02[i] = i+1; }

    MATH::A_Matrix_Eigen trans02 = test02.Transpose();
    ASSERT_EQ( trans02.Rows(), 3 );
    ASSERT_EQ( trans02.Cols(), 3 );
    
    // Test 03 ( NxM matrix N>M)
    MATH::A_Matrix_Eigen test03(4,3);
    for( int i=0; i<12; i++ ){ test03[i] = i+1; }

    MATH::A_Matrix_Eigen trans03 = test03.Transpose();
    ASSERT_EQ( trans03.Rows(), 3 );
    ASSERT_EQ( trans03.Cols(), 4 );
    for( int i=0; i<4; i++ )
    for( int j=0; j<3; j++ )
        ASSERT_NEAR( trans03(j,i), test03(i,j), eps );

    // Test 04 ( NxM matrix N<M)
    MATH::A_Matrix_Eigen test04(3,4);
    for( int i=0; i<12; i++ ){ test04[i] = i+1; }

    MATH::A_Matrix_Eigen trans04 = test04.Transpose();
    ASSERT_EQ( trans04.Rows(), 4 );
    ASSERT_EQ( trans04.Cols(), 3 );
    for( int i=0; i<4; i++ )
    for( int j=0; j<3; j++ )
        ASSERT_NEAR( trans04(i,j), test04(j,i), eps );

}

/******************************************************/
/*             Test the Inverse Function              */
/******************************************************/
TEST( A_Matrix_Eigen, Inverse )
{
    // EPS
    const double eps = 0.0001;

    // TEST 01 (Simple Matrix)
    MATH::A_Matrix_Eigen test01(3,3);
    for( int i=0; i<9; i++ ){  test01[i] = i+1; }
        
    MATH::A_Matrix_Eigen inv01 = test01.Inverse();
    ASSERT_EQ( inv01.Rows(), 3 );
    ASSERT_EQ( inv01.Cols(), 3 );
    ASSERT_NEAR( inv01(0,0), -0.63889, eps );
    ASSERT_NEAR( inv01(0,1), -0.16667, eps );
    ASSERT_NEAR( inv01(0,2),  0.30556, eps );
    ASSERT_NEAR( inv01(1,0), -0.05556, eps );
    ASSERT_NEAR( inv01(1,1),  0,       eps );
    ASSERT_NEAR( inv01(1,2),  0.05556, eps );
    ASSERT_NEAR( inv01(2,0),  0.52778, eps );
    ASSERT_NEAR( inv01(2,1),  0.16667, eps );
    ASSERT_NEAR( inv01(2,2), -0.19444, eps );

    // Test 02 (4x3)
    MATH::A_Matrix_Eigen test02(4,3);
    for( int i=0; i<12; i++ ){
        test02[i] = i+1;
    }

    // Check results
    MATH::A_Matrix_Eigen inv02 = test02.Inverse();
    ASSERT_EQ( inv02.Rows(), 3);
    ASSERT_EQ( inv02.Cols(), 4);
    ASSERT_NEAR( inv02(0,0), -0.48333, eps );
    ASSERT_NEAR( inv02(0,1), -0.24444, eps );
    ASSERT_NEAR( inv02(0,2), -0.00556, eps );
    ASSERT_NEAR( inv02(0,3),  0.23333, eps );
    ASSERT_NEAR( inv02(1,0), -0.03333, eps );
    ASSERT_NEAR( inv02(1,1), -0.01111, eps );
    ASSERT_NEAR( inv02(1,2),  0.01111, eps );
    ASSERT_NEAR( inv02(1,3),  0.03333, eps );
    ASSERT_NEAR( inv02(2,0),  0.41667, eps );
    ASSERT_NEAR( inv02(2,1),  0.22222, eps );
    ASSERT_NEAR( inv02(2,2),  0.02778, eps );
    ASSERT_NEAR( inv02(2,3), -0.16667, eps );
}


