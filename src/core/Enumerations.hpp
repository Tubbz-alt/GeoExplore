/**
 * @file    Enumerations.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_CORE_ENUMERATIONS_HPP__
#define __SRC_CORE_ENUMERATIONS_HPP__

namespace GEO{

/**
 * @class CoordinateSystem
 *
 * Common Geographic Projections which are supported.
 */
enum class CoordinateSystem{

    WGS84 = 4326,  // EPSG: 4326

}; /// End of ProjectionType Class


} /// End of GEO Namespace


#endif
