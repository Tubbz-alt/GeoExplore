/**
 * @file    TEST_DEM_IO_Driver_Types.cpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#include <gtest/gtest.h>

// GeoExplore Libraries
#include <GeoExplore/dem/DEM_IO_Driver_Types.hpp>

using namespace GEO;

/**
 * Test hte value enumerations
*/
TEST( DEM_IO_Driver_Types, DEM_IO_Driver_Type_static_cast ){

    ASSERT_EQ( static_cast<uint16_t>(DEM::DEM_IO_Driver_Type::UNKNOWN), 0 );
    ASSERT_EQ( static_cast<uint16_t>(DEM::DEM_IO_Driver_Type::BASE), 1 );
    ASSERT_EQ( static_cast<uint16_t>(DEM::DEM_IO_Driver_Type::FLAT), 2 );
    ASSERT_EQ( static_cast<uint16_t>(DEM::DEM_IO_Driver_Type::SRTM), 3 );


}

/** 
* Test the Driver type to string
*/
TEST( DEM_IO_Driver_Types, DEM_IO_Driver_Type_To_String ){

    // Check drivers
    ASSERT_EQ( DEM::DEM_IO_Driver_Type_To_String(DEM::DEM_IO_Driver_Type::UNKNOWN), "UNKNOWN" );
    ASSERT_EQ( DEM::DEM_IO_Driver_Type_To_String(DEM::DEM_IO_Driver_Type::BASE), "BASE" );
    ASSERT_EQ( DEM::DEM_IO_Driver_Type_To_String(DEM::DEM_IO_Driver_Type::FLAT), "FLAT" );
    ASSERT_EQ( DEM::DEM_IO_Driver_Type_To_String(DEM::DEM_IO_Driver_Type::SRTM), "SRTM" );
    

}

/**
 * Test he string to driver type
*/
TEST( DEM_IO_Driver_Types, String_To_DEM_IO_Driver_Type ){

    // Check unknown
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type("UNKNOWN"), DEM::DEM_IO_Driver_Type::UNKNOWN );
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type(""), DEM::DEM_IO_Driver_Type::UNKNOWN );
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type("srt"), DEM::DEM_IO_Driver_Type::UNKNOWN );

    // Check Base
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type("base"), DEM::DEM_IO_Driver_Type::BASE );
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type("BASE"), DEM::DEM_IO_Driver_Type::BASE );
    
    // Check FLAT
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type("flat"), DEM::DEM_IO_Driver_Type::FLAT );
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type("FLAT"), DEM::DEM_IO_Driver_Type::FLAT );
    
    // Check SRTM
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type("SRTM"), DEM::DEM_IO_Driver_Type::SRTM );
    ASSERT_EQ( DEM::String_To_DEM_IO_Driver_Type("srtm"), DEM::DEM_IO_Driver_Type::SRTM );
}
