/**
 * @file    ImageDriverBase.hpp
 * @author  Marvin Smith
 * @date    5/11/2014
*/
#ifndef __GEOEXPLORE_IO_IMAGEDRIVERBASE_HPP__
#define __GEOEXPLORE_IO_IMAGEDRIVERBASE_HPP__

/// GeoExplore Libraries
#include "../core/Enumerations.hpp"
#include "../filesystem.hpp"
#include "../image/MemoryResource.hpp"

/// C++ Standard Libraries
#include <memory>


namespace GEO{
namespace IO{

/**
 * @class ImageDriverBase
 *
 * @brief Base driver type.
 */
template <typename ResourceType>
class ImageDriverBase{

    public:
        

        /// Pointer Type
        typedef std::shared_ptr<ImageDriverBase> ptr_t;


        /// Pixel Type
        typedef typename ResourceType::pixel_type pixel_type;

        /**
         * @brief Get the pixel value at the specified location.
         *
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         *
         * @return Pixel value at the location.
        */
        virtual pixel_type Get_Pixel( const int& row, 
                                     const int& col)
        {
            return pixel_type();
        }


        /**
         * @brief Get the image driver type.
         *
         * @return Image driver type enumeration.
        */
        virtual ImageDriverType Get_ImageDriverType()const{
            return ImageDriverType::Base;
        }
        

        /**
         * @brief Get the rows.
         * 
         * @return Number of rows in image.
        */
        virtual int Rows()const = 0;


        /**
         * @brief Get the columns.
         * 
         * @return Number of columns in image.
        */
        virtual int Cols()const = 0;

    
        /**
         * @brief Open the driver
        */
        virtual void Open() = 0;


        /**
         * @brief Open the driver given an image.
         *
         * @param[in] pathname Image pathname.
        */
        virtual void Open( const FS::FilesystemPath& pathname ) = 0;
        
        /**
         * @brief Read an image from file.
         *
         * @param[in] pathname Image pathname.
         *
         * @return Image resource.
        */
        virtual typename IMG::MemoryResource<pixel_type>::ptr_t Read_Image(  FS::FilesystemPath const& pathname ) = 0;

        
        /**
         * @brief Write an image.
         *
         * @param[in] output_image Image to write.
         * @param[in] pathname Image pathname to write to.
         */
        virtual void Write_Image( IMG::Image_<typename ResourceType::pixel_type,ResourceType>const& output_image, 
                                  FS::FilesystemPath const& pathname ) = 0;


}; /// End of ImageDriverBase Class

} /// End of IO Namespace
} /// End of GEO Namespace

#endif
