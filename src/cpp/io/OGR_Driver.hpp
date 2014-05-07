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
*/
int compute_UTM_Zone( const double& longitude );

/**
 * Convert a coordinate from UTM to Geodetic
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
