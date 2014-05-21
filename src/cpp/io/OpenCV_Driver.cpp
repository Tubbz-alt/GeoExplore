/**
 * @file    OpenCV_Driver.cpp
 * @author  Marvin Smith
 * @date    5/16/2014
*/
#include "OpenCV_Driver.hpp"

namespace GEO{
namespace IO{
namespace OPENCV{


/**
 * Get the rows
*/
int ImageDriverOpenCV::rows()const{
    return 0;
}

/**
 * Get the columns
*/
int ImageDriverOpenCV::cols()const{
    return 0;
}

/**
 * ImageDriverOpenCV Type Function
*/
ImageDriverType ImageDriverOpenCV::type()const{
    return ImageDriverType::OPENCV;
}

/**
 * Open the driver
*/
void ImageDriverOpenCV::open(){

}

/**
 * Open the driver
*/
void ImageDriverOpenCV::open( const boost::filesystem::path& pathname ){

}

} /// End of OpenCV Namespace
} /// End of IO Namespace
} /// End of GEO Namespace


