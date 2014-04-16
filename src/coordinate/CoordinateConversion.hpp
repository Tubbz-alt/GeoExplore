/**
 * @file    CoordinateConversion.hpp
 * @author  Marvin Smith
 * @date    4/15/2014
 */
#ifndef __SRC_COORDINATE_COORDINATECONVERSION_HPP__
#define __SRC_COORDINATE_COORDINATECONVERSION_HPP__

#include <gorgon/coordinate/CoordinateBase.hpp>
#include <gorgon/coordinate/CoordinateGeodetic.hpp>
#include <gorgon/coordinate/CoordinateUTM.hpp>

/**
 * Convert between coordinate systems
 */
template<typename DATATYPE>
CoordinateBase<DATATYPE>::ptr_t  convert_coordinate_system( CoordinateBase<DATATYPE>::ptr_t const& coordinate, CoordinateSystem const& output_coordinate_system ){


}


#endif
