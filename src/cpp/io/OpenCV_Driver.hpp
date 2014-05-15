/**
 * @file    OpenCV_Driver.hpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#ifndef __SRC_CPP_IO_OPENCVDRIVER_HPP__
#define __SRC_CPP_IO_OPENCVDRIVER_HPP__

/// GeoExplore Libraries
#include <GeoExplore/image/Image.hpp>

/// OpenCV Libraries
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace GEO{
namespace IO{
namespace OPENCV{

/**
 * Convert PixelType to OpenCV Type
*/
template<typename PixelType>
int PixelType2OpenCVType(){
    if( std::is_same<PixelType,PixelRGB_u8>::value ){
        return CV_8UC3;
    }
    if( std::is_same<PixelType,PixelRGB_u12>::value ){
        return CV_16UC3;
    }
    if( std::is_same<PixelType,PixelRGB_u14>::value ){
        return CV_16UC3;
    }
    if( std::is_same<PixelType,PixelRGB_u16>::value ){
        return CV_16UC3;
    }
    
    return CV_8UC1;
}

/**
 * Write an RGB Image to NETPBM File
*/
template<typename PixelType>
void write_image( Image<PixelType>const&  output_image, boost::filesystem::path const& pathname ){

    // convert pixel data to 
    std::cout << "write opencv image" << std::endl;
    
    // convert the output image to an opencv structure
    cv::Mat image( output_image.rows(), output_image.cols(), PixelType2OpenCVType<PixelType>());
    
    // start loading the output image
    for( size_t c=0; c<output_image.channels(); c++ ){
    for( size_t y=0; y<output_image.rows(); y++ ){
    for( size_t x=0; x<output_image.cols(); x++ ){
        image.at<PixelType::channeltype::datatype>(y,x)[c] = output_image(y,x)[c];
    }}}

    // run imwrite
    cv::imwrite( pathname.c_str(), image );

}



} /// End of OpenCV Namespace
} /// End of IO Namespace
} /// End of GEO Namespace

#endif
