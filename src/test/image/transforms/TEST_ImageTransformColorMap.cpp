/**
 * @file    TEST_ImageTransformColorMap.cpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/math/A_Point.hpp>
#include <GeoExplore/image/Image.hpp>
#include <GeoExplore/image/MemoryResource.hpp>
#include <GeoExplore/image/Pixel_Types.hpp>
#include <GeoExplore/image/transforms/ImageTransformColorMap.hpp>
#include <GeoExplore/io/opencv_utils/OpenCV_Utilities.hpp>


using namespace GEO;

/**
 * Constructor
*/
TEST( A_Color_Map_Pair,  Constructors ){

    IMG::A_Color_Map_Pair<IMG::PixelGray_df,IMG::PixelRGB_u8> pair02( IMG::PixelGray_df(0.4),
                                                                      IMG::PixelRGB_u8(200,123,100));
    ASSERT_NEAR( pair02.Get_Input_Pixel()[0], 0.4, 0.001 );
    ASSERT_EQ( pair02.Get_Output_Pixel()[0], 200 );
    ASSERT_EQ( pair02.Get_Output_Pixel()[1], 123 );
    ASSERT_EQ( pair02.Get_Output_Pixel()[2], 100 );
    
}


/**
 * Construction with sorting
*/
TEST( A_Color_Map, Constructor_sorted )
{
    // EPS
    const double eps = 0.0001;
    
    // Pixel Values
    IMG::PixelRGB_u8 result;
    
    // Create map 
    IMG::A_Color_Map<IMG::PixelGray_df,IMG::PixelRGB_u8> color_map;
    color_map.Add_Color_Pair(IMG::PixelGray_df( 0), IMG::PixelRGB_u8( 10, 10, 10));
    color_map.Add_Color_Pair(IMG::PixelGray_df(20), IMG::PixelRGB_u8( 30, 30, 30));
    color_map.Add_Color_Pair(IMG::PixelGray_df(10), IMG::PixelRGB_u8( 20, 20, 20));

    // Iterate over values
    ASSERT_EQ( color_map.Get_Number_Of_Color_Map_Pairs(), 3 );
    ASSERT_NEAR( color_map.Get_Color_Map_Pair(0).Get_Input_Pixel()[0], 0, eps );
    ASSERT_NEAR( color_map.Get_Color_Map_Pair(1).Get_Input_Pixel()[0],10, eps );
    ASSERT_NEAR( color_map.Get_Color_Map_Pair(2).Get_Input_Pixel()[0],20, eps );

}


/**
 * Interpolate Color
*/
TEST( A_Color_Map, Interpolate_Color )
{
    
    // Pixel Values
    IMG::PixelRGB_u8 result;
    
    // Create map 
    IMG::A_Color_Map<IMG::PixelGray_df,IMG::PixelRGB_u8> color_map;
    color_map.Add_Color_Pair(IMG::PixelGray_df( 0), IMG::PixelRGB_u8( 10, 10, 10));
    color_map.Add_Color_Pair(IMG::PixelGray_df(10), IMG::PixelRGB_u8( 20, 20, 20));

    // Interpolate
    result = color_map.Interpolate_Color( IMG::PixelGray_df( -1 ));
    ASSERT_EQ( result, IMG::PixelRGB_u8( 10, 10, 10 ));
    
    result = color_map.Interpolate_Color( IMG::PixelGray_df( 0 ));
    ASSERT_EQ( result, IMG::PixelRGB_u8( 10, 10, 10 ));
    
    result = color_map.Interpolate_Color( IMG::PixelGray_df( 10 ));
    ASSERT_EQ( result, IMG::PixelRGB_u8( 20, 20, 20 ));
    
    result = color_map.Interpolate_Color( IMG::PixelGray_df( 11 ));
    ASSERT_EQ( result, IMG::PixelRGB_u8( 20, 20, 20 ));
    
    result = color_map.Interpolate_Color( IMG::PixelGray_df( 5 ));
    ASSERT_EQ( result, IMG::PixelRGB_u8( 15, 15, 15 ));

}

/**
 * Test the Compute Color Map Method
*/
TEST( ImageTransformColorMap, Compute_Color_Map_Gray_df_to_RGB_u8 )
{
    // Define our image size
    A_Size<int> image_size(1000,1000);
    MATH::A_Point2d origin( image_size.Width()/2.0, image_size.Height()/2.0);
    double sigma_x = 200;
    double sigma_y = 200;
    double alpha = 101;
    double base_elevation = 100;

    // Build the color map
    IMG::A_Color_Map<IMG::PixelGray_df,IMG::PixelRGB_u8> color_map;

    // Add the pairs
    color_map.Add_Color_Pair( IMG::PixelGray_df( base_elevation       ), IMG::PixelRGB_u8::Green());
    color_map.Add_Color_Pair( IMG::PixelGray_df( base_elevation +  50 ), IMG::PixelRGB_u8::Red());
    color_map.Add_Color_Pair( IMG::PixelGray_df( base_elevation + 100 ), IMG::PixelRGB_u8::Blue());

    // Generate a terrain map
    IMG::Image<IMG::PixelGray_df>::ptr_t  terrain_data(new IMG::Image<IMG::PixelGray_df>(image_size));

    // Load the data
    double dist;
    for( int r=0; r<image_size.Height(); r++ )
    for( int c=0; c<image_size.Width();  c++ )
    {
        // Compute the gaussian
        dist = MATH::Gaussian2D( MATH::A_Point2d(c,r), origin, sigma_x, sigma_y, alpha );

        // Add to the value
        (*terrain_data)(r,c) = base_elevation + dist - 1;
    }

    // Create output image
    IMG::Image<IMG::PixelRGB_u8>::ptr_t  color_relief_image(new IMG::Image<IMG::PixelRGB_u8>(image_size));

    // Compute the color relief map
    IMG::Compute_Color_Map( terrain_data, color_relief_image, color_map );
    
    // Check the various pixels
    ASSERT_EQ( (*color_relief_image)(0,0)[0],   0 );
    ASSERT_EQ( (*color_relief_image)(0,0)[1], 255 );
    ASSERT_EQ( (*color_relief_image)(0,0)[2],   0 );

    ASSERT_EQ( (*color_relief_image)(image_size.Width()/2,image_size.Height()/2)[0],   0 );
    ASSERT_EQ( (*color_relief_image)(image_size.Width()/2,image_size.Height()/2)[1],   0 );
    ASSERT_EQ( (*color_relief_image)(image_size.Width()/2,image_size.Height()/2)[2], 255 );
    
}

