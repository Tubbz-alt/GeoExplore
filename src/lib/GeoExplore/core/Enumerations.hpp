/**
 * @file    Enumerations.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_CORE_ENUMERATIONS_HPP__
#define __SRC_CORE_ENUMERATIONS_HPP__

/// C++ Standard Libraries
#include <cinttypes>
#include <string>

namespace GEO{


/**
 * @class Datum
 *
 * @brief Common Geographic Datums which are supported.
 */
enum class Datum : uint8_t{
    UNKNOWN = 0 /**< Not supported or provided.*/,
    NAD83   = 2 /**< North American Datum 1983*/,
    WGS84   = 3 /**< World Geographic System 1984*/,
}; /// End of ProjectionType Class


/**
 * @brief Convert a datum to the GDAL Well Known Text
 *
 * @param[in] datum Datum to test
 * @return Well-Known-Text Format
*/
std::string Datum2WKT_string( Datum const& datum );

/**
 * @brief Convert a Datum to String
 *
 * @param[in] datum Datum to Convert
 * 
 * @return String
*/
std::string DatumToString( const Datum& datum );


/**
 * @brief Convert a String to Datum.
 *
 * @param[in] datum Datum string to convert.
 *
 * @return Datum object.
*/
Datum StringToDatum( std::string const& datum_string );


/**
 * @class CoordinateType
 *
 * @brief Define the type of coordinate
 */
enum class CoordinateType{
    Base     /**< Base Implementation of CoordinateType*/,
    Geographic /**< Geographic Coordinate (Lat/Lon)*/,
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
