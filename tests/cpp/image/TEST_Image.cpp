/**
 * @file    TEST_Image.cpp
 * @author  Marvin Smith
 * @date    5/10/2014
*/
#include <gtest/gtest.h>

/// GeoExplore Library
#include <GeoExplore.hpp>

/// C++ Standard Libraries
#include <iostream>

using namespace std;


/**
 * Test the Image_ class functions using a Memory resource
*/
TEST( Image, Constructors ){

    /// Create a RAM Image
    GEO::IMG::Image<GEO::IMG::PixelRGB_u8> image01;
    
    // make sure the resource is empty
    ASSERT_EQ( image01.rows(), 0);
    ASSERT_EQ( image01.cols(), 0);
    
    /// Create a RAM Image with a specified size
    GEO::IMG::Image<GEO::IMG::PixelRGB_d> image02(100,75);
    ASSERT_EQ( image02.rows(), 100);
    ASSERT_EQ( image02.cols(), 75);
    

}

/**
 * Test the Image_ class getters and setters
*/
TEST( Image, FunctionOperators ){

    // create a ram image
    GEO::IMG::Image<GEO::IMG::PixelRGB_u8> image01(10,10);

    // set some pixels
    image01(5,5) = GEO::IMG::PixelRGB_u8(1, 2, 3);
    ASSERT_EQ( image01(5,5)[0], 1);
    ASSERT_EQ( image01(5,5)[1], 2);
    ASSERT_EQ( image01(5,5)[2], 3);

}

/**
 * Test the DiskImage class Constructor
*/
TEST( DiskImage, Constructor ){

    // create a disk image
    GEO::IMG::DiskImage<GEO::IMG::PixelGray_df> image;
    GEO::IO::read_image( "../../tests/data/dem/n39_w120_3arc_v1.bil", image );

    ASSERT_EQ( image.rows(), 1201 );
    ASSERT_EQ( image.cols(), 1201 );
    ASSERT_EQ( image.channels(), 1 ); 
}

/**
 * Test the disk image function operator
*/
TEST( DiskImage, FunctionOperators ){

    // create a disk image
    GEO::IMG::DiskImage<GEO::IMG::PixelGray_df> image;
    GEO::IO::read_image( "../../tests/data/dem/n39_w120_3arc_v1.bil", image );

    // make sure we get data out
    ASSERT_EQ( image.rows(), 1201 );
    ASSERT_EQ( image.cols(), 1201 );
    ASSERT_EQ( image.channels(), 1 ); 
    cout << "Printing" << endl;
    cout << image[0][0] << ", " << image[1][0] << endl;

    FAIL();

}


