/**
 * @file    TEST_GDAL_Driver.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include<gtest/gtest.h>

/// C++ Standard Library
#include <vector>

/// GeoExplore Library 
#include <GeoExplore.hpp>

using namespace std;

/**
 * Test the GDAL Read Image Data for JPEG RGB
*/
TEST( GDAL_Driver, LoadImageJPEGRGB ){
    
    /**
     * Call the load image on a jpeg image 
    */
    int rowSize;
    std::vector<GEO::PixelRGB_UInt8> pixels = GEO::IO::GDAL::load_image_data<GEO::PixelRGB_UInt8>( "../../tests/data/images/Lenna.jpg", rowSize);

    /// make sure the image is the right size
    ASSERT_EQ( pixels.size(), 512*512);
    ASSERT_EQ( rowSize, 512);

    // make sure not all values are non-zero
    bool redNonZero = false;
    bool greenNonZero = false;
    bool blueNonZero = false;
    for( size_t i=0; i<pixels.size(); i++ ){
        if( pixels[i].r() > 0 ){ redNonZero = true; }
        if( pixels[i].g() > 0 ){ greenNonZero = true; }
        if( pixels[i].b() > 0 ){ blueNonZero = true; }
        
        if( redNonZero == true &&
            greenNonZero == true &&
            blueNonZero == true ){
            break;
        }
    }

    ASSERT_TRUE( redNonZero );
    ASSERT_TRUE( greenNonZero );
    ASSERT_TRUE( blueNonZero );
    

}


