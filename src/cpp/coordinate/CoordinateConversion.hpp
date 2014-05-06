/**
 * @file    CoordinateConversion.hpp
 * @author  Marvin Smith
 * @date    4/15/2014
 */
#ifndef __SRC_COORDINATE_COORDINATECONVERSION_HPP__
#define __SRC_COORDINATE_COORDINATECONVERSION_HPP__

/// GeoExplore Libraries
#include <GeoExplore/coordinate/CoordinateBase.hpp>
#include <GeoExplore/coordinate/CoordinateGeodetic.hpp>
#include <GeoExplore/coordinate/CoordinateUTM.hpp>
#include <GeoExplore/io/OGR_Driver.hpp>

/// C++ Libraries
#include <stdexcept>

namespace GEO{

/**
 * Convert between coordinate systems
 */
template<typename DATATYPE>
typename CoordinateBase<DATATYPE>::ptr_t  convert_coordinate( typename CoordinateBase<DATATYPE>::ptr_t const& coordinate, 
                                                              CoordinateType const& output_coordinate_type, 
                                                              Datum const& output_datum ){

    // compare before and after types.  Return a copy of the input if the before and after are the same
    if( coordinate->datum() == output_datum &&  coordinate->type() == output_coordinate_type ){
        return coordinate->clone();
    }
    
    // otherwise, throw an error
    throw std::runtime_error("Conversion type currently not supported.");

}


/**
 * Convert using actual structures.
*/
template<typename DATATYPE>
CoordinateUTM<DATATYPE>  convert_coordinate( CoordinateGeodetic<DATATYPE> const& coordinate, 
                                             Datum const& output_datum ){

    // create the output coordinate with the proper datum
    CoordinateUTM<DATATYPE> output;
    output.datum() = output_datum;

    // pass the inputs to the OGR converter
    GEO::OGR::convert_Geodetic2UTM( coordinate.latitude(), coordinate.longitude(), coordinate.altitude(), coordinate.datum(),
                                    output.datum(), output.zone(), output.easting(), output.northing(),  output.altitude() );


    return output;
}


/**
  * Convert forcing the datum to remain the same
 */
template<typename DATATYPE>
CoordinateUTM<DATATYPE> convert_coordinate( CoordinateGeodetic<DATATYPE> const& coordinate ){
    return convert_coordinate(coordinate, coordinate.datum());
}


} /// End of GEO Namespace

#endif
