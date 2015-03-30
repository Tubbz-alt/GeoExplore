/**
 * @file    TEST_ImageTransformNormalize.cpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../../../lib/image/PixelCast.hpp"
#include "../../../lib/image/Pixel_Types.hpp"
#include "../../../lib/image/transforms/ImageTransformNormalize.hpp"

using namespace GEO;

/**
 * Test the Normalize Image Method
*/
TEST( ImageTransformNormalize, Normalize_Image_Gray_df ){

    // Define our image size
    const A_Size<int> image_size( 100,100);

    // Define our range
    const IMG::PixelGray_df min_value(1);
    const IMG::PixelGray_df max_value (2);

    // Generate a test image
    IMG::Image<IMG::PixelGray_df>::ptr_t image(new IMG::Image<IMG::PixelGray_df>( image_size ));
    
    // Generate an output image
    IMG::Image<IMG::PixelGray_df>::ptr_t output_image(new IMG::Image<IMG::PixelGray_df>( image_size ));

    // Set the input image data
    for( int r=0; r<image_size.Height(); r++ )
    for( int c=0; c<image_size.Width(); c++ ){
        (*image)(r,c) = r+c;
    }

    // Normalize the image
    IMG::Normalize_Image<IMG::PixelGray_df>( image,
                                             output_image, 
                                             min_value, 
                                             max_value, 
                                             IMG::NormalizeMode::MINMAX );

    
    // Check the pixel values
    ASSERT_NEAR( output_image->operator()(0,0)[0], min_value[0], 0.0001 );
    ASSERT_NEAR( output_image->operator()(image_size.Height()-1,image_size.Width()-1)[0], max_value[0], 0.0001 );

}


/**
 * Test the Normalize Image Method
*/
TEST( ImageTransformNormalize, Normalize_Image_RGB_u8 ){

    // Define our image size
    const A_Size<int> image_size( 100,100);

    // Define our range
    const IMG::PixelRGB_u8 min_value(1, 2, 3);
    const IMG::PixelRGB_u8 max_value (123, 145, 222);

    // Generate a test image
    IMG::Image<IMG::PixelRGB_u8>::ptr_t image(new IMG::Image<IMG::PixelRGB_u8>( image_size ));
    
    // Generate an output image
    IMG::Image<IMG::PixelRGB_u8>::ptr_t output_image(new IMG::Image<IMG::PixelRGB_u8>( image_size ));

    // Set the input image data
    for( int r=0; r<image_size.Height(); r++ )
    for( int c=0; c<image_size.Width(); c++ ){
    for( int i=0; i<3; i++ ){
        (*image)(r,c)[i] = r+c;
    }}

    // Normalize the image
    IMG::Normalize_Image<IMG::PixelRGB_u8>( image,
                                            output_image, 
                                            min_value, 
                                            max_value, 
                                            IMG::NormalizeMode::MINMAX );

    
    // Check the pixel values
    ASSERT_EQ( output_image->operator()(0,0)[0], min_value[0] );
    ASSERT_EQ( output_image->operator()(0,0)[1], min_value[1] );
    ASSERT_EQ( output_image->operator()(0,0)[2], min_value[2] );
    ASSERT_EQ( output_image->operator()(image_size.Height()-1,image_size.Width()-1)[0], max_value[0] );
    ASSERT_EQ( output_image->operator()(image_size.Height()-1,image_size.Width()-1)[1], max_value[1] );
    ASSERT_EQ( output_image->operator()(image_size.Height()-1,image_size.Width()-1)[2], max_value[2] );

}

