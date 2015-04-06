/**
 * @file    TEST_GDAL_Utilities.cpp
 * @author  Marvin Smith
 * @date    4/3/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <coordinate/CoordinateGeographic.hpp>
#include <coordinate/CoordinateUTM.hpp>
#include <image/ChannelType.hpp>
#include <io/gdal_utils/GDAL_Utilities.hpp>

using namespace GEO;

/**
 * Test the ctype2gdaltype
*/
TEST( GDAL_Utilities, ctype2gdaltype )
{
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt8>(), GDT_Byte );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt12>(), GDT_UInt16 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt14>(), GDT_UInt16 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt16>(), GDT_UInt16 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeUInt32>(), GDT_UInt32 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeDouble>(), GDT_Float64 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<IMG::ChannelTypeDoubleFree>(), GDT_Float64 );
    ASSERT_EQ( IO::GDAL::ctype2gdaltype<float>(), GDT_Unknown );

}

/**
 * Test the Short driver from filename
*/
TEST( GDAL_Utilities, Get_Short_Driver_From_Filename )
{
    // Test Unknowns
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.txt")), "");

    // Test JPEG
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.jpg")), "JPEG");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.jpeg")), "JPEG");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.JPG")), "JPEG");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.JPEG")), "JPEG");

    // Test GeoTiff
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.tif")), "GTiff");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.tiff")), "GTiff");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.TIF")), "GTiff");
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.TIFF")), "GTiff");

    // Test PNG
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.png")), "PNG" );
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.PNG")), "PNG" );

    // Test NITF
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.ntf")), "NITF" );
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.nitf")), "NITF" );
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.NTF")), "NITF" );
    ASSERT_EQ( IO::GDAL::Get_Short_Driver_From_Filename(FS::FilesystemPath("image.NITF")), "NITF" );

}


/**
 * Test the Compute Geo Transform with invalid inputs
*/
TEST( GDAL_Utilities, Compute_Geo_Transform_invalid )
{
    // Status
    Status status;
    double * adfGeoTransform = new double[6];

    // Create coordinate and pixel lists
    std::vector<CRD::CoordinateUTM_d>         utm_coordinate_list;
    std::vector<CRD::CoordinateGeographic_d>  geog_coordinate_list;
    std::vector<MATH::A_Point2d>              pixel_list;

    // Test 01 (Run with no input coordinates)
    status = IO::GDAL::Compute_Geo_Transform( pixel_list, geog_coordinate_list, adfGeoTransform );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), (int)GDALStatusReason::TRANSFORM_NOT_ENOUGH_COORDINATES );

    status = IO::GDAL::Compute_Geo_Transform( pixel_list, utm_coordinate_list, adfGeoTransform );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), (int)GDALStatusReason::TRANSFORM_NOT_ENOUGH_COORDINATES );

    // Test 02 (Invalid number of coordinates)
    pixel_list.push_back(MATH::A_Point2d(0,0));
    pixel_list.push_back(MATH::A_Point2d(40,0));
    pixel_list.push_back(MATH::A_Point2d(0,50));
    utm_coordinate_list.push_back(CRD::CoordinateUTM_d( 11, false, 0, 0));
    utm_coordinate_list.push_back(CRD::CoordinateUTM_d( 11, false, 40, 0));
    utm_coordinate_list.push_back(CRD::CoordinateUTM_d( 11, false, 0, 50));
    geog_coordinate_list.push_back(CRD::CoordinateGeographic_d( 11, 12 ));
    geog_coordinate_list.push_back(CRD::CoordinateGeographic_d( 11, 12 ));
    geog_coordinate_list.push_back(CRD::CoordinateGeographic_d( 11, 12 ));
    
    status = IO::GDAL::Compute_Geo_Transform( pixel_list, geog_coordinate_list, adfGeoTransform );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), (int)GDALStatusReason::TRANSFORM_NOT_ENOUGH_COORDINATES );

    status = IO::GDAL::Compute_Geo_Transform( pixel_list, utm_coordinate_list, adfGeoTransform );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), (int)GDALStatusReason::TRANSFORM_NOT_ENOUGH_COORDINATES );
    
    // Test 03 (Pixels don't match the input coordinates
    pixel_list.push_back(MATH::A_Point2d(0,0));
    pixel_list.push_back(MATH::A_Point2d(40,0));
    pixel_list.push_back(MATH::A_Point2d(0,50));
    pixel_list.push_back(MATH::A_Point2d(90,50));
    utm_coordinate_list.push_back(CRD::CoordinateUTM_d( 11, false, 0, 0));
    utm_coordinate_list.push_back(CRD::CoordinateUTM_d( 11, false, 40, 0));
    utm_coordinate_list.push_back(CRD::CoordinateUTM_d( 11, false, 0, 50));
    geog_coordinate_list.push_back(CRD::CoordinateGeographic_d( 11, 12 ));
    geog_coordinate_list.push_back(CRD::CoordinateGeographic_d( 11, 12 ));
    geog_coordinate_list.push_back(CRD::CoordinateGeographic_d( 11, 12 ));
    
    status = IO::GDAL::Compute_Geo_Transform( pixel_list, geog_coordinate_list, adfGeoTransform );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), (int)GDALStatusReason::TRANSFORM_NOT_ENOUGH_COORDINATES );

    status = IO::GDAL::Compute_Geo_Transform( pixel_list, utm_coordinate_list, adfGeoTransform );
    ASSERT_EQ( status.Get_Status_Type(), StatusType::FAILURE );
    ASSERT_EQ( (int)status.Get_Status_Reason(), (int)GDALStatusReason::TRANSFORM_NOT_ENOUGH_COORDINATES );
    

    // Clean Up
    delete [] adfGeoTransform;
}

