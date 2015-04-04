/**
 * @file    Image_IO.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
 *
 * @brief Contains the high-level Image Read-Write operations.
*/
#ifndef __SRC_CPP_IO_IMAGEIO_HPP__
#define __SRC_CPP_IO_IMAGEIO_HPP__

/// GeoExplore Libraries
#include "../image/DiskResource.hpp"
#include "../image/MemoryResource.hpp"
#include "../image/Image.hpp"
#include "../io/GDAL_Driver.hpp"
#include "../io/NETPBM_Driver.hpp"
#include "../io/OpenCV_Driver.hpp"
#include "../utilities.hpp"

/// C++ Standard Libraries
#include <iostream>


namespace GEO{
namespace IO{

/**
 * @enum DriverOptions
 *
 * @brief Driver Options
*/
enum class DriverOptions{
    NONE,
    READ_ONLY
}; /// End Driver Options Class


/**
 * @brief Get the image driver for a read operation.
 *
 * @param[in] pathname Image pathname to evaluate.
 * @param[in] options Driver options.
 *
 * @return Image driver pointer.  Nullptr if an error occurred.
*/
template <typename ResourceType>
typename ImageDriverBase<ResourceType>::ptr_t  Get_Read_Driver( const FS::FilesystemPath& pathname, 
                                                                const DriverOptions& options = DriverOptions::NONE )    
{
    // GDAL Drivers
    if( GDAL::ImageDriverGDAL<ResourceType>::Is_Read_Supported(pathname) == true ){
        return typename ImageDriverBase<ResourceType>::ptr_t( new GDAL::ImageDriverGDAL<ResourceType>());
    }
    
    // opencv drivers
    if( OPENCV::ImageDriverOpenCV<ResourceType>::Is_Read_Supported(pathname) == true ){
        return typename ImageDriverBase<ResourceType>::ptr_t( new OPENCV::ImageDriverOpenCV<ResourceType>());
    }

    // Return null
    return nullptr;
}



/**
 * @brief Compute the image driver for a write operation.
 *
 * @param[in] pathname Image pathname to evaluate.
 * @param[in] options Driver options.
 *
 * @return Image driver pointer.  Nullptr if an error occurred.
*/
template <typename ResourceType>
typename ImageDriverBase<ResourceType>::ptr_t  Get_Write_Driver( const FS::FilesystemPath& pathname, 
                                                                 const DriverOptions& options = DriverOptions::NONE )
{
    // GDAL Drivers
    if( GDAL::ImageDriverGDAL<ResourceType>::Is_Write_Supported(pathname) == true ){
        return typename ImageDriverBase<ResourceType>::ptr_t( new GDAL::ImageDriverGDAL<ResourceType>());
    }

    // opencv drivers
    if( OPENCV::ImageDriverOpenCV<ResourceType>::Is_Write_Supported(pathname) == true ){
        return typename ImageDriverBase<ResourceType>::ptr_t( new OPENCV::ImageDriverOpenCV<ResourceType>());
    }

    // Return null
    return nullptr;
}


/**
 * @brief Read an Image.
 * 
 * @param[in] pathname Image file to read.
 * @param[out] image Image container to read into.
*/
template<typename PixelType>
void Read_Image( FS::FilesystemPath const& pathname, 
                 IMG::Image_<PixelType, IMG::MemoryResource<PixelType>>& output_image )
{

    // make sure the file exists
    if( pathname.Exists() == false ){
        throw std::runtime_error(std::string(std::string("error: File \"") + pathname.ToString() + std::string("\" does not exist.")).c_str());
    }

    // decide which driver to use depending on the filename
    typename ImageDriverBase<IMG::MemoryResource<PixelType>>::ptr_t driver = Get_Read_Driver<IMG::MemoryResource<PixelType>>(pathname);

    // If null, throw an error
    if( driver == nullptr ){
        throw std::runtime_error("Unknown driver.");
    }
    
    // Load the Driver
    output_image.Set_Resource( driver->Read_Image(pathname));
}


/**
 * Read a Disk Image
*/
template <typename PixelType>
void Read_Image( FS::FilesystemPath const& pathname, 
                 IMG::Image_<PixelType,IMG::DiskResource<PixelType> >& output_image )
{

    // make sure the file exists
    if( pathname.Exists() == false ){
        throw std::runtime_error(std::string(std::string("error: File \"") + pathname.ToString() + std::string("\" does not exist.")).c_str());
    }

    // compute the required driver
    typename ImageDriverBase<IMG::DiskResource<PixelType>>::ptr_t image_driver = Get_Read_Driver<IMG::DiskResource<PixelType>>( pathname, 
                                                                                                                                DriverOptions::READ_ONLY );
    
    // create the resource
    typename IMG::DiskResource<PixelType>::ptr_t resource;
    
    // Open the driver    
    image_driver->Open();
    

    // set the resource
    resource->Set_Driver( image_driver );

    // set the driver
    output_image.Set_Resource( resource );

}


/**
 * @brief Write an image to file.
 *
 * @param[in] output_image Image data to write.
 * @param[in] pathname Image pathname to write to.
*/
template <typename PixelType, typename ResourceType>
void Write_Image( IMG::Image_<PixelType,ResourceType>& output_image, 
                  FS::FilesystemPath const& pathname )
{

    // determine the driver type
    typename ImageDriverBase<ResourceType>::ptr_t  driver = Get_Write_Driver<ResourceType>(pathname);

    // Make sure we are not null
    if( driver == nullptr ){
        throw std::runtime_error("No driver returned.");
    }

    // Write
    driver->Write_Image( output_image, pathname );
}



} /// End of IO Namespace
} /// End of GEO Namespace

#endif
