/**
 * @file    TEST_CoordinateConversion.cpp
 * @author  Marvin Smith
 * @date    3/25/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/coordinate/CoordinateConversion.hpp"
#include "../Unit_Testing_Only/Coordinate_Test_Harness.hpp"

using namespace GEO;


/**
 * Test the UTM to Geographic Conversions
*/
TEST( CoordinateConversion, convert_coordinate_UTM_Geographic ){
    
    // Get an instance of the test harness
    Coordinate_Test_Harness::ptr_t instance = Coordinate_Test_Harness::Instance_Of();

}

