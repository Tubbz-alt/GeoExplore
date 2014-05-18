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
 * ImageDriverOpenCV Type Function
*/
ImageDriverType ImageDriverOpenCV::type()const{
    return ImageDriverType::OPENCV;
}

} /// End of OpenCV Namespace
} /// End of IO Namespace
} /// End of GEO Namespace


