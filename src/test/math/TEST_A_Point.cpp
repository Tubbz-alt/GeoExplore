/**
 * @file    TEST_A_Point.cpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/math/A_Point.hpp>

using namespace GEO;

/**
 * Test the Default Constructors
*/
TEST( A_Point, Constructor_Default ){

    // Create some points
    MATH::A_Point2d point_2d_01;
    MATH::A_Point2f point_2f_01;
    MATH::A_Point2i point_2i_01;
    MATH::A_Point2s point_2s_01;
    MATH::A_Point2s point_2u_01;
    
    MATH::A_Point3d point_3d_01;
    MATH::A_Point3f point_3f_01;
    MATH::A_Point3i point_3i_01;
    MATH::A_Point3s point_3s_01;
    MATH::A_Point3s point_3u_01;

    // Check the dims
    ASSERT_EQ( point_2d_01.Dims(), 2 );
    ASSERT_EQ( point_2f_01.Dims(), 2 );
    ASSERT_EQ( point_2i_01.Dims(), 2 );
    ASSERT_EQ( point_2s_01.Dims(), 2 );
    ASSERT_EQ( point_2u_01.Dims(), 2 );
    
    ASSERT_EQ( point_3d_01.Dims(), 3 );
    ASSERT_EQ( point_3f_01.Dims(), 3 );
    ASSERT_EQ( point_3i_01.Dims(), 3 );
    ASSERT_EQ( point_3s_01.Dims(), 3 );
    ASSERT_EQ( point_3u_01.Dims(), 3 );

    // Check the values
    ASSERT_NEAR( point_2d_01.x(), 0, 0.00001 );
    ASSERT_NEAR( point_2d_01.y(), 0, 0.00001 );
    ASSERT_NEAR( point_2f_01.x(), 0, 0.00001 );
    ASSERT_NEAR( point_2f_01.y(), 0, 0.00001 );
    ASSERT_EQ( point_2i_01.x(), 0 );
    ASSERT_EQ( point_2i_01.y(), 0 );
    ASSERT_EQ( point_2s_01.x(), 0 );
    ASSERT_EQ( point_2s_01.y(), 0 );
    ASSERT_EQ( point_2u_01.x(), 0 );
    ASSERT_EQ( point_2u_01.y(), 0 );
    
    ASSERT_NEAR( point_3d_01.x(), 0, 0.00001 );
    ASSERT_NEAR( point_3d_01.y(), 0, 0.00001 );
    ASSERT_NEAR( point_3d_01.z(), 0, 0.00001 );
    ASSERT_NEAR( point_3f_01.x(), 0, 0.00001 );
    ASSERT_NEAR( point_3f_01.y(), 0, 0.00001 );
    ASSERT_NEAR( point_3f_01.z(), 0, 0.00001 );
    ASSERT_EQ( point_3i_01.x(), 0 );
    ASSERT_EQ( point_3i_01.y(), 0 );
    ASSERT_EQ( point_3i_01.z(), 0 );
    ASSERT_EQ( point_3s_01.x(), 0 );
    ASSERT_EQ( point_3s_01.y(), 0 );
    ASSERT_EQ( point_3s_01.z(), 0 );
    ASSERT_EQ( point_3u_01.x(), 0 );
    ASSERT_EQ( point_3u_01.y(), 0 );
    ASSERT_EQ( point_3u_01.z(), 0 );

}

/**
 * Test the 2d constructor
*/
TEST( A_Point, Constructor_2d ){

    // Create point
    MATH::A_Point2d point_2d_01( 1, 2 );
    MATH::A_Point2i point_2d_02( 3, 4 );
    MATH::A_Point3f point_3d_01( -1, 1.1);

    ASSERT_NEAR( point_2d_01.x(), 1, 0.0001 );
    ASSERT_NEAR( point_2d_01.y(), 2, 0.0001 );
    ASSERT_EQ(   point_2d_02.x(), 3 );
    ASSERT_EQ(   point_2d_02.y(), 4 );
    ASSERT_NEAR( point_3d_01.x(), -1, 0.0001 );
    ASSERT_NEAR( point_3d_01.y(), 1.1, 0.0001 );
    ASSERT_NEAR( point_3d_01.z(), 0, 0.00001 );

}

/**
 * Test the 3d constructor
*/
TEST( A_Point, Constructor_3d ){

    // Create points
    MATH::A_Point3d point01( 1, 2, -2.2 );
    ASSERT_NEAR( point01[0],  1, 0.0001 );
    ASSERT_NEAR( point01[1],  2, 0.0001 );
    ASSERT_NEAR( point01[2],-2.2, 0.0001 );

}

