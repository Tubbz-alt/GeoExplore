/**
 * @file    TEST_MemoryResource.cpp
 * @author  Marvin Smith
 * @date    5/10/2014
*/
#include <gtest/gtest.h>

/// GeoExplore Library
#include <GeoExplore.hpp>

/**
 * Test the Memory Resource Constructor
*/
TEST( MemoryResource, DefaultConstructor ){

    // create first memory resource
    GEO::MemoryResource<GEO::PixelRGB_u8> memoryResource01;
    
    // make sure the rows and columns are empty
    ASSERT_EQ( memoryResource01.rows(), 0);
    ASSERT_EQ( memoryResource01.cols(), 0);

    // make sure an assertion is thrown when we try to access memory
    ASSERT_THROW( memoryResource01[0], GEO::MemoryResourceNotInitializedException);

}


