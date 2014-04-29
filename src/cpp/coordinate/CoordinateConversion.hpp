/**
 * @file    CoordinateConversion.hpp
 * @author  Marvin Smith
 * @date    4/15/2014
 */
#ifndef __SRC_COORDINATE_COORDINATECONVERSION_HPP__
#define __SRC_COORDINATE_COORDINATECONVERSION_HPP__

#include <GeoExplore/coordinate/CoordinateBase.hpp>
#include <GeoExplore/coordinate/CoordinateGeodetic.hpp>
#include <GeoExplore/coordinate/CoordinateUTM.hpp>

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

} /// End of GEO Namespace

#endif
