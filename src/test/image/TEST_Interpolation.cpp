/**
 * @file    TEST_Interpolation.cpp
 * @author  Marvin Smith
 * @date    4/1/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/core/A_Size.hpp>
#include <GeoExplore/image/Interpolation.hpp>
#include <GeoExplore/image/MemoryResource.hpp>
#include <GeoExplore/image/Pixel_Types.hpp>


using namespace GEO;

/**
 * Test Interpolation
*/
TEST( Interpolation, Interpolate_Nearest_Neighbor_invalid ){

    // Set Image Size
    A_Size<int> image_size(100,100);

    // Create Images
    IMG::Image<IMG::PixelRGB_u16> image01;
    IMG::Image<IMG::PixelRGB_u16> image02(image_size);
    
    // Set Pixel Data
    for( int r=0; r<image_size.Width();  r++ )
    for( int c=0; c<image_size.Height(); c++ )
    for( int x=0; x<3; x++ )
        image02(r,c)[x] = r+c + 1;

    // Empty Images
    ASSERT_EQ( IMG::Interpolate_Nearest_Neighbor( image01, MATH::A_Point2d(0,0)),  IMG::PixelRGB_u16());
    ASSERT_EQ( IMG::Interpolate_Nearest_Neighbor( image01, MATH::A_Point2d(3,10)), IMG::PixelRGB_u16());

    // Pixel Below Min
    ASSERT_EQ( IMG::Interpolate_Nearest_Neighbor( image02, MATH::A_Point2d(-1,-1)), IMG::PixelRGB_u16(1,1,1));
    ASSERT_EQ( IMG::Interpolate_Nearest_Neighbor( image02, MATH::A_Point2d(-9,-9)), IMG::PixelRGB_u16(1,1,1));

    // Pixel Above Max
    ASSERT_EQ( IMG::Interpolate_Nearest_Neighbor( image02, MATH::A_Point2d(101,101)), IMG::PixelRGB_u16(199,199,199));
    ASSERT_EQ( IMG::Interpolate_Nearest_Neighbor( image02, MATH::A_Point2d(105,105)), IMG::PixelRGB_u16(199,199,199));

    // Pixel Generally out of bounds
    ASSERT_EQ( IMG::Interpolate_Nearest_Neighbor( image02, MATH::A_Point2d(10,101)), IMG::PixelRGB_u16(110,110,110));
    ASSERT_EQ( IMG::Interpolate_Nearest_Neighbor( image02, MATH::A_Point2d(101,10)), IMG::PixelRGB_u16(110,110,110));

}

/**
 * Test the Interpolate Nearest Neighbor Method
*/
TEST( Interpolation, Interpolate_Nearest_Neighbor ){

    // Epsilon
    const double eps = 0.0001;

    // Define the image size
    A_Size<int> image_size(100,100);

    // Create an image
    IMG::Image<IMG::PixelGray_df> image(image_size);

    // Set Pixel Data
    for( int r=0; r<image_size.Width();  r++ )
    for( int c=0; c<image_size.Height(); c++ )
        image(r,c) = r+c;

    // Test Interpolation
    ASSERT_NEAR( IMG::Interpolate_Nearest_Neighbor( image, MATH::A_Point2d(  0  ,  0  ))[0],   0, eps );
    ASSERT_NEAR( IMG::Interpolate_Nearest_Neighbor( image, MATH::A_Point2d(  0.5,  0.5))[0],   0, eps );
    ASSERT_NEAR( IMG::Interpolate_Nearest_Neighbor( image, MATH::A_Point2d(  1.0,  1.0))[0],   2, eps );
    ASSERT_NEAR( IMG::Interpolate_Nearest_Neighbor( image, MATH::A_Point2d(  1.0,  1.5))[0],   2, eps );
    ASSERT_NEAR( IMG::Interpolate_Nearest_Neighbor( image, MATH::A_Point2d(  1.5,  1.0))[0],   2, eps );
    ASSERT_NEAR( IMG::Interpolate_Nearest_Neighbor( image, MATH::A_Point2d(  1.5,  1.5))[0],   2, eps );
    ASSERT_NEAR( IMG::Interpolate_Nearest_Neighbor( image, MATH::A_Point2d( 99  , 99  ))[0], 198, eps );

}

