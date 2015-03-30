/**
 * @file    Image_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#ifndef __GEOEXPLORE_LIB_IMAGE_IMAGE_UTILITIES_HPP__
#define __GEOEXPLORE_LIB_IMAGE_IMAGE_UTILITIES_HPP__

// GeoExplore Libraries
#include "../core/A_Status.hpp"
#include "Image.hpp"

// C++ Standard Libraries
#include <cmath>


namespace GEO{
namespace IMG{

/**
 * @brief Compute Image Min and Max
 *
 * @param[in] image Image to check.
 * @param[out] min_pixel Minimum pixel.
 * @param[out] max_pixel Maximum pixel.
 *
 * @return Status of the operation.
 */
template <typename PixelType, typename ResourceType>
Status MinMax( Image_<PixelType, ResourceType>const& image, 
               PixelType& min_pixel,
               PixelType& max_pixel )
{

    // Make sure the image is not empty
    if( image.Rows() <= 0 || image.Cols() <= 0 ){
        return Status( StatusType::FAILURE, CoreStatusReason::UNINITIALIZED, "Uninitialized.");
    }

    // Iterate over image
    min_pixel = image[0];
    max_pixel = image[0];

    for( int i=0; i<(image.Rows()*image.Cols()); i++ ){
    for( int c=0; c<(image.Channels()); c++ ){
        min_pixel[c] = std::min( image[i][c], min_pixel[c] );
        max_pixel[c] = std::max( image[i][c], max_pixel[c] );
    }
    }

    // return success
    return Status( StatusType::SUCCESS );
}




} // End of IMG Namespace
} // End of GEO Namespace


#endif
