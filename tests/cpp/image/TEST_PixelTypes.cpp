/**
 * @file    TEST_PixelTypes.cpp
 * @author  Marvin Smith
 * @date    5/7/2014
*/
#include <gtest/gtest.h>

/// GeoExplore
#include <GeoExplore.hpp>

/**
 * Test the constructor for PixelRGB 
*/
TEST( PixelRGB, Constructors ){

    /// Create a RGB Pixel Double
    GEO::PixelRGB_Double pixel01(0, 0.5, 1);
    ASSERT_NEAR( pixel01.r(),   0, 0.0001 );
    ASSERT_NEAR( pixel01.g(), 0.5, 0.0001 );
    ASSERT_NEAR( pixel01.b(), 1.0, 0.0001 );
    
    /// Create another RGB Double Pixel
    GEO::PixelRGB_Double pixel02;
    ASSERT_NEAR( pixel02.r(), 0, 0.0001 );
    ASSERT_NEAR( pixel02.g(), 0, 0.0001 );
    ASSERT_NEAR( pixel02.b(), 0, 0.0001 );

    /// Create the last RGB Double Pixel
    GEO::PixelRGB_Double pixel03(0.25);
    ASSERT_NEAR( pixel03.r(), 0.25, 0.0001 );
    ASSERT_NEAR( pixel03.g(), 0.25, 0.0001 );
    ASSERT_NEAR( pixel03.b(), 0.25, 0.0001 );
    
    /// Create a RGB Pixel UInt8
    GEO::PixelRGB_UInt8 pixel04;
    ASSERT_EQ( pixel04.r(), 0 );
    ASSERT_EQ( pixel04.g(), 0 );
    ASSERT_EQ( pixel04.b(), 0 );
    
    GEO::PixelRGB_UInt8 pixel05(100);
    ASSERT_EQ( pixel05.r(), 100 );
    ASSERT_EQ( pixel05.g(), 100 );
    ASSERT_EQ( pixel05.b(), 100 );
    
    GEO::PixelRGB_UInt8 pixel06(50,150,250);
    ASSERT_EQ( pixel06.r(),  50 );
    ASSERT_EQ( pixel06.g(), 150 );
    ASSERT_EQ( pixel06.b(), 250 );
    
    /// Create a RGB Pixel UInt12
    GEO::PixelRGB_UInt12 pixel07; 
    ASSERT_EQ( pixel07.r(), 0 );
    ASSERT_EQ( pixel07.g(), 0 );
    ASSERT_EQ( pixel07.b(), 0 );
    
    GEO::PixelRGB_UInt12 pixel08(2000);
    ASSERT_EQ( pixel08.r(), 2000 );
    ASSERT_EQ( pixel08.g(), 2000 );
    ASSERT_EQ( pixel08.b(), 2000 );
    
    GEO::PixelRGB_UInt12 pixel09(0, 2000, 4095);
    ASSERT_EQ( pixel09.r(),    0 );
    ASSERT_EQ( pixel09.g(), 2000 );
    ASSERT_EQ( pixel09.b(), 4095 );
    

    /// Create a RGB Pixel UInt14
    GEO::PixelRGB_UInt14 pixel10;
    ASSERT_EQ( pixel10.r(), 0 );
    ASSERT_EQ( pixel10.g(), 0 );
    ASSERT_EQ( pixel10.b(), 0 );
    
    GEO::PixelRGB_UInt14 pixel11(10000);
    ASSERT_EQ( pixel11.r(), 10000 );
    ASSERT_EQ( pixel11.g(), 10000 );
    ASSERT_EQ( pixel11.b(), 10000 );
    
    GEO::PixelRGB_UInt14 pixel12(0, 10000, 16383);
    ASSERT_EQ( pixel12.r(), 0 );
    ASSERT_EQ( pixel12.g(), 10000 );
    ASSERT_EQ( pixel12.b(), 16383 );
    
    
    /// Create a RGB Pixel UInt16
    GEO::PixelRGB_UInt16 pixel13;
    ASSERT_EQ( pixel13.r(), 0 );
    ASSERT_EQ( pixel13.g(), 0 );
    ASSERT_EQ( pixel13.b(), 0 );
    
    GEO::PixelRGB_UInt16 pixel14(30000);
    ASSERT_EQ( pixel14.r(), 30000 );
    ASSERT_EQ( pixel14.g(), 30000 );
    ASSERT_EQ( pixel14.b(), 30000 );
    
    GEO::PixelRGB_UInt16 pixel15(0, 30000, 65535);
    ASSERT_EQ( pixel15.r(), 0 );
    ASSERT_EQ( pixel15.g(), 30000 );
    ASSERT_EQ( pixel15.b(), 65535 );
    
    
    /// Create a RGB Pixel UInt32
    GEO::PixelRGB_UInt32 pixel16;
    ASSERT_EQ( pixel16.r(), 0 );
    ASSERT_EQ( pixel16.g(), 0 );
    ASSERT_EQ( pixel16.b(), 0 );
    
    GEO::PixelRGB_UInt32 pixel17(2294967295);
    ASSERT_EQ( pixel17.r(), 2294967295 );
    ASSERT_EQ( pixel17.g(), 2294967295 );
    ASSERT_EQ( pixel17.b(), 2294967295 );
    
    GEO::PixelRGB_UInt32 pixel18(0, 2294967295,4294967295);
    ASSERT_EQ( pixel18.r(),  0 );
    ASSERT_EQ( pixel18.g(), 2294967295 );
    ASSERT_EQ( pixel18.b(), 4294967295 );
    

}

