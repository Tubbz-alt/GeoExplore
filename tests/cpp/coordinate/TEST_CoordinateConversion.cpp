/**
 * @file    TEST_CoordinateConversion.cpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#include <gtest/gtest.h>

#include <GeoExplore.hpp>

 /**
  * Test the Coordinate Conversion 
 */
 TEST( CoordinateConversion, Geodetic2Geodetic ){

    // create a geodetic coordinate
    GEO::CoordinateGeodetic_d coordinate01(0, 0, 0, GEO::Datum::WGS84);
    
    // convert the coordinate
    GEO::CoordinateUTM_d result01 = GEO::convert_coordinate( coordinate01 );

    // test the output


}

