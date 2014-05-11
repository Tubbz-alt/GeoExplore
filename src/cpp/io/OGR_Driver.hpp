/**
 * @file    OGR_Driver.hpp
 * @author  Marvin Smith
 * @date    4/30/2014
*/
#ifndef __SRC_CPP_IO_OGRDRIVER_HPP__
#define __SRC_CPP_IO_OGRDRIVER_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>
#include <GeoExplore/coordinate/CoordinateUTM.hpp>
#include <GeoExplore/coordinate/CoordinateGeodetic.hpp>


namespace GEO{
namespace OGR{

/**
 * @class OGR_Driver
*/
class OGR_Driver {

    public:
        
        /**
          *  Default Constructor
         */
        OGR_Driver();

    private:

};  /// End of OGR_Driver Class


/**
 * Compute the UTM Zone Given the Longitude
 *
 * @param[in] longitude Required to determine which zone longitude best fits into
 *
 * @return UTM zone for the given longitude.
*/
int compute_UTM_Zone( const double& longitude );

/**
 * Convert a coordinate from UTM to Geodetic
 *
 * @param[in] fromZone Input UTM Zone
 * @param[in] fromEasting  Input UTM Easting (x)
 * @param[in] fromNorthing Input UTM Northing (y)
 * @param[in] fromAltitude Input UTM Altitude (z)
 * @param[in] fromDatum    Input UTM Datum
 * @param[in] toDatum      Output Fixed Geodetic Datum
 * @param[out] toLatitude  Output Geodetic Latitude
 * @param[out] toLongitude Output Geodetic Longitude
 * @param[out] toAltitude  Output Geodetic Altitude
 *
 * @return Geodetic Coordinate
*/
void convert_UTM2Geodetic( int const&    fromZone,
                           double const& fromEasting,  
                           double const& fromNorthing,  
                           double const& fromAltitude,    
                           Datum const&  fromDatum,
                           Datum const&  toDatum,
                           double&       toLatitude, 
                           double&       toLongitude, 
                           double&       toAltitude );

/**
 * Convert a coordinate from Geodetic to UTM
 *
 * @param[in]  fromLatitude  Input Geodetic Latitude
 * @param[in]  fromLongitude Input Geodetic Longitude
 * @param[in]  fromAltitude  Input Geodetic Altitude
 * @param[in]  fromDatum     Input Datum
 * @param[in]  toDatum       Output Fixed Datum
 * @param[in]  toZone        Output Fixed UTM Zone
 * @param[out] toEasting     Output UTM Easting (x)
 * @param[out] toNorthing    Output UTM Northing (y)
 * @param[out] toAltitude    Output UTM Altitude (z)
 *
 * @return Output UTM Coordinate
*/
void convert_Geodetic2UTM_fixedZone( double const& fromLatitude,
                                     double const& fromLongitude,
                                     double const& fromAltitude,
                                     Datum const&  fromDatum,
                                     Datum const&  toDatum,
                                     int const&    toZone,
                                     double&       toEasting,
                                     double&       toNorthing,
                                     double&       toAltitude );
 
 
/**
 * Convert a coordinate from Geodetic to UTM
 *
 * @param[in]  fromLatitude  Input Geodetic Latitude
 * @param[in]  fromLongitude Input Geodetic Longitude
 * @param[in]  fromAltitude  Input Geodetic Altitude
 * @param[in]  fromDatum     Input Datum
 * @param[in]  toDatum       Output Fixed Datum
 * @param[out] toEasting     Output UTM Easting  (x)
 * @param[out] toNorthing    Output UTM Northing (y)
 * @param[out] toAltitude    Output UTM Altitude (z)
 *
 * @return UTM Coordinate
*/
void convert_Geodetic2UTM( double const& fromLatitude,
                           double const& fromLongitude,
                           double const& fromAltitude,
                           Datum const&  fromDatum,
                           Datum const&  toDatum,
                           int&          toZone,
                           double&       toEasting,
                           double&       toNorthing,
                           double&       toAltitude );


} /// End of OGR Namespace
} /// End of GEO Namespace

#endif
