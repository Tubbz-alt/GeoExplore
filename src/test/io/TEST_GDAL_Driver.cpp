/**
 * @file    TEST_GDAL_Driver.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include "../lib/coordinate/CoordinateGeographic.hpp"
#include "../lib/coordinate/CoordinateUTM.hpp"
#include "../lib/image/DiskResource.hpp"
#include "../lib/image/MemoryResource.hpp"
#include "../lib/image/Pixel_Types.hpp"
#include "../lib/io/GDAL_Driver.hpp"

using namespace GEO;

/**
 * GDAL Driver Constructor
*/
TEST( ImageDriverGDAL, Default_Constructors ){

    // Create RGB_u8 GDAL_Driver
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>> gdal_driver_rgb_u8;
    ASSERT_FALSE( gdal_driver_rgb_u8.Is_Open() );

}

/**
 * Get Image Driver TYpe
*/
TEST( ImageDriverGDAL, Get_ImageDriverType ){

    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>> gdal_driver01;
    IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGB_u8>> gdal_driver02;
    
    ASSERT_EQ( gdal_driver01.Get_ImageDriverType(), ImageDriverType::GDAL );
    ASSERT_EQ( gdal_driver02.Get_ImageDriverType(), ImageDriverType::GDAL );

}

/**
 * GDAL Is_Read_Supported Method
*/
TEST( ImageDriverGDAL, Is_Read_Supported ){

    // Expected strings
    const std::string tiff_test_01 = "/root/image.tiff";
    const std::string tiff_test_02 = "/root/image.tif";
    const std::string tiff_test_03 = "/root/image.TIF";
    const std::string tiff_test_04 = "/root/image.TIFF";
    const std::string tiff_test_05 = "image.tif";
    const std::string tiff_test_06 = "image.tiff";
    const std::string tiff_test_07 = "image.TIF";
    const std::string tiff_test_08 = "image.TIFF";

    // Test PNG and other unknowns
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u12>>::Is_Read_Supported("Image.png"));
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u12>>::Is_Read_Supported("Image.txt"));
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u12>>::Is_Read_Supported("Image.j2k"));

    // Test Tiff
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_01 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_02 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_03 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_04 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_05 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_06 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_07 ) );
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Read_Supported( tiff_test_08 ) );
    
    // Test J2k
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u12>>::Is_Read_Supported("image.jp2"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u12>>::Is_Read_Supported("image.JP2"));
    
    // Test  Jpeg
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelGray_df>>::Is_Read_Supported("image.jpg"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelGray_df>>::Is_Read_Supported("image.jpeg"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelGray_df>>::Is_Read_Supported("image.JPEG"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelGray_df>>::Is_Read_Supported("image.JPG"));

    // Test DTED
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGB_u16>>::Is_Read_Supported("/root/image.dt1"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGB_u16>>::Is_Read_Supported("/root/image.dt0"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGB_u16>>::Is_Read_Supported("/root/image.DT2"));
    
    // Read srtm
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::DiskResource<IMG::PixelRGBA_df>>::Is_Read_Supported("file.hgt"));

    // Read nitf
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u8>>::Is_Read_Supported("image.ntf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u8>>::Is_Read_Supported("image.nitf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u8>>::Is_Read_Supported("image.NTF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_u8>>::Is_Read_Supported("image.NITF"));

}

/**
 * GDAL Is_Write_Supported Method
*/
TEST( ImageDriverGDAL, Is_Write_Supported ){

    // Make sure most formats fail  
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported(""));
    ASSERT_FALSE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.txt"));
    
    // Test NITF
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.ntf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.nitf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.NTF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.NITF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("../image.ntf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("../image.nitf"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("../image.NTF"));

    // Test Tiff
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.tif"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("/image.tif"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.tiff"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("/image.tiff"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.TIF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("/../image.TIF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("image.TIFF"));
    ASSERT_TRUE( IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>::Is_Write_Supported("/../image.TIFF"));
}

/**
 * Test the Get OGR Spatial Reference Method
*/
TEST( ImageDriverGDAL, Get_OGR_Spatial_Reference_invalid_data ){

    // Create some files
    boost::filesystem::path path01("file-that-does-not-exist");
    boost::filesystem::path path02("CMakeLists.txt");

    // Create an empty driver
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  driver01;
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  driver02(path01);
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  driver03(path02);

    // Call the method
    OGRSpatialReference ogr_spatial_reference01;
    OGRSpatialReference ogr_spatial_reference02;
    OGRSpatialReference ogr_spatial_reference03;
    
    ASSERT_FALSE( driver01.Get_OGR_Spatial_Reference( ogr_spatial_reference01 ));
    ASSERT_FALSE( driver02.Get_OGR_Spatial_Reference( ogr_spatial_reference02 ));
    ASSERT_FALSE( driver03.Get_OGR_Spatial_Reference( ogr_spatial_reference03 ));
    
}


/**
 * Test the Get OGR Spatial Reference Method
*/
TEST( ImageDriverGDAL, Get_OGR_Spatial_Reference_valid_data ){

    // Define EPS
    const double eps = 0.00001;

    // pick some files to load
    boost::filesystem::path path01("data/unit-tests/dems/srtm/N39W120.hgt");
    boost::filesystem::path path02("data/unit-tests/images/i_3001a.ntf");
    boost::filesystem::path path03("data/unit-tests/images/erdas_spnad83.tif");

    // Make sure the files exist
    if( boost::filesystem::exists(path01) == false ||
        boost::filesystem::exists(path02) == false ||
        boost::filesystem::exists(path03) == false )
    {
        std::cerr << "Files don't exist. Test will fail." << std::endl;
        FAIL();
    }

    // Create GDAL Drivers
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  driver01(path01);
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u8>> driver02(path02);
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u8>> driver03(path03);

    // Open the driver
    driver01.Open();
    driver02.Open();
    driver03.Open();

    // Check that they are open
    ASSERT_TRUE( driver01.Is_Open() );
    ASSERT_TRUE( driver02.Is_Open() );
    ASSERT_TRUE( driver03.Is_Open() );
    
    // Call the Get methods
    OGRSpatialReference ogr_spatial_reference01;
    OGRSpatialReference ogr_spatial_reference02;
    OGRSpatialReference ogr_spatial_reference03;

    ASSERT_TRUE( driver01.Get_OGR_Spatial_Reference( ogr_spatial_reference01 ) );
    ASSERT_TRUE( driver02.Get_OGR_Spatial_Reference( ogr_spatial_reference02 ) );
    ASSERT_TRUE( driver03.Get_OGR_Spatial_Reference( ogr_spatial_reference03 ) );

    // Check the output
    ASSERT_TRUE( ogr_spatial_reference01.IsGeographic() );
    ASSERT_TRUE( ogr_spatial_reference02.IsGeographic() );
    ASSERT_TRUE( ogr_spatial_reference03.IsProjected() );
}



/**
 * Check the Geo Geo Transform Method with Invalid Data
*/
TEST( ImageDriverGDAL, Get_GDAL_Geo_Transform_invalid_data ){

    // Sample transform
    double adf_transform[6];

    // Create some files
    boost::filesystem::path path01("file-that-does-not-exist");

    // Create an empty driver
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  driver01;
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  driver02(path01);

    // Make sure it fails
    ASSERT_FALSE( driver01.Get_GDAL_Geo_Transform( adf_transform ));
    ASSERT_FALSE( driver02.Get_GDAL_Geo_Transform( adf_transform ));

    // Try to open both
    driver01.Open();
    driver02.Open();

    ASSERT_FALSE( driver01.Is_Open() );
    ASSERT_FALSE( driver02.Is_Open() );
    
    // Make sure it fails
    ASSERT_FALSE( driver01.Get_GDAL_Geo_Transform( adf_transform ));
    ASSERT_FALSE( driver02.Get_GDAL_Geo_Transform( adf_transform ));

}


/**
 * Check the Get Geo Transform Method
*/
TEST( ImageDriverGDAL, Get_GDAL_Geo_Transform_valid_data ){

    // Define EPS
    const double eps = 0.00001;

    // pick some files to load
    boost::filesystem::path path01("data/unit-tests/dems/srtm/N39W120.hgt");
    boost::filesystem::path path02("data/unit-tests/images/i_3001a.ntf");

    // Make sure the files exist
    if( boost::filesystem::exists(path01) == false ||
        boost::filesystem::exists(path02) == false )
    {
        std::cerr << "Files don't exist. Test will fail." << std::endl;
        FAIL();
    }

    // Create GDAL Drivers
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  driver01(path01);
    IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u8>> driver02(path02);

    // Get the transforms
    double adf_transform01[6];
    double adf_transform02[6];

    double exp_adf_transform_01[6];
    double exp_adf_transform_02[6];
    exp_adf_transform_01[0] = -120.000139;
    exp_adf_transform_01[1] =    0.000278;
    exp_adf_transform_01[2] =    0;
    exp_adf_transform_01[3] =   40.000139;
    exp_adf_transform_01[4] =    0;
    exp_adf_transform_01[5] =   -0.000278;
    
    exp_adf_transform_02[0] =  85.0;
    exp_adf_transform_02[1] =   0;
    exp_adf_transform_02[2] =   0;
    exp_adf_transform_02[3] =  32.983333;
    exp_adf_transform_02[4] =   0;
    exp_adf_transform_02[5] =   0;


    // Make sure it fails before opening
    ASSERT_FALSE( driver01.Get_GDAL_Geo_Transform( adf_transform01 ) );
    ASSERT_FALSE( driver02.Get_GDAL_Geo_Transform( adf_transform02 ) );
     
    // Open each
    driver01.Open();
    driver02.Open();

    // Make sure the drivers are open
    ASSERT_TRUE( driver01.Is_Open() );
    ASSERT_TRUE( driver02.Is_Open() );
    
    // Make sure it passes after opening
    ASSERT_TRUE( driver01.Get_GDAL_Geo_Transform( adf_transform01 ) );
    ASSERT_TRUE( driver02.Get_GDAL_Geo_Transform( adf_transform02 ) );


    // Check values
    ASSERT_NEAR( adf_transform01[0], exp_adf_transform_01[0], eps );
    ASSERT_NEAR( adf_transform01[1], exp_adf_transform_01[1], eps );
    ASSERT_NEAR( adf_transform01[2], exp_adf_transform_01[2], eps );
    ASSERT_NEAR( adf_transform01[3], exp_adf_transform_01[3], eps );
    ASSERT_NEAR( adf_transform01[4], exp_adf_transform_01[4], eps );
    ASSERT_NEAR( adf_transform01[5], exp_adf_transform_01[5], eps );
    
    ASSERT_NEAR( adf_transform02[0], exp_adf_transform_02[0], eps );
    ASSERT_NEAR( adf_transform02[1], exp_adf_transform_02[1], eps );
    ASSERT_NEAR( adf_transform02[2], exp_adf_transform_02[2], eps );
    ASSERT_NEAR( adf_transform02[3], exp_adf_transform_02[3], eps );
    ASSERT_NEAR( adf_transform02[4], exp_adf_transform_02[4], eps );
    ASSERT_NEAR( adf_transform02[5], exp_adf_transform_02[5], eps );

}

/**
 * Test Get Image Extent
*/
TEST( ImageDriverGDAL, Compute_Image_Extent_invalid_data ){

    // Status
    Status status;

    // Pick an invalid file
    boost::filesystem::path path01("file-that-does-not-exist");
    boost::filesystem::path path02("CMakeLists.txt");

    // Define the types
    typedef IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  DriverType01;
    typedef IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u8>> DriverType02;
    typedef IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelGray_df>> DriverType03;

    // Run the method
    DriverType01::Compute_Image_Extent<CRD::CoordinateUTM_d>( path01, status );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    

    FAIL();
}

/**
 * Test Get Image Extent 
*/
TEST( ImageDriverGDAL, Compute_Image_Extent_valid_data ){


    // Status
    Status status;

    // Define EPS
    const double eps = 0.00001;

    // pick some files to load
    boost::filesystem::path path01("data/unit-tests/dems/srtm/N39W120.hgt");
    boost::filesystem::path path02("data/unit-tests/images/i_3001a.ntf");

    // Make sure the files exist
    if( boost::filesystem::exists(path01) == false ||
        boost::filesystem::exists(path02) == false )
    {
        std::cerr << "Files don't exist. Test will fail." << std::endl;
        FAIL();
    }

    // Define our types
    typedef IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGB_u8>>  DriverType01;
    typedef IO::GDAL::ImageDriverGDAL<IMG::MemoryResource<IMG::PixelRGBA_u8>> DriverType02;

    // Run the method
    MATH::A_Rectangle<CRD::CoordinateUTM_d> rectangle01 = DriverType01::Compute_Image_Extent<CRD::CoordinateUTM_d>( path01, status );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    
    MATH::A_Rectangle<CRD::CoordinateGeographic_d> rectangle02 = DriverType02::Compute_Image_Extent<CRD::CoordinateGeographic_d>( path02, status );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    
    // Expected values
    const int exp_zone_01 = 45;
    const bool exp_is_northern_01 = true;
    const double exp_easting_meters_01 = 313117.6;
    const double exp_northing_meters_01 = 3651215.4;
    const Datum exp_datum_01 = Datum::WGS84;

    // Check the extents
    ASSERT_EQ( rectangle01.TL().zone(), exp_zone_01 );
    ASSERT_TRUE( rectangle01.TL().Is_Northern_Hemisphere() );
    ASSERT_NEAR( rectangle01.TL().easting_meters(),   exp_easting_meters_01,  eps );
    ASSERT_NEAR( rectangle01.TL().northing_meters(),  exp_northing_meters_01, eps );
    ASSERT_EQ( rectangle01.TL().datum(),            exp_datum_01 );
    FAIL();
}

