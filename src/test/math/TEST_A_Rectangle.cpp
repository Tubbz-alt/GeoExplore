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


bool Compare_Rectangles( MATH::A_Rectangle2d r1, 
                         MATH::A_Rectangle2d r2,
                         const double&       eps = 0.001 )
{
    
    // Set to true if both are empty
    if( std::fabs(r1.Area()) < eps && std::fabs(r2.Area()) < eps ){ return true; }

    if( std::fabs(r1.BL().x() - r2.BL().x()) >= eps ){ return false; }
    if( std::fabs(r1.BL().y() - r2.BL().y()) >= eps ){ return false; }
    if( std::fabs(r1.TR().x() - r2.TR().x()) >= eps ){ return false; }
    if( std::fabs(r1.TR().y() - r2.TR().y()) >= eps ){ return false; }

    return true;
}

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

/**
 * Test Rectangle Area
*/
TEST( A_Rectangle, Area ){

    ASSERT_NEAR( MATH::A_Rectangle2d(MATH::A_Point2d(-1,-1),0,0).Area(), 0, 0.00001 );
    ASSERT_NEAR( MATH::A_Rectangle2d(MATH::A_Point2d(-1,-1),1,1).Area(), 1, 0.00001 );
    ASSERT_NEAR( MATH::A_Rectangle2d(MATH::A_Point2d(1,1),0,0).Area(), 0, 0.00001 );
    ASSERT_NEAR( MATH::A_Rectangle2d(MATH::A_Point2d(1,1),2,3).Area(), 6, 0.00001 );
    ASSERT_NEAR( MATH::A_Rectangle2d(MATH::A_Point2d(-1,-1),3,0).Area(), 0, 0.00001 );
    ASSERT_NEAR( MATH::A_Rectangle2d(MATH::A_Point2d(-1,-1),2,0).Area(), 0, 0.00001 );
    ASSERT_NEAR( MATH::A_Rectangle2d(MATH::A_Point2d(-1,-1),0,1).Area(), 0, 0.00001 );

}

/**
 * Test Rectangle Intersection
*/
TEST( A_Rectangle, Intersection ){

    // Create some rectangles
    MATH::A_Rectangle2d r01( MATH::A_Point2d( 1, 1), 2, 2);
    MATH::A_Rectangle2d r02( MATH::A_Point2d(-1,-1), 2, 2);
    MATH::A_Rectangle2d r03( MATH::A_Point2d(-1,-1), 3, 3);
    MATH::A_Rectangle2d r04( MATH::A_Point2d( 0,-1), 3, 3);
    MATH::A_Rectangle2d r05( MATH::A_Point2d( 3, 3), 3, 3);
    
    // Define our expected rectangles
    MATH::A_Rectangle2d exp_test_fail;
    MATH::A_Rectangle2d exp_test_01 = r01;
    MATH::A_Rectangle2d exp_test_02 = r02;
    MATH::A_Rectangle2d exp_test_03 = r03;
    MATH::A_Rectangle2d exp_test_04 = r02;
    MATH::A_Rectangle2d exp_test_05( MATH::A_Point2d(0,-1), 1, 2);


    // TEST 01 (Same Rectangles)
    ASSERT_TRUE( Compare_Rectangles(r01.Intersection(r01), exp_test_01 ) );
    ASSERT_TRUE( Compare_Rectangles(r02.Intersection(r02), exp_test_02 ) );
    ASSERT_TRUE( Compare_Rectangles(r03.Intersection(r03), exp_test_03 ) );

    // TEST 02 (One Inside the Other)
    ASSERT_TRUE( Compare_Rectangles(r03.Intersection(r02), exp_test_04 ) );
    ASSERT_TRUE( Compare_Rectangles(r02.Intersection(r03), exp_test_04 ) );

    // TEST 03 (Sides overlap)
    ASSERT_TRUE( Compare_Rectangles(r02.Intersection(r04), exp_test_05 ) );
    ASSERT_TRUE( Compare_Rectangles(r04.Intersection(r02), exp_test_05 ) );


    // TEST 04 (sides touch but no overlap)
    ASSERT_TRUE( Compare_Rectangles(r01.Intersection(r02), exp_test_fail ) );
    ASSERT_TRUE( Compare_Rectangles(r02.Intersection(r01), exp_test_fail ) );


    // TEST 05 (No overlap)
    ASSERT_TRUE( Compare_Rectangles(r03.Intersection(r05), exp_test_fail ) );
    ASSERT_TRUE( Compare_Rectangles(r05.Intersection(r03), exp_test_fail ) );


}


/**
 * Test Rectangle Union 
 */
TEST( A_Rectangle, Union ){

    // Create some rectangles
    MATH::A_Rectangle2d r01( MATH::A_Point2d( 1, 1), 2, 2);
    MATH::A_Rectangle2d r02( MATH::A_Point2d(-1,-1), 2, 2);
    MATH::A_Rectangle2d r03( MATH::A_Point2d(-1,-1), 3, 3);
    MATH::A_Rectangle2d r04( MATH::A_Point2d( 0,-1), 3, 3);
    MATH::A_Rectangle2d r05( MATH::A_Point2d( 3, 3), 3, 3);

    // Test the Union
    MATH::A_Rectangle2d exp_result_01( MATH::A_Point2d(-1, -1), 4, 3);

    // TEST 01 Same Rectangles
    ASSERT_TRUE( Compare_Rectangles(r01.Union(r01), r01));
    ASSERT_TRUE( Compare_Rectangles(r02.Union(r02), r02));
    ASSERT_TRUE( Compare_Rectangles(r03.Union(r03), r03));

    // TEST 02 Overlapping Rectangles
    ASSERT_TRUE( Compare_Rectangles( r02.Union(r03), r03 ));
    ASSERT_TRUE( Compare_Rectangles( r03.Union(r02), r03 ));

    // TEST 03 Sides Overlap 
    ASSERT_TRUE( Compare_Rectangles( r03.Union(r04), exp_result_01 ));
    ASSERT_TRUE( Compare_Rectangles( r04.Union(r03), exp_result_01 ));

    

}

