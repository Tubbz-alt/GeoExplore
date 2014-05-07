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
#include <iostream>
#include <stdexcept>

namespace GEO{

/**
 * Convert between coordinate systems given pointers to coordinates
 */
template<typename DATATYPE>
typename CoordinateBase<DATATYPE>::ptr_t  convert_coordinate( typename CoordinateBase<DATATYPE>::ptr_t const& coordinate, 
                                                              CoordinateType const& output_coordinate_type, 
                                                              Datum const& output_datum ){

    // compare before and after types.  Return a copy of the input if the before and after are the same
    if( coordinate->datum() == output_datum &&  coordinate->type() == output_coordinate_type ){
        return coordinate->clone();
    }
    
    // check if we have a Geodetic to UTM
    if( coordinate->type() == CoordinateType::Geodetic && output_coordinate_type == CoordinateType::UTM ){
    
        // cast the input to the proper type
        typename CoordinateGeodetic<DATATYPE>::ptr_t input = boost::static_pointer_cast<CoordinateGeodetic<DATATYPE> >(coordinate);

        // create an output coordinate
        typename CoordinateUTM<DATATYPE>::ptr_t output( new CoordinateUTM<DATATYPE>(output_datum));

        // convert
        GEO::OGR::convert_Geodetic2UTM( input->latitude(), input->longitude(), input->altitude(), input->datum(), output->datum(), output->zone(), output->easting(), output->northing(), output->altitude() );

        // downcast and send
        return output;
    
    }

    // otherwise, throw an error
    throw std::runtime_error("Conversion type currently not supported.");

}


/**
 * Convert from Geodetic to UTM
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
  * Convert Geodetic to UTM forcing the datum to remain the same
 */
template<typename DATATYPE>
CoordinateUTM<DATATYPE> convert_coordinate( CoordinateGeodetic<DATATYPE> const& coordinate ){
    return convert_coordinate(coordinate, coordinate.datum());
}

/**
 * Convert from UTM to Geodetic
*/
template<typename DATATYPE>
CoordinateGeodetic<DATATYPE> convert_coordinate( CoordinateUTM<DATATYPE> const& coordinate, const Datum& outputDatum ){
    
    // create the output coordinate
    CoordinateGeodetic<DATATYPE> output;
    output.datum() = outputDatum;

    // pass inputs to the ogr converter
    GEO::OGR::convert_UTM2Geodetic( coordinate.zone(), coordinate.easting(), coordinate.northing(), coordinate.altitude(),
                                    coordinate.datum(), output.datum(), output.latitude(), output.longitude(), 
                                    output.altitude()
                                  );

    return output;
}


/**
 * Convert from UTM to geodetic with a forced datum
*/
template<typename DATATYPE>
CoordinateGeodetic<DATATYPE> convert_coordinate( CoordinateUTM<DATATYPE> const& coordinate ){
    return convert_coordinate(coordinate, coordinate.datum());
}



} /// End of GEO Namespace

#endif
