/**
 * @file    TEST_A_Status.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore
#include "../../lib/core/A_Status.hpp"

using namespace GEO;

/**
 * Test the Constructor
*/
TEST( Status, Constructors ){

    // TEST 01
    Status status01( StatusType::SUCCESS );
    ASSERT_EQ( status01.Get_Status_Type(), StatusType::SUCCESS );

    // Test 2
    Status status02;
    ASSERT_EQ( status02.Get_Status_Type(), StatusType::SUCCESS );
    
}

