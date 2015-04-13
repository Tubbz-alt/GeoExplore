/**
 * @file    CoordinateConversion.hpp
 * @author  Marvin Smith
 * @date    4/15/2014
 */
#ifndef __SRC_COORDINATE_COORDINATECONVERSION_HPP__
#define __SRC_COORDINATE_COORDINATECONVERSION_HPP__

/// GeoExplore Libraries
#include "CoordinateBase.hpp"
#include "CoordinateGeographic.hpp"
#include "CoordinateUTM.hpp"
#include "../io/OGR_Driver.hpp"

/// C++ Libraries
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace GEO{
namespace CRD{

/**
 * Convert between coordinate systems given pointers to coordinates
 */
template<typename DATATYPE>
typename CoordinateBase<DATATYPE>::ptr_t  convert_coordinate( typename CoordinateBase<DATATYPE>::ptr_t const& coordinate, 
                                                              CoordinateType const& output_coordinate_type, 
                                                              Datum const& output_datum ){

    // compare before and after types.  Return a copy of the input if the before and after are the same
    if( coordinate->datum() == output_datum &&  coordinate->Get_Type() == output_coordinate_type ){
        return coordinate->clone();
    }
    
    // check if we have a Geographic to UTM
    if( coordinate->Get_Type() == CoordinateType::Geographic && 
        output_coordinate_type == CoordinateType::UTM ){
    
        // cast the input to the proper type
        typename CoordinateGeographic<DATATYPE>::ptr_t input = std::dynamic_pointer_cast<CoordinateGeographic<DATATYPE> >(coordinate);

        // create an output coordinate
        typename CoordinateUTM<DATATYPE>::ptr_t output( new CoordinateUTM<DATATYPE>(output_datum));

        // convert
        GEO::IO::OGR::convert_Geographic2UTM( input->latitude_degrees(), 
                                              input->longitude_degrees(), 
                                          input->altitude_meters(), 
                                          input->datum(), 
                                          output->datum(), 
                                          output->zone(), 
                                          output->easting_meters(), 
                                          output->northing_meters(), 
                                          output->altitude_meters() );

        // downcast and send
        return output;
    }

    // check if we have UTM to geodetic
    if( coordinate->Get_Type() == CoordinateType::UTM && output_coordinate_type == CoordinateType::Geographic ){

        // cast the input to UTM
        typename CoordinateUTM<DATATYPE>::ptr_t input = std::dynamic_pointer_cast<CoordinateUTM<DATATYPE> >(coordinate);

        // create an output coordinate
        typename CoordinateGeographic<DATATYPE>::ptr_t output( new CoordinateGeographic<DATATYPE>(output_datum));

        // convert
        GEO::IO::OGR::convert_UTM2Geographic( input->zone(), 
                                              input->easting_meters(), 
                                              input->northing_meters(), 
                                              input->altitude_meters(), 
                                              input->datum(), 
                                              output->datum(),
                                              output->latitude_degrees(), 
                                              output->longitude_degrees(), 
                                              output->altitude_meters() );

        return output;


    }

    // otherwise, throw an error
    throw std::runtime_error("Conversion type currently not supported.");

}


/**
 * @brief Convert from Geographic to Geographic
 *
 * @note This is more to allow templated code to compile.
 *
 * @param[in] coordinate Geographic Coordinate.
 *
 * @return Copy of this coordinate (Geographic).
*/
template <typename OutputCoordinateType>
typename std::enable_if<std::is_same<OutputCoordinateType, CoordinateGeographic<typename OutputCoordinateType::datatype>>::value, CoordinateGeographic<typename OutputCoordinateType::datatype> >::type
        convert_coordinate( CoordinateGeographic<typename OutputCoordinateType::datatype> const& coordinate ){
    return coordinate;
}


/**
 * Convert from Geographic to UTM
 *
 * @param[in] coordinate Lat/Lon Coordinate to convert
 * @param[in] output_datum Datum to convert to
 *
 * @return  UTM coordinate.
*/
template <typename OutputCoordinateType>
typename std::enable_if<std::is_same<OutputCoordinateType, CoordinateUTM<typename OutputCoordinateType::datatype>>::value, CoordinateUTM<typename OutputCoordinateType::datatype> >::type
        convert_coordinate( CoordinateGeographic<typename OutputCoordinateType::datatype> const& coordinate, 
                                             Datum const& output_datum )
{

    // create the output coordinate with the proper datum
    CoordinateUTM<typename OutputCoordinateType::datatype> output;
    output.datum() = output_datum;

    // pass the inputs to the OGR converter
    GEO::IO::OGR::convert_Geographic2UTM( coordinate.latitude_degrees(), 
                                          coordinate.longitude_degrees(), 
                                          coordinate.altitude_meters(), 
                                          coordinate.datum(),
                                          output.datum(), 
                                          output.zone(), 
                                          output.easting_meters(), 
                                          output.northing_meters(),  
                                          output.altitude_meters() );


    return output;
}


/**
 * Convert from Geographic to UTM with fixed zone
 *
 * @param[in] coordinate Lat/Lon coordinate to convert
 * @param[in] zone Zone to set output to
 * @param[in] datum Datum
 *
 * @return UTM Coordinate output
*/
template <typename DATATYPE>
CoordinateUTM<DATATYPE> convert_coordinate( CoordinateGeographic<DATATYPE> const& coordinate, 
                                            const int& zone, 
                                            Datum const& datum ){
    
    /// create the output
    CoordinateUTM<DATATYPE> output;
    output.datum() = datum;
    output.zone() = zone;

    // pass the inputs to the OGR converter
    GEO::IO::OGR::convert_Geographic2UTM_fixedZone( coordinate.latitude_degrees(),
                                                    coordinate.longitude_degrees(),
                                                    coordinate.altitude_meters(),
                                                    coordinate.datum(),
                                                    output.datum(),
                                                    zone,
                                                    output.easting_meters(),
                                                    output.northing_meters(),
                                                    output.altitude_meters()
                                                  );

    return output;
}


/**
 * Convert from Geographic to UTM with fixed Zone and fixed datum
 *
 * @param[in] coordinate Lat/Lon coordinate to convert
 * @param[in] zone Zone to set output to
 *
 * @return UTM Coordinate output.
*/
template <typename OutputCoordinateType>
typename std::enable_if<std::is_same<OutputCoordinateType, CoordinateUTM<typename OutputCoordinateType::datatype>>::value, CoordinateUTM<typename OutputCoordinateType::datatype> >::type
    convert_coordinate( CoordinateGeographic<typename OutputCoordinateType::datatype> const& coordinate, const int& zone ){
    return convert_coordinate<OutputCoordinateType>(coordinate, zone, coordinate.datum());
}


/**
  * Convert Geographic to UTM forcing the datum to remain the same
  *
  * @param[in] coordinate Lat/Lon Coordinate to convert
  * 
  * @return UTM Coordinate output
 */
template <typename OutputCoordinateType>
typename std::enable_if<std::is_same<OutputCoordinateType, CoordinateUTM<typename OutputCoordinateType::datatype>>::value, 
                        CoordinateUTM<typename OutputCoordinateType::datatype> >::type
    convert_coordinate( CoordinateGeographic<typename OutputCoordinateType::datatype> const& coordinate ){
    return convert_coordinate<OutputCoordinateType>(coordinate, coordinate.datum());
}


/**
 * @brief Convert from UTM to Geographic.
 *
 * @param[in] coordinate UTM coordinate to convert.
 * @param[in] datum Datum to convert to.
 *
 * @return Geographic coordinate.
*/
template <typename OutputCoordinateType>
typename std::enable_if<std::is_same<OutputCoordinateType, CoordinateGeographic<typename OutputCoordinateType::datatype>>::value, 
                        CoordinateGeographic<typename OutputCoordinateType::datatype> >::type
        convert_coordinate( CoordinateUTM<typename OutputCoordinateType::datatype> const& coordinate, 
                            const Datum& outputDatum )
{
    
    // create the output coordinate
    CoordinateGeographic<typename OutputCoordinateType::datatype> output;
    output.datum() = outputDatum;

    // pass inputs to the ogr converter
    GEO::IO::OGR::convert_UTM2Geographic( coordinate.zone(), 
                                          coordinate.easting_meters(), 
                                          coordinate.northing_meters(), 
                                          coordinate.altitude_meters(),
                                          coordinate.datum(), 
                                          output.datum(), 
                                          output.latitude_degrees(), 
                                          output.longitude_degrees(), 
                                          output.altitude_meters()
                                        );

    return output;
}


/**
 * @brief Convert from UTM to geographic with a forced datum.
 *
 * @param[in] coordinate UTM coordinate to convert.
 *
 * @return Geographic coordinate.
*/
template <typename OutputCoordinateType>
typename std::enable_if<std::is_same<OutputCoordinateType, CoordinateGeographic<typename OutputCoordinateType::datatype>>::value, 
                            CoordinateGeographic<typename OutputCoordinateType::datatype> >::type
         convert_coordinate( CoordinateUTM<typename OutputCoordinateType::datatype> const& coordinate ){
    return convert_coordinate<OutputCoordinateType>(coordinate, coordinate.datum());
}


} /// End of CRD Namespace
} /// End of GEO Namespace

#endif
