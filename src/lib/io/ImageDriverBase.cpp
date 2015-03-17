/**
 * @file    ImageDriverBase.cpp
 * @author  Marvin Smith
 * @date    5/16/2014
*/
#include "ImageDriverBase.hpp"

namespace GEO{
namespace IO{

/**
 * Get the image driver type
*/
ImageDriverType ImageDriverBase::type()const{
    return ImageDriverType::Base;
}

} /// End of IO Namespace
} /// End of GEO Namespace
