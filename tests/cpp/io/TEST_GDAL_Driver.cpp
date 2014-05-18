/**
 * @file    TEST_GDAL_Driver.cpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#include<gtest/gtest.h>

/// Boost C++ Library
#include <boost/shared_ptr.hpp>

/// GeoExplore Library 
#include <GeoExplore.hpp>

/// GDAL
#include <gdal/cpl_conv.h>

using namespace std;

/**
 * Test the GDAL Read Image Data for JPEG RGB
*/
TEST( GDAL_Driver, LoadImageJPEGRGB ){
    
    /**
     * Call the load image on a jpeg image 
    */
    int rowSize, colSize;
    typename GEO::IO::GDAL::GDAL_Driver::image_data_type<GEO::PixelRGB_UInt8> pixels = GEO::IO::GDAL::load_image_data<GEO::PixelRGB_UInt8>( "../../tests/data/images/Lenna.jpg", rowSize, colSize);

    /// make sure the image is the right size
    ASSERT_EQ( rowSize, 512);
    ASSERT_EQ( colSize, 512);

    // make sure not all values are non-zero
    bool redNonZero = false;
    bool greenNonZero = false;
    bool blueNonZero = false;
    for( size_t i=0; i<rowSize*colSize; i++ ){
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

/**
 * Test GDAL Short Driver by extension
*/
TEST( GDAL_Driver, GetShortDriverByFilename ){

    ASSERT_EQ( GEO::IO::GDAL::getShortDriverFromFilename("output.png"), "PNG");

}

/**
 * Test ChannelType to GDAL Type
*/
TEST( GDAL_Driver, ChannelType2GDALType ){

    ASSERT_EQ( GEO::IO::GDAL::ctype2gdaltype<double>(), GDT_Unknown );
    ASSERT_EQ( GEO::IO::GDAL::ctype2gdaltype<GEO::ChannelTypeDouble>(), GDT_Float64);


}
