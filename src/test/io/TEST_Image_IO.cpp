/**
 * @file    TEST_Image_IO.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../lib/image/Image.hpp"
#include "../../lib/image/MemoryResource.hpp"
#include "../../lib/image/Pixel_Types.hpp"
#include "../../lib/io/Image_IO.hpp"

using namespace GEO;

/**
 * Test the Read_Image method
*/
TEST( Image_IO, Read_Image_lena_rgb_u8_test_01 ){
    
    // Load the image
    IMG::Image<IMG::PixelRGB_u8> image;
    IO::Read_Image( "data/unit-tests/images/lenna.jpg", image );

    // Check image size
    ASSERT_EQ( image.Rows(), 512 );
    ASSERT_EQ( image.Cols(), 512 );

}

/**
 * Test the Write_Image method.
 */
TEST( Image_IO, Write_Image_tif_rgb_u8_test_01 ){
    
    // Define the desired image size
    const A_Size<int> image_size(1000,1000);
    const int block_size = 100;
    
    // Define the eps
    const double eps = 1;

    // Create a Checkerboard Image
    IMG::Image<IMG::PixelRGB_u8> image(image_size);
    for( int r=0; r<image.Rows(); r++ )
    for( int c=0; c<image.Cols(); c++ ){
        if( (r/block_size)%2 == 0 && (c/block_size)%2 == 0 ){
            image(r,c) = IMG::PixelRGB_u8::White();
        }
        else if( (r/block_size)%2 == 1 && (c/block_size)%2 == 0 ){
            image(r,c) = IMG::PixelRGB_u8::Red();
        }
        else if( (r/block_size)%2 == 0 && (c/block_size)%2 == 1 ){
            image(r,c) = IMG::PixelRGB_u8::Green();
        }
        else{
            image(r,c) = IMG::PixelRGB_u8::Blue();
        }
    }

    // Define the output path
    FS::FilesystemPath output_path("output-test.tif");

    // Write Image
    IO::Write_Image( image, output_path );
    ASSERT_TRUE( output_path.Exists() );

    // Check image information
    IMG::Image<IMG::PixelRGB_u8> result_image;
    IO::Read_Image( output_path, result_image );

    // Check sizes
    ASSERT_EQ( result_image.Rows(), image.Rows() );
    ASSERT_EQ( result_image.Cols(), image.Cols() );

    // Check contents
    for( int r=0; r<image.Rows(); r++ )
    for( int c=0; c<image.Cols(); c++ )
    for( int x=0; x<image.Channels(); x++ ){
        ASSERT_NEAR( image(r,c)[x], result_image(r,c)[x], eps );
    }
    
    // Delete the test image
    output_path.Delete();
    ASSERT_FALSE( output_path.Exists() );
    
}

/**
 * Test the Write Image Method.
*/
TEST( Image_IO, Write_Image_tif_rgba_u8_test_01 ){

    // Define the desired image size
    const A_Size<int> image_size(1000,1000);
    const int block_size = 100;
    
    // Define the eps
    const double eps = 1;

    // Create a Checkerboard Image
    IMG::Image<IMG::PixelRGBA_u8> image(image_size);
    for( int r=0; r<image.Rows(); r++ )
    for( int c=0; c<image.Cols(); c++ ){
        if( (r/block_size)%2 == 0 && (c/block_size)%2 == 0 ){
            image(r,c) = IMG::PixelRGBA_u8::White();
        }
        else if( (r/block_size)%2 == 1 && (c/block_size)%2 == 0 ){
            image(r,c) = IMG::PixelRGBA_u8::Red();
        }
        else if( (r/block_size)%2 == 0 && (c/block_size)%2 == 1 ){
            image(r,c) = IMG::PixelRGBA_u8::Green();
        }
        else{
            image(r,c) = IMG::PixelRGBA_u8::Blue();
        }
    }

    // Define the output path
    FS::FilesystemPath output_path("output-test.tif");

    // Write Image
    IO::Write_Image( image, output_path );
    ASSERT_TRUE( output_path.Exists() );

    // Check image information
    IMG::Image<IMG::PixelRGBA_u8> result_image;
    IO::Read_Image( output_path, result_image );

    // Check sizes
    ASSERT_EQ( result_image.Rows(), image.Rows() );
    ASSERT_EQ( result_image.Cols(), image.Cols() );

    // Check contents
    for( int r=0; r<image.Rows(); r++ )
    for( int c=0; c<image.Cols(); c++ )
    for( int x=0; x<image.Channels(); x++ ){
        ASSERT_NEAR( image(r,c)[x], result_image(r,c)[x], eps );
    }
    
    // Delete the test image
    output_path.Delete();
    ASSERT_FALSE( output_path.Exists() );

}


