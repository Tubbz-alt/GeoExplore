/**
 * @file    geo-explore-unit-tests.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
 */
#include <gtest/gtest.h>


/**
 * @brief Main Function
*/
GTEST_API_ int main(int argc, char *argv[] ) 
{
  
  // Print Entry
  printf("Running main() from gtest_main.cc\n");
  
  // Initialize Google Tests
  testing::InitGoogleTest(&argc, argv);
  
  // Run Tests
  return RUN_ALL_TESTS();
}
