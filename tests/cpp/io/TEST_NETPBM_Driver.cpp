/**
 * @file    TEST_NETPBM_Driver.hpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#include <gtest/gtest.h>

/// GeoExplore Libraries
#include <GeoExplore.hpp>

/// C++ Standard Libraries
#include <iostream>

using namespace std;

/**
 * Test the Write PPM Function
*/
TEST( NETPBM_Driver, WriteImagePPM ){

    /// create an image
    GEO::IMG::Image<GEO::IMG::PixelRGB_d>  image01(50,50);

    for( int i=0; i<25; i++ ){
    for( int j=0; j<25; j++ ){
        
        image01(i +  0, j +  0) = GEO::IMG::PixelRGB_d(0,0,0);
        image01(i + 25, j +  0) = GEO::IMG::PixelRGB_d(1,0,0);
        image01(i +  0, j + 25) = GEO::IMG::PixelRGB_d(0,1,0);
        image01(i + 25, j + 25) = GEO::IMG::PixelRGB_d(0,0,1);
    }}

    // write the image
    GEO::IO::NETPBM::write_image( image01, "file.ppm");

    // make sure the file exists
    if( boost::filesystem::exists( "file.ppm" ) == false ){
        FAIL();
    }

    // delete file
    system("rm file.ppm");
}

/**
 * Test the Write PGM Function
*/
TEST( NETPBM_Driver, WriteImagePGM ){
    
    /// create an image
    GEO::IMG::Image<GEO::IMG::PixelRGB_d>  image01(50,50);

    for( int i=0; i<25; i++ ){
    for( int j=0; j<25; j++ ){
        
        image01(i +  0, j +  0) = GEO::IMG::PixelRGB_d(0,0,0);
        image01(i + 25, j +  0) = GEO::IMG::PixelRGB_d(1,0,0);
        image01(i +  0, j + 25) = GEO::IMG::PixelRGB_d(0,1,0);
        image01(i + 25, j + 25) = GEO::IMG::PixelRGB_d(0,0,1);
    }}

    // write the image
    GEO::IO::NETPBM::write_image( image01, "file.pgm");

    // make sure the file exists
    if( boost::filesystem::exists( "file.pgm" ) == false ){
        FAIL();
    }

    // delete file
    system("rm file.pgm");
}

/**
 * Test the Write Image with bad file type
*/
TEST( NETPBM_Driver, WriteImageError ){

    /// Create an image
    GEO::IMG::Image<GEO::IMG::PixelRGB_d> image01;

    // write the image
    ASSERT_THROW( GEO::IO::NETPBM::write_image( image01, "file.jpg"), GEO::GeneralException );

}