/**
 * PixelGray Constructors
*/
TEST( PixelGray, Constructors ){

    /// Create PixelGray Double
    GEO::PixelGray_Double pixel01;
    ASSERT_NEAR( pixel01.val(), 0, 0.00001 );

    GEO::PixelGray_Double pixel02(1);
    ASSERT_NEAR( pixel02.val(), 1, 0.00001 );

    /// Create PixelGray UInt8
    GEO::PixelGray_UInt8  pixel03;
    ASSERT_EQ( pixel03.val(), 0 );

    GEO::PixelGray_UInt8  pixel04(255);
    ASSERT_EQ( pixel04.val(), 255 );
    
    /// Create PixelGray UInt12
    GEO::PixelGray_UInt12 pixel05;
    ASSERT_EQ( pixel05.val(), 0 );
    
    GEO::PixelGray_UInt12 pixel06(4095);
    ASSERT_EQ( pixel06.val(), 4095 );

    /// Create PixelGray UInt14
    GEO::PixelGray_UInt14 pixel07;
    ASSERT_EQ( pixel07.val(), 0);
    
    GEO::PixelGray_UInt14 pixel08(16383);
    ASSERT_EQ( pixel08.val(), 16383 );

    /// Create PixelGray UInt16
    GEO::PixelGray_UInt16 pixel09;
    ASSERT_EQ( pixel09.val(), 0 );

    GEO::PixelGray_UInt16 pixel10(65535);
    ASSERT_EQ( pixel10.val(), 65535);

    /// Create PixelGray UInt32
    GEO::PixelGray_UInt32 pixel11;
    ASSERT_EQ( pixel11.val(), 0 );
    
    GEO::PixelGray_UInt32 pixel12(4294967295);
    ASSERT_EQ( pixel12.val(), 4294967295 );

}   

/**
 * Test Pixel Type Casting
*/
TEST( PixelTypes, PixelCast ){

    // RGB to Grayscale uint8
    GEO::PixelRGB_u8  testPixel01( 0, 0, 0);
    GEO::PixelGray_u8 result01 = GEO::pixel_cast<GEO::ChannelTypeUInt8>(testPixel01);
    ASSERT_EQ( result01[0], 0 );

    // RGB_d to Grayscale uint8
    GEO::PixelRGB_d   testPixel03( 0.25, 0.5, 1);
    GEO::PixelGray_u8 result03 = GEO::pixel_cast<GEO::ChannelTypeUInt8>(testPixel03);
    ASSERT_EQ( result03[0], 148);

    // Grayscale to RGB
    GEO::PixelGray_u8 testPixel02( 0 );
    GEO::PixelRGB_u8  result02 = GEO::pixel_cast<GEO::ChannelTypeUInt8>(testPixel02);
    ASSERT_EQ( result02[0], 0 );
    ASSERT_EQ( result02[1], 0 );
    ASSERT_EQ( result02[2], 0 );
    
    // Grayscale to RGB
    GEO::PixelGray_u8 testPixel04( 100 );
    GEO::PixelRGB_d   result04 = GEO::pixel_cast<GEO::ChannelTypeDouble>(testPixel04);
    ASSERT_NEAR( result04[0], 100.0/255, 0.001 );
    ASSERT_NEAR( result04[1], 100.0/255, 0.001 );
    ASSERT_NEAR( result04[2], 100.0/255, 0.001 );
    
}


