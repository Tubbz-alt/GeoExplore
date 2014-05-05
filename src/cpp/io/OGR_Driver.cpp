/**
  *  @file   OGR_Driver.cpp
  *  @author Marvin Smith
  *  @date   5/3/2014
*/
#include "OGR_Driver.hpp"

namespace  GEO {

/**
 *  Default Constructor
*/
OGR_Driver::OGR_Driver(){



}

/**
 *  Convert from UTM to Geodetic
*/
CoordinateGeodetic  convert( CoordinateUTM const& coord,  Datum const& datum ){

    /// Create output coordinate
    CoordinateUTM output;

    /// return output
    return output;
}

}  /// End of GEO Namespace