/**
 * @file    OGR_Driver.hpp
 * @author  Marvin Smith
 * @date    4/30/2014
*/
#ifndef __SRC_CPP_IO_OGRDRIVER_HPP__
#define __SRC_CPP_IO_OGRDRIVER_HPP__

/// GeoExplore Libraries
#include "../core/Enumerations.hpp"
#include "../coordinate/CoordinateUTM.hpp"
#include "../coordinate/CoordinateGeographic.hpp"


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
 * @brief Convert a coordinate from UTM to Geographic
 *
 * @param[in] fromZone Input UTM Zone
 * @param[in] fromEasting  Input UTM Easting (x)
 * @param[in] fromNorthing Input UTM Northing (y)
 * @param[in] fromAltitude Input UTM Altitude (z)
 * @param[in] fromDatum    Input UTM Datum
 * @param[in] toDatum      Output Fixed Geographic Datum
 * @param[out] toLatitude  Output Geographic Latitude
 * @param[out] toLongitude Output Geographic Longitude
 * @param[out] toAltitude  Output Geographic Altitude
 *
 * @return Geographic Coordinate
*/
void convert_UTM2Geographic( int const&    fromZone,
                             double const& fromEasting,  
                             double const& fromNorthing,  
                             double const& fromAltitude,    
                             Datum const&  fromDatum,
                             Datum const&  toDatum,
                             double&       toLatitude, 
                             double&       toLongitude, 
                             double&       toAltitude );

/**
 * @brief Convert a list of coordinates from UTM to Geographic.
 *
 * @param[in] number_points Number of points to process.
 * @param[in] fromZone UTM Zone of all coordinates.
 * @param[in] fromHemi True if all points in northern, false if southern.
 * @param[in] fromDatum Datum to convert from.
 * @param[in] toDatum Datum to convert to.
 * @param[in/out] x List of input eastings,  output longitudes.
 * @param[in/out] y List of input northings, output latitudes.
 * @param[in/out] z List of input/output altitudes.
*/
void convert_UTM2Geographic_list( int const& number_points,
                                  int  const& fromZone,
                                  bool const& fromHemi,
                                  Datum const& fromDatum,
                                  Datum const& toDatum,
                                  double*& x,
                                  double*& y,
                                  double*& z );

/**
 * Convert a coordinate from Geographic to UTM
 *
 * @param[in]  fromLatitude  Input Geographic Latitude
 * @param[in]  fromLongitude Input Geographic Longitude
 * @param[in]  fromAltitude  Input Geographic Altitude
 * @param[in]  fromDatum     Input Datum
 * @param[in]  toDatum       Output Fixed Datum
 * @param[in]  toZone        Output Fixed UTM Zone
 * @param[out] toEasting     Output UTM Easting (x)
 * @param[out] toNorthing    Output UTM Northing (y)
 * @param[out] toAltitude    Output UTM Altitude (z)
 *
 * @return Output UTM Coordinate
*/
void convert_Geographic2UTM_fixedZone( double const& fromLatitude,
                                       double const& fromLongitude,
                                       double const& fromAltitude,
                                       Datum const&  fromDatum,
                                       Datum const&  toDatum,
                                       int const&    toZone,
                                       double&       toEasting,
                                       double&       toNorthing,
                                       double&       toAltitude );
 
 
/**
 * @brief Convert a coordinate from Geographic to UTM
 *
 * @param[in]  fromLatitude  Input Geographic Latitude
 * @param[in]  fromLongitude Input Geographic Longitude
 * @param[in]  fromAltitude  Input Geographic Altitude
 * @param[in]  fromDatum     Input Datum
 * @param[in]  toDatum       Output Fixed Datum
 * @param[out] toEasting     Output UTM Easting  (x)
 * @param[out] toNorthing    Output UTM Northing (y)
 * @param[out] toAltitude    Output UTM Altitude (z)
 *
 * @return UTM Coordinate
*/
void convert_Geographic2UTM( double const& fromLatitude,
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