/**
 * Test the Compute Geo Transform Method.
 */
TEST( GDAL_Utilities, Compute_Geo_Transform_geographic )
{
    // EPS
    const double eps = 0.01;

    // Status
    Status status;

    // Create a set of coordinate pairs to test
    std::vector<CRD::CoordinateGeographic_d> coordinates;
    std::vector<MATH::A_Point2d> pixels;

    coordinates.push_back(CRD::CoordinateGeographic_d(39.7, -119.7));
    pixels.push_back(MATH::A_Point2d(0,0));

    coordinates.push_back(CRD::CoordinateGeographic_d(39.7, -119.2));
    pixels.push_back(MATH::A_Point2d(750,0));
    
    coordinates.push_back(CRD::CoordinateGeographic_d(39.2, -119.7));
    pixels.push_back(MATH::A_Point2d(0,1200));
    
    coordinates.push_back(CRD::CoordinateGeographic_d(39.2, -119.2));
    pixels.push_back(MATH::A_Point2d(750,1200));
    
    // Compute the Geo Transform
    double* adfGeoTransform = new double[6];
    status = IO::GDAL::Compute_Geo_Transform( pixels, coordinates, adfGeoTransform );

    // Check the results
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_NEAR( adfGeoTransform[0], -119.7, eps );
    ASSERT_NEAR( adfGeoTransform[1], 0.0007, eps );
    ASSERT_NEAR( adfGeoTransform[2],      0, eps );
    ASSERT_NEAR( adfGeoTransform[3],  39.70, eps );
    ASSERT_NEAR( adfGeoTransform[4],      0, eps );
    ASSERT_NEAR( adfGeoTransform[5],      0, eps );
    
    delete [] adfGeoTransform;
}

/**
 * Test the Compute Geo Transform Method.
 */
