/**
 * @file    TEST_Common_Equations.cpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/math/Common_Equations.hpp"

using namespace GEO;

/**
 * Test the LERP Equation
 */
TEST( Common_Equations, LERP )
{

    // Define EPS
    const double eps = 0.0001;

    ASSERT_EQ( MATH::LERP<int>( 1, 5, 0.5), 3 );
    ASSERT_NEAR( MATH::LERP<double>( 1, 5, 0.5), 3, eps );
    ASSERT_NEAR( MATH::LERP<double>( 0, 1, 0.25), 0.25, eps );
}
