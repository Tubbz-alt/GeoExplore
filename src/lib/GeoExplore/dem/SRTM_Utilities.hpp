/**
 * @file    SRTM_Utilities.hpp
 * @author  Marvin Smith
 * @date    4/1/2015
*/
#ifndef __GEOEXPLORE_LIB_DEM_SRTM_UTILITIES_HPP__
#define __GEOEXPLORE_LIB_DEM_SRTM_UTILITIES_HPP__

// GeoExplore Libraries
#include "../coordinate/CoordinateGeographic.hpp"
#include "../core.hpp"
#include "../math/A_Point.hpp"
#include "../math/A_Rectangle.hpp"


namespace GEO{
namespace DEM{
namespace SRTM{

/**
 * @brief Convert Coordinate to SRTM Pixel Coordinate.
 *
 * @param[in] coordinate Coordinate to evaluate.
 * @param[in] extent  SRTM file extent.
 * @param[in] rows Elevation tile rows.
 * @param[in] cols Elevation tile columns.
 * @param[out] status Status of the operation.
 *
 * @return 2d Pixel Coordinate.
 */
MATH::A_Point2d Coordinate_To_SRTM_Pixel( CRD::CoordinateGeographic_d const& coordinate,
                                          MATH::A_Rectangle2d const&         extent,
                                          int const&                         rows,
                                          int const&                         cols,
                                          Status&                            status );

} // End of SRTM Namespace



} // End of DEM Namespace
} // End of GEO Namespace

#endif
