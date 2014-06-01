/**
 * @file    ImageDriverBase.hpp
 * @author  Marvin Smith
 * @date    5/11/2014
*/
#ifndef __GEOEXPLORE_IO_IMAGEDRIVERBASE_HPP__
#define __GEOEXPLORE_IO_IMAGEDRIVERBASE_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>

/// Boost C++ Libraries
#include <boost/filesystem.hpp>

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
        
        /**
         * Get the rows
        */
        virtual int rows() = 0;

        /**
         * Get the columns
        */
        virtual int cols() = 0;
    
        /**
         * Open the driver
        */
        virtual void open() = 0;

        /**
         * Open the driver given an image
        */
        virtual void open( const boost::filesystem::path& pathname ) = 0;
        

}; /// End of ImageDriverBase Class

} /// End of IO Namespace
} /// End of GEO Namespace

#endif