TEST( GDAL_Utilities, Compute_Geo_Transform_utm )
{
    
    // EPS
    const double eps = 0.01;

    // Status
    Status status;

    // Create a set of coordinate pairs to test
    std::vector<CRD::CoordinateUTM_d> coordinates;
    std::vector<MATH::A_Point2d> pixels;

    coordinates.push_back(CRD::CoordinateUTM_d(11, false, -119.7, 39.7));
    pixels.push_back(MATH::A_Point2d(0,0));

    coordinates.push_back(CRD::CoordinateUTM_d(11, false, -119.2, 39.7));
    pixels.push_back(MATH::A_Point2d(750,0));
    
    coordinates.push_back(CRD::CoordinateUTM_d(11, false, -119.7, 39.2));
    pixels.push_back(MATH::A_Point2d(0,1200));
    
    coordinates.push_back(CRD::CoordinateUTM_d(11, false, -119.2, 39.2));
    pixels.push_back(MATH::A_Point2d(750,1200));
    
    // Compute the Geo Transform
    double* adfGeoTransform = new double[6];
    status = IO::GDAL::Compute_Geo_Transform( pixels, coordinates, adfGeoTransform );

    // Check the results
    ASSERT_EQ( status.Get_Status_Type(), StatusType::SUCCESS );
    ASSERT_NEAR( adfGeoTransform[0], -119.7, eps );
    ASSERT_NEAR( adfGeoTransform[1], 0.0007, eps );
    ASSERT_NEAR( adfGeoTransform[2],      0, eps );
    ASSERT_NEAR( adfGeoTransform[3],  39.70, eps );
    ASSERT_NEAR( adfGeoTransform[4],      0, eps );
    ASSERT_NEAR( adfGeoTransform[5],      0, eps );
    
    delete [] adfGeoTransform;

}

/**************************************************************/
/*      Test the GDAL Process OGR from Metadata Method        */
/**************************************************************/
TEST( GDAL_Utilities, GDAL_Process_OGR_From_Metadata )
{
    // EPS
    const double eps = 0.01;
    
    // Misc Variables
    int zone, isNorth;
    double* adfGeoTransform = new double[6];
    IMG::MetadataContainer::ptr_t metadata(new IMG::MetadataContainer());
    OGRSpatialReference oSRS;
    A_Size<int> image_size(100,100);

    // TEST 01 (Run method on null metadata container)
    ASSERT_FALSE( IO::GDAL::GDAL_Process_OGR_From_Metadata( nullptr,
                                                            image_size,
                                                            oSRS,
                                                            adfGeoTransform ));

    // TEST 02 (Empty Metadata Container )
    ASSERT_FALSE( IO::GDAL::GDAL_Process_OGR_From_Metadata( metadata,
                                                            image_size,
                                                            oSRS,
                                                            adfGeoTransform ));

    // TEST 03 (4 corners, UTM)
    // 11, true, 384409, 4048901
    metadata->Clear();
    metadata->Add_Metadata_Entry("IS_PROJECTED", "TRUE");
    metadata->Add_Metadata_Entry("IS_UTM", "TRUE");
    metadata->Add_Metadata_Entry("UTM_ZONE", 11);
    metadata->Add_Metadata_Entry("UTM_IS_NORTHERN", "TRUE" );
    metadata->Add_Metadata_Entry("CORNER_COORDINATE_TL_X", 384409);
    metadata->Add_Metadata_Entry("CORNER_COORDINATE_TL_Y", 4048901);
    metadata->Add_Metadata_Entry("CORNER_COORDINATE_TR_X", 384459);
    metadata->Add_Metadata_Entry("CORNER_COORDINATE_TR_Y", 4048901);
    metadata->Add_Metadata_Entry("CORNER_COORDINATE_BL_X", 384409);
    metadata->Add_Metadata_Entry("CORNER_COORDINATE_BL_Y", 4048801);
    metadata->Add_Metadata_Entry("CORNER_COORDINATE_BR_X", 384459);
    metadata->Add_Metadata_Entry("CORNER_COORDINATE_BR_Y", 4048801);
    ASSERT_TRUE( IO::GDAL::GDAL_Process_OGR_From_Metadata( metadata,
                                                           image_size,
                                                           oSRS,
                                                           adfGeoTransform ));
    
    ASSERT_EQ( oSRS.GetUTMZone(&isNorth), 11);
    ASSERT_EQ( isNorth, 1);
    ASSERT_NEAR( adfGeoTransform[0], 384409, eps );
    ASSERT_NEAR( adfGeoTransform[1], 0.49999999999954525, eps );
    ASSERT_NEAR( adfGeoTransform[2], 0, eps );
    ASSERT_NEAR( adfGeoTransform[3], 4048901, eps );
    ASSERT_NEAR( adfGeoTransform[4], 0, eps );
    ASSERT_NEAR( adfGeoTransform[5], -0.99999999998544808, eps );


    // Clean up
    delete [] adfGeoTransform;

}


