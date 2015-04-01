/**
 * @file    TEST_A_Rectangle.cpp
 * @author  Marvin Smith
 * @date    3/23/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/math/A_Point.hpp"
#include "../../lib/math/A_Rectangle.hpp"

using namespace GEO;

/**
 * Test the rectangle with points
*/
TEST( A_Rectangle, Constructors_Point2d ){

    // Create an empty rectangle
    MATH::A_Rectangle2d rectangle01;

    ASSERT_NEAR( rectangle01.TL().x(), 0, 0.00001 );
    ASSERT_NEAR( rectangle01.TL().y(), 0, 0.00001 );
    ASSERT_NEAR( rectangle01.TR().x(), 0, 0.00001 );
    ASSERT_NEAR( rectangle01.TR().y(), 0, 0.00001 );
    ASSERT_NEAR( rectangle01.BL().x(), 0, 0.00001 );
    ASSERT_NEAR( rectangle01.BL().y(), 0, 0.00001 );
    ASSERT_NEAR( rectangle01.BR().x(), 0, 0.00001 );
    ASSERT_NEAR( rectangle01.BR().y(), 0, 0.00001 );
    ASSERT_NEAR( rectangle01.Width(), 0, 0.0001 );
    ASSERT_NEAR( rectangle01.Height(), 0, 0.0001 );

    // Create another rectangle
    MATH::A_Rectangle2i rectangle02( MATH::A_Point2i( 1, 1), MATH::A_Point2i( 3, 2));
    
    ASSERT_EQ( rectangle02.TL().x(), 1 );
    ASSERT_EQ( rectangle02.TL().y(), 2 );
    ASSERT_EQ( rectangle02.TR().x(), 3 );
    ASSERT_EQ( rectangle02.TR().y(), 2 );
    ASSERT_EQ( rectangle02.BL().x(), 1 );
    ASSERT_EQ( rectangle02.BL().y(), 1 );
    ASSERT_EQ( rectangle02.BR().x(), 3 );
    ASSERT_EQ( rectangle02.BR().y(), 1 );
    ASSERT_EQ( rectangle02.Width(),  2 );
    ASSERT_EQ( rectangle02.Height(), 1 );

    // Create a final rectangle
    MATH::A_Rectangle2f rectangle03( MATH::A_Point2f( 10, -1), 5, 4);
    ASSERT_NEAR( rectangle03.TL().x(), 10, 0.0001 );
    ASSERT_NEAR( rectangle03.TL().y(),  3, 0.0001 );
    ASSERT_NEAR( rectangle03.TR().x(), 15, 0.0001 );
    ASSERT_NEAR( rectangle03.TR().y(),  3, 0.0001 );
    ASSERT_NEAR( rectangle03.BL().x(), 10, 0.0001 );
    ASSERT_NEAR( rectangle03.BL().y(), -1, 0.0001 );
    ASSERT_NEAR( rectangle03.BR().x(), 15, 0.0001 );
    ASSERT_NEAR( rectangle03.BR().y(), -1, 0.0001 );
    ASSERT_NEAR( rectangle03.Width(),   5, 0.0001 );
    ASSERT_NEAR( rectangle03.Height(),  4, 0.0001 );

}


/**
 * Test theh Inside Method
*/
TEST( A_Rectangle, Inside ){

    // Create a rectangle
    MATH::A_Rectangle2d rectangle01( MATH::A_Point2d(-1,-2), 2, 4 );

    // Test the corners
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d(-1,-2) ) );
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d( 1,-2) ) );
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d(-1, 2) ) );
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d( 1, 2) ) );

    // Test some interior points
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d( 0, 0)));
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d( 0,-2)));
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d( 0, 2)));
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d( 1, 0)));
    ASSERT_TRUE( rectangle01.Inside( MATH::A_Point2d( 1, 0)));
    
    // Test some exterior points
    ASSERT_FALSE( rectangle01.Inside( MATH::A_Point2d( 3, 0)));
    ASSERT_FALSE( rectangle01.Inside( MATH::A_Point2d( 0, 3)));
    ASSERT_FALSE( rectangle01.Inside( MATH::A_Point2d( 3, 3)));
    ASSERT_FALSE( rectangle01.Inside( MATH::A_Point2d(-3,-3)));

}