/** 
 * Test the Copy Constructor
*/
TEST( A_Point, Copy_Constructor ){

    // Create a point
    MATH::A_Point3d initial_point( 1, 2, -3 );

    // Copy the point
    MATH::A_Point3d copy_point(initial_point);

    // Check results
    ASSERT_NEAR( initial_point[0], 1, 0.0001 );
    ASSERT_NEAR( initial_point[1], 2, 0.0001 );
    ASSERT_NEAR( initial_point[2],-3, 0.0001 );
    ASSERT_NEAR( copy_point[0], 1, 0.0001 );
    ASSERT_NEAR( copy_point[1], 2, 0.0001 );
    ASSERT_NEAR( copy_point[2],-3, 0.0001 );

    // Change point 1
    initial_point.x() = 4;
    initial_point.y() = 5;
    initial_point.z() =-6;

    // Check results
    ASSERT_NEAR( initial_point[0], 4, 0.0001 );
    ASSERT_NEAR( initial_point[1], 5, 0.0001 );
    ASSERT_NEAR( initial_point[2],-6, 0.0001 );
    ASSERT_NEAR( copy_point[0], 1, 0.0001 );
    ASSERT_NEAR( copy_point[1], 2, 0.0001 );
    ASSERT_NEAR( copy_point[2],-3, 0.0001 );

    // Change point 2
    copy_point[0] = 7;
    copy_point[1] = 8;
    copy_point[2] =-9;

    // Check results
    ASSERT_NEAR( initial_point[0], 4, 0.0001 );
    ASSERT_NEAR( initial_point[1], 5, 0.0001 );
    ASSERT_NEAR( initial_point[2],-6, 0.0001 );
    ASSERT_NEAR( copy_point[0], 7, 0.0001 );
    ASSERT_NEAR( copy_point[1], 8, 0.0001 );
    ASSERT_NEAR( copy_point[2],-9, 0.0001 );
}


/** 
 * Test the assignment operator
*/
TEST( A_Point, Assignment_Operator){

    // Create a point
    MATH::A_Point3d initial_point( 1, 2, -3 );

    // Copy the point
    MATH::A_Point3d copy_point( 10, 11, 12 );
    copy_point = initial_point;

    // Check results
    ASSERT_NEAR( initial_point[0], 1, 0.0001 );
    ASSERT_NEAR( initial_point[1], 2, 0.0001 );
    ASSERT_NEAR( initial_point[2],-3, 0.0001 );
    ASSERT_NEAR( copy_point[0], 1, 0.0001 );
    ASSERT_NEAR( copy_point[1], 2, 0.0001 );
    ASSERT_NEAR( copy_point[2],-3, 0.0001 );

    // Change point 1
    initial_point.x() = 4;
    initial_point.y() = 5;
    initial_point.z() =-6;

    // Check results
    ASSERT_NEAR( initial_point[0], 4, 0.0001 );
    ASSERT_NEAR( initial_point[1], 5, 0.0001 );
    ASSERT_NEAR( initial_point[2],-6, 0.0001 );
    ASSERT_NEAR( copy_point[0], 1, 0.0001 );
    ASSERT_NEAR( copy_point[1], 2, 0.0001 );
    ASSERT_NEAR( copy_point[2],-3, 0.0001 );

    // Change point 2
    copy_point[0] = 7;
    copy_point[1] = 8;
    copy_point[2] =-9;

    // Check results
    ASSERT_NEAR( initial_point[0], 4, 0.0001 );
    ASSERT_NEAR( initial_point[1], 5, 0.0001 );
    ASSERT_NEAR( initial_point[2],-6, 0.0001 );
    ASSERT_NEAR( copy_point[0], 7, 0.0001 );
    ASSERT_NEAR( copy_point[1], 8, 0.0001 );
    ASSERT_NEAR( copy_point[2],-9, 0.0001 );

}


/**
 * Test the Addition Operators
*/
TEST( A_Point, Addition_Operator ){

    // Create a point pair
    MATH::A_Point2d point_2d_01( 1, 2 );
    MATH::A_Point2d point_2d_02( -1, 2 );
    
    // Add
    MATH::A_Point2d result_2d = point_2d_01 + point_2d_02;
    ASSERT_NEAR( result_2d.x(), 0, 0.0001 );
    ASSERT_NEAR( result_2d.y(), 4, 0.0001 );
    
    // Create another point pair
    MATH::A_Point3i point_3i_01(  1, 2, -1 );
    MATH::A_Point3i point_3i_02( -1, 2, -2 );
    
    // Add
    MATH::A_Point3i result_3i = point_3i_01 + point_3i_02;
    ASSERT_NEAR( result_3i.x(), 0, 0.0001 );
    ASSERT_NEAR( result_3i.y(), 4, 0.0001 );
    ASSERT_NEAR( result_3i.z(),-3, 0.0001 );

}


/**
 * Test the Subtraction Operators
*/
TEST( A_Point, Subtraction_Operator ){

    // Create a point pair
    MATH::A_Point2d point_2d_01( 1, 2 );
    MATH::A_Point2d point_2d_02( -1, 2 );
    
    // Add
    MATH::A_Point2d result_2d = point_2d_01 - point_2d_02;
    ASSERT_NEAR( result_2d.x(), 2, 0.0001 );
    ASSERT_NEAR( result_2d.y(), 0, 0.0001 );
    
    // Create another point pair
    MATH::A_Point3i point_3i_01(  1, 2, -1 );
    MATH::A_Point3i point_3i_02( -1, 2, -2 );
    
    // Add
    MATH::A_Point3i result_3i = point_3i_01 - point_3i_02;
    ASSERT_NEAR( result_3i.x(), 2, 0.0001 );
    ASSERT_NEAR( result_3i.y(), 0, 0.0001 );
    ASSERT_NEAR( result_3i.z(), 1, 0.0001 );

}


