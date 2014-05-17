/**
 * @file    ImageDriverBase.hpp
 * @author  Marvin Smith
 * @date    5/11/2014
*/
#ifndef __GEOEXPLORE_IO_IMAGEDRIVERBASE_HPP__
#define __GEOEXPLORE_IO_IMAGEDRIVERBASE_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>

namespace GEO{
namespace IO{


class ImageDriverBase{

    public:
        
        /**
         * Get the pixel value
        */
        template <typename PixelType>
        PixelType getPixel( const int& x, const int& y)const{
            return PixelType();
        }

        /**
         * Get the image driver type
        */
        virtual ImageDriverType type()const;


}; /// End of ImageDriverBase Class

} /// End of IO Namespace
} /// End of GEO Namespace

#endif
