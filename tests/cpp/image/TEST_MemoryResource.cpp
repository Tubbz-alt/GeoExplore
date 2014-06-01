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

/**
 * Test the memory resource assignment operator
*/
TEST( MemoryResource, AssignmentOperator ){

    // create a Memory Resource with a specific size
    GEO::MemoryResource<GEO::PixelGray_u8> resource01(100,100);

    // load the reference with dummy values
    for( int i=0; i<(resource01.rows()*resource01.cols()); i++ ){
        resource01[i] = i;
    }

    // create a new resource and copy the values
    GEO::MemoryResource<GEO::PixelGray_u8> resource02 = resource01;

    // make sure the values match
    ASSERT_EQ( resource02.rows(), 100 );
    ASSERT_EQ( resource02.cols(), 100 );
    for( int i=0; i<(resource01.rows()*resource01.cols()); i++ ){
        ASSERT_EQ( resource02[i], i );
    }

}


