/**
 * @file    OpenCV_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/20/2015
 *
 * @brief Contains OpenCV-Related helper functions.
*/
#ifndef __GEOEXPLORE_SRC_UTILS_OPENCV_UTILITIES_HPP__
#define __GEOEXPLORE_SRC_UTILS_OPENCV_UTILITIES_HPP__

// GeoExplore Libraries
#include "../image/Image.hpp"
#include "../image/Pixel_Types.hpp"

// OpenCV Libraries
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace GEO{
namespace UTILS{
namespace OCV{


template <typename PixelType>
class OpenCV_Type_Converter{
    
    public:
        
        static int pixel_cast( PixelType const& pixel_value ){
            return 0;
        }
};

template <>
class OpenCV_Type_Converter<IMG::PixelRGBA_u8>{

    public:

        /**
         * @brief Convert form a PixelRGBA type to cv::Vec3b
        */
        static cv::Vec3b pixel_cast( IMG::PixelRGBA_u8 const& pixel_value ){
            return cv::Vec3b( pixel_value[2], pixel_value[1], pixel_value[0]);
        }

}; 

/**
 * @brief View the requested image using OpenCV's Highgui Module
 */
template <typename PixelType, typename ResourceType>
void View_Image( IMG::Image_<PixelType, ResourceType> const& image, 
                 std::string const& window_name, 
                 const int& wait_time_milliseconds = 0 )
{

    // Make sure the image loaded properly
    if( image.rows() <= 0 || image.cols() <= 0 ){
        return;
    }

    // Create output image
    cv::Mat view_image( image.rows(), image.cols(), CV_8UC3 );

    // Iterate over image
    for( int r=0; r<view_image.rows; r++ )
    for( int c=0; c<view_image.cols; c++ )
        view_image.at<cv::Vec3b>(r,c) = OpenCV_Type_Converter<PixelType>::pixel_cast( image(r,c) );

    // View the image
    cv::imshow( window_name.c_str(), view_image );

    // Wait
    cv::waitKey( wait_time_milliseconds );
}


} // End of OCV   Namespace
} // End of UTILS Namespace
} // End of GEO   Namespace

#endif
