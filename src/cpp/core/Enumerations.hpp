/**
 * @file    Enumerations.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_CORE_ENUMERATIONS_HPP__
#define __SRC_CORE_ENUMERATIONS_HPP__

namespace GEO{

/**
 * @class Datum
 *
 * Common Geographic Datums which are supported.
 */
enum class Datum{

    WGS84,
    NAD83,

}; /// End of ProjectionType Class

/**
 * @class CoordinateType
 */
enum class CoordinateType{

    Base,
    Geodetic,
    UTM,

}; /// End of CoordinateType


} /// End of GEO Namespace


#endif
