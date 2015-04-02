/**
  *  @file   OGR_Driver.cpp
  *  @author Marvin Smith
  *  @date   5/3/2014
*/
#include "OGR_Driver.hpp"

/// OGR Bindings
#include <ogr_spatialref.h>

/// C++ Standard Libraries
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace  GEO {
namespace  OGR {

/**
 *  Default Constructor
*/
OGR_Driver::OGR_Driver(){



}

/**
 * Compute the best utm zone.
*/
int compute_UTM_Zone( double const& longitude ){

    // compute the appropriate UTM Zone
    return ((int)std::floor(( longitude + 180 )/6.0) + 1);
}


/**
 *  Convert from UTM to Geographic
*/
void convert_UTM2Geographic( int const&    fromZone,
                           double const& fromEasting,  
                           double const& fromNorthing,  
                           double const& fromAltitude,    
                           Datum const&  fromDatum,
                           Datum const&  toDatum,
                           double&       toLatitude, 
                           double&       toLongitude, 
                           double&       toAltitude )
{ 

    // create a pair of spatial reference objects
    OGRSpatialReference sourceSRS, targetSRS;

    //set it to the required DATUM
    sourceSRS.SetWellKnownGeogCS( Datum2WKT_string(fromDatum).c_str());
    targetSRS.SetWellKnownGeogCS( Datum2WKT_string(toDatum).c_str());

    // set the source UTM Components
    sourceSRS.SetUTM( fromZone, fromNorthing >= 0 );
    
    // Create the Coordinate Transformation
    OGRCoordinateTransformation *poTransform = OGRCreateCoordinateTransformation( &sourceSRS, &targetSRS );
    if( poTransform == NULL ){
        throw std::runtime_error("ERROR: call failed");
    }

    double x = fromEasting;
    double y = fromNorthing;
    double z = fromAltitude;
    
    if( !poTransform->Transform( 1, &x, &y, &z ) )
        throw std::runtime_error("ERROR: transform failed");
   
    OCTDestroyCoordinateTransformation( poTransform );

    // set the output
    toLatitude  = y;
    toLongitude = x;
    toAltitude  = z;
}


/**
 * Convert From UTM to geographic
 */
void convert_UTM2Geographic_list( int const& number_points,
                                  int  const& fromZone,
                                  bool const& fromHemi,
                                  Datum const& fromDatum,
                                  Datum const& toDatum,
                                  double*& x,
                                  double*& y,
                                  double*& z )
{

    // Make sure the inputs are not null
    if( x == NULL || x == nullptr ||
        y == NULL || y == nullptr ||
        z == NULL || z == nullptr  ){
        return;
    }

    // Create the OGR Reference Object
    OGRSpatialReference sourceSRS, targetSRS;

    // Set the datums
    sourceSRS.SetWellKnownGeogCS( Datum2WKT_string(fromDatum).c_str());
    targetSRS.SetWellKnownGeogCS( Datum2WKT_string(toDatum).c_str());

    // set the source UTM Components
    sourceSRS.SetUTM( fromZone, fromHemi );
    
    // Create the Coordinate Transformation
    OGRCoordinateTransformation *poTransform = OGRCreateCoordinateTransformation( &sourceSRS, &targetSRS );
    if( poTransform == NULL ){
        throw std::runtime_error("ERROR: call failed");
    }

    if( !poTransform->Transform( number_points, x, y, z ) )
        throw std::runtime_error("ERROR: transform failed");
   
    OCTDestroyCoordinateTransformation( poTransform );

}


/**
 * Convert from Geographic to UTM
*/
void convert_Geographic2UTM( double const& fromLatitude,
                           double const& fromLongitude,
                           double const& fromAltitude,
                           Datum const&  fromDatum,
                           Datum const&  toDatum,
                           int&          toZone,
                           double&       toEasting,
                           double&       toNorthing,
                           double&       toAltitude
                           )
{


    /// create the spatial references objects
    OGRSpatialReference sourceSRS, targetSRS;

    // set it to the required Datum
    sourceSRS.SetWellKnownGeogCS( Datum2WKT_string(fromDatum).c_str());
    targetSRS.SetWellKnownGeogCS( Datum2WKT_string(toDatum  ).c_str());

    // set the required utm components
    toZone = compute_UTM_Zone( fromLongitude );
    targetSRS.SetUTM( toZone, fromLatitude >= 0);

    // create the coordinate conversion
    OGRCoordinateTransformation *poTransform = OGRCreateCoordinateTransformation( &sourceSRS, &targetSRS );
    if( poTransform == NULL ){
        throw std::runtime_error("error: Call failed.");
    }
    
    double x = fromLongitude;
    double y = fromLatitude;
    double z = fromAltitude;

    if( !poTransform->Transform( 1, &x, &y, &z ))
        throw std::runtime_error("error: Transform failed.");

    // set the output
    toEasting  = x;
    toNorthing = y;
    toAltitude = z;

}


/**
 * Convert from Geographic to UTM
*/
void convert_Geographic2UTM_fixedZone( double const& fromLatitude,
                                     double const& fromLongitude,
                                     double const& fromAltitude,
                                     Datum const&  fromDatum,
                                     Datum const&  toDatum,
                                     int const&    toZone,
                                     double&       toEasting,
                                     double&       toNorthing,
                                     double&       toAltitude
                                    )
{

    /// create the spatial references objects
    OGRSpatialReference sourceSRS, targetSRS;

    // set it to the required Datum
    sourceSRS.SetWellKnownGeogCS( Datum2WKT_string(fromDatum).c_str());
    targetSRS.SetWellKnownGeogCS( Datum2WKT_string(toDatum  ).c_str());

    // set the required utm components
    targetSRS.SetUTM( toZone, fromLatitude >= 0);

    // create the coordinate conversion
    OGRCoordinateTransformation *poTransform = OGRCreateCoordinateTransformation( &sourceSRS, &targetSRS );
    if( poTransform == NULL ){
        throw std::runtime_error("error: Call failed.");
    }
    
    double x = fromLongitude;
    double y = fromLatitude;
    double z = fromAltitude;

    if( !poTransform->Transform( 1, &x, &y, &z ))
        throw std::runtime_error("error: Transform failed.");

    // set the output
    toEasting  = x;
    toNorthing = y;
    toAltitude = z;

}



}  /// End of OGR Namespace
}  /// End of GEO Namespace
