/**
 * @file    geo-explore-unit-tests.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
 */
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../lib/core/A_Status.hpp"

// Unit Test Libraries
#include "Unit_Testing_Only/Coordinate_Test_Harness.hpp"

/**
 * @brief Main Function
*/
GTEST_API_ int main(int argc, char *argv[] ) 
{
    // Status
    GEO::Status status;

    // Create the test harness
    status = Coordinate_Test_Harness::Instance_Of()->Initialize("data/unit-test-data/coordinate-test-set.xml");
    
    // Print Entry
    printf("Running main() from gtest_main.cc\n");
  
    // Initialize Google Tests
    testing::InitGoogleTest(&argc, argv);
  
    // Run Tests
    return RUN_ALL_TESTS();
}
