/**
 * @file    OpenCV_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/20/2015
 *
 * @brief Contains OpenCV-Related helper functions.
*/
#ifndef __GEOEXPLORE_SRC_UTILS_OPENCV_UTILITIES_HPP__
#define __GEOEXPLORE_SRC_UTILS_OPENCV_UTILITIES_HPP__

namespace GEO{
namespace UTILS{
namespace OCV{

/**
 * @brief View the requested image using OpenCV's Highgui Module
 */
template <typename PixelType, typename ResourceType>
void View_Image( IMG::Image_<PixelType, ResourceType> const& image, 
                 std::string const& window_name, 
                 const int& wait_time_milliseconds = 0 )
{

    // Make sure the image loaded properly



}


} // End of OCV   Namespace
} // End of UTILS Namespace
} // End of GEO   Namespace

#endif
