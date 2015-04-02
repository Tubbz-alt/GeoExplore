/**
 * @file    Interpolation.hpp
 * @author  Marvin Smith
 * @date    4/1/2015
*/
#ifndef __GEOEXPLORE_LIB_IMAGE_INTERPOLATION_HPP__
#define __GEOEXPLORE_LIB_IMAGE_INTERPOLATION_HPP__

// C++ Standard Libraries
#include <algorithm>
#include <cmath>
#include <iostream>

// GeoExplore Libraries
#include "Image.hpp"
#include "../math/A_Point.hpp"

namespace GEO{
namespace IMG{

/**
 * @brief Interpolate Nearest Neighbor
 *
 * @param[in] image Image to interpolate.
 * @param[in] point Point to Interpolate.
 *
 * @return Pixel type.
*/
template <typename PixelType, 
          typename ResourceType >
PixelType Interpolate_Nearest_Neighbor( IMG::Image_<PixelType,ResourceType> const& image,
                                        MATH::A_Point2<double> const& point )
{
    
    // Check if image empty
    if( image.Rows() <= 0 || image.Cols() <= 0 ){
        return PixelType();
    }

    // Check if values
    int x, y;
    x = std::max( 0, (int)point.x());
    y = std::max( 0, (int)point.y());
    x = std::min( image.Cols()-1, x);
    y = std::min( image.Rows()-1, y);
    
    return image(y,x);
}

/**
 * @brief Interpolate Bilinear
 *
 * @param[in] image Image to interpolate.
 * @param[in] point Point to interpolate.
 *
 * @return Pixel type.
*/
template <typename PixelType,
          typename ResourceType>
PixelType Interpolate_Bilinear( IMG::Image_<PixelType,ResourceType> const& image,
                                MATH::A_Point2<double> const& point )
{

    // Check if image empty
    if( image.Rows() <= 0 || image.Cols() <= 0 ){
        return PixelType();
    }

    // Check if values
    double x, y;
    int dx, dy;
    x = std::max( 0, (int)point.x());
    y = std::max( 0, (int)point.y());
    x = std::min( image.Cols()-1, (int)x);
    y = std::min( image.Rows()-1, (int)y);
    
    if( std::fabs(x - std::floor(x+0.5)) < 0.0001 ||
        std::fabs(y - std::floor(y+0.5)) < 0.0001 )
    {
        // set the pixel value
        dx = std::floor(x + 0.5);
        dy = std::floor(y + 0.5);

        // Return if the value sits on an integer
        return image( dy, dx );
    }

    // Compute Range
    PixelType output;
    std::vector<double> min_row(output.Dims(), 0);
    std::vector<double> max_row(output.Dims(), 0);
    std::vector<double> min_col(output.Dims(), 0);
    for( int i=0; i<(int)min_row.size(); i++ ){
        //min_row[i] = image(0, 
        //max_row[i] = image(image.Rows()-1,0)
    }

    return image(dy,dx);
}


} // End of IMG Namespace
} // End of GEO Namespace

#endif
