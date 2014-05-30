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
 * @brief Common Geographic Datums which are supported.
 */
enum class Datum{

    EGM96 /**< Earth Graviational Model 1996*/,
    NAD83 /**< North American Datum 1983*/,
    WGS84 /**< World Geodetic System 1984*/,

}; /// End of ProjectionType Class

/**
 * @brief Convert a datum to the GDAL Well Known Text
 *
 * @param[in] datum Datum to test
 * @return Well-Known-Text Format
*/
std::string Datum2WKT_string( Datum const& datum );

/**
 * @class CoordinateType
 *
 * @brief Define the type of coordinate
 */
enum class CoordinateType{

    Base     /**< Base Implementation of CoordinateType*/,
    Geodetic /**< Geodetic Coordinate (Lat/Lon)*/,
    UTM      /**< Universal Transverse Mercator*/,

}; /// End of CoordinateType

/**
 * @brief Convert a coordinate type to string
 *
 * @param[in] ctype Coordinate Type to Convert
 * @return CoordinateType name as string
*/
std::string CoordinateType2String( CoordinateType const& ctype );

/**
 * @class ImageDriver
 *
 * @brief Type of image driver
*/
enum class ImageDriverType{
    Base,
    GDAL,
    NETPBM,
    OPENCV,
}; /// End of ImageDriver Enumerations


} /// End of GEO Namespace


#endif
