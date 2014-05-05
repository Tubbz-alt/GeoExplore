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
 * Convert a coordinate from UTM to Geodetic
*/
CoordinateGeodetic convert( CoordinateUTM const& coord,  Datum const& datum );


} /// End of GEO Namespace

#endif
