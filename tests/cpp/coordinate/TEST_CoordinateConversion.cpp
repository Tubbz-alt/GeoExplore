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
    GEO::CoordinateBaseDouble::ptr_t coordinate01( new GEO::CoordinateGeodeticDouble(0, 0, 0, GEO::Datum::WGS84 ));
    
    // convert the coordinate
    GEO::CoordinateBaseDouble::ptr_t baseResult01 = GEO::convert_coordinate<double>( coordinate01, GEO::CoordinateType::UTM, GEO::Datum::WGS84 );
    GEO::CoordinateUTMDouble::ptr_t result01 = boost::static_pointer_cast<GEO::CoordinateUTMDouble>(baseResult01);


 }

