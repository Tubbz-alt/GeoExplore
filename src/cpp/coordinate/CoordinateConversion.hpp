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

/**
 * Convert between coordinate systems
 */
template<typename DATATYPE>
CoordinateBase<DATATYPE>::ptr_t  convert_coordinate( CoordinateBase<DATATYPE>::ptr_t const& coordinate, 
                                                     CoordinateType const& output_coordinate_type, 
                                                     Datum const& output_datum ){

    // compare before and after types
    if( coordinate.datum() == output_datum &&  coordinate.type() == output_coordinate_type ){
        return ptr_t->clone();
    }
    
    // 
}


#endif
