/**
 * @file    Common_Equations.hpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#ifndef __GEOEXPLORE_MATH_COMMON_EQUATIONS_HPP__
#define __GEOEXPLORE_MATH_COMMON_EQUATIONS_HPP__

// C++ Standard Libraries
#include <cmath>

// GeoExplore Libraries
#include "A_Point.hpp"

namespace GEO{
namespace MATH{

/**
 * @brief Linear Interpolation
 * 
 * @param[in] v0 First value.
 * @param[in] v1 Second value.
 * 
 * @return Interpolated value.
 */
template <typename TP>
TP LERP( TP const& v0, TP const& v1, double const& t )
{
    return ((1-t)*v0 + (t*v1));
}


/**
 * @brief 2-dimension Gaussian Function
 *
 * @param[in] point Point to evaluate.
 * @param[in] origin Point at origin.
 * @param[in] sigma_x Sigma in x direction.
 * @param[in] sigma_y Sigma in y direction.
 * @param[in] alpha Scale factor.
 *
 * @return Gaussian result.
*/
template <typename TP>
TP Gaussian2D( MATH::A_Point2<TP> const& point,
               MATH::A_Point2<TP> const& origin,
               const double&             sigma_x,
               const double&             sigma_y,
               const double&             alpha )
{
    
    TP sum_x = std::pow(point.x() - origin.x(), 2.0)/(2*sigma_x*sigma_x);
    TP sum_y = std::pow(point.y() - origin.y(), 2.0)/(2*sigma_y*sigma_y);
    return alpha * std::exp( -(sum_x + sum_y) );
}


} // End of MATH Namespace
} // End of GEO  Namespace

#endif