/**
 * Test Interpolation
*/
TEST( Interpolation, Interpolate_Bilinear_invalid ){

    // Set Image Size
    A_Size<int> image_size(100,100);

    // Create Images
    IMG::Image<IMG::PixelRGB_u16> image01;
    IMG::Image<IMG::PixelRGB_u16> image02(image_size);
    
    // Set Pixel Data
    for( int r=0; r<image_size.Width();  r++ )
    for( int c=0; c<image_size.Height(); c++ )
    for( int x=0; x<3; x++ )
        image02(r,c)[x] = r+c + 1;

    // Empty Images
    ASSERT_EQ( IMG::Interpolate_Bilinear( image01, MATH::A_Point2d(0,0)),  IMG::PixelRGB_u16());
    ASSERT_EQ( IMG::Interpolate_Bilinear( image01, MATH::A_Point2d(3,10)), IMG::PixelRGB_u16());

    // Pixel Below Min
    ASSERT_EQ( IMG::Interpolate_Bilinear( image02, MATH::A_Point2d(-1,-1)), IMG::PixelRGB_u16(1,1,1));
    ASSERT_EQ( IMG::Interpolate_Bilinear( image02, MATH::A_Point2d(-9,-9)), IMG::PixelRGB_u16(1,1,1));

    // Pixel Above Max
    ASSERT_EQ( IMG::Interpolate_Bilinear( image02, MATH::A_Point2d(101,101)), IMG::PixelRGB_u16(199,199,199));
    ASSERT_EQ( IMG::Interpolate_Bilinear( image02, MATH::A_Point2d(101,101)), IMG::PixelRGB_u16(199,199,199));

    // Pixel Generally out of bounds
    ASSERT_EQ( IMG::Interpolate_Bilinear( image02, MATH::A_Point2d(10,101)), IMG::PixelRGB_u16(110,110,110));
    ASSERT_EQ( IMG::Interpolate_Bilinear( image02, MATH::A_Point2d(101,10)), IMG::PixelRGB_u16(110,110,110));

}

/**
 * Test the Interpolate Bilinear Method
*/
TEST( Interpolation, Interpolate_Bilinear ){

    // Epsilon
    const double eps = 0.0001;

    // Define the image size
    A_Size<int> image_size(100,100);

    // Create an image
    IMG::Image<IMG::PixelGray_df> image(image_size);

    // Set Pixel Data
    for( int r=0; r<image_size.Width();  r++ )
    for( int c=0; c<image_size.Height(); c++ )
        image(r,c) = r+c;

    // Test Interpolation
    ASSERT_NEAR( IMG::Interpolate_Bilinear( image, MATH::A_Point2d(  0  ,  0  ))[0],   0, eps );
    ASSERT_NEAR( IMG::Interpolate_Bilinear( image, MATH::A_Point2d(  0.5,  0.5))[0],   1, eps );
    ASSERT_NEAR( IMG::Interpolate_Bilinear( image, MATH::A_Point2d( 98.5, 98.5))[0], 197, eps );
    ASSERT_NEAR( IMG::Interpolate_Bilinear( image, MATH::A_Point2d( 99  , 99  ))[0], 198, eps );
    ASSERT_NEAR( IMG::Interpolate_Bilinear( image, MATH::A_Point2d(  1.0,  1.0))[0],   2, eps );
    ASSERT_NEAR( IMG::Interpolate_Bilinear( image, MATH::A_Point2d(  1.0,  1.5))[0], 2.5, eps );
    ASSERT_NEAR( IMG::Interpolate_Bilinear( image, MATH::A_Point2d(  1.5,  1.0))[0], 2.5, eps );
    ASSERT_NEAR( IMG::Interpolate_Bilinear( image, MATH::A_Point2d(  1.5,  1.5))[0],   3, eps );

}

