/**
 * @file    Enumerations.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_CORE_ENUMERATIONS_HPP__
#define __SRC_CORE_ENUMERATIONS_HPP__

/// C++ Standard Libraries
#include <string>

namespace GEO{

/**
 * @class Datum
 *
 * Common Geographic Datums which are supported.
 */
enum class Datum{

    EGM96,
    NAD83,
    WGS84,

}; /// End of ProjectionType Class

/**
 * Convert a datum to the GDAL WKCS
*/
std::string Datum2WKT_string( Datum const& datum );

/**
 * @class CoordinateType
 */
enum class CoordinateType{

    Base,
    Geodetic,
    UTM,

}; /// End of CoordinateType

/**
 * Convert a coordinate type to string
*/
std::string CoordinateType2String( CoordinateType const& ctype );

/**
 * @class ImageDriver
*/
enum class ImageDriverType{
    Base,
    GDAL,
    NETPBM,
    OPENCV,
}; /// End of ImageDriver Enumerations


} /// End of GEO Namespace


#endif
