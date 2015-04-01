/**
 * @file    OpenCV_Driver.hpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#ifndef __SRC_CPP_IO_OPENCVDRIVER_HPP__
#define __SRC_CPP_IO_OPENCVDRIVER_HPP__

/// GeoExplore Libraries
#include "../core/Enumerations.hpp"
#include "../image/ChannelType.hpp"
#include "../image/Image.hpp"
#include "../image/PixelCast.hpp"
#include "../image/Pixel_Types.hpp"
#include "../utilities/FilesystemUtilities.hpp"
#include "ImageDriverBase.hpp"
#include "opencv_utils/OpenCV_Utilities.hpp"


/// OpenCV Libraries
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace GEO{
namespace IO{
namespace OPENCV{


/**
 * @class Pixel2OpenCVType
 *
 * @brief Generic Conversion Definition between 3d points and opencv points
*/
template <typename PixelType>
class Pixel2OpenCVType{
    
    public:
    
        typedef typename PixelType::channeltype cvtype;

}; /// End of Pixel2OpenCVType


/**
 * @class Pixel2OpenCVType
 *
 * @brief Convert from grayscale double to double
*/
template <>
class Pixel2OpenCVType<IMG::PixelGray_d>{
    
    public:
    
        typedef double cvtype;

        /**
         * @brief Convert GeoImage Pixel to OpenCV Pixel
         *
         * @param[in] input Input pixel value.
         * @param[out] output Output pixel value.
         */
        static void Pix2CV( IMG::PixelGray_d const& input, 
                            cvtype& output )
        {
            output = input[0];
        }
}; 


/**
 * @class Pixel2OpenCVType
 *
 * @brief Convert from RGB Double to Vec3d
*/
template <>
class Pixel2OpenCVType<IMG::PixelRGB_d>{
    
    public:

        /// OpenCV Type
        typedef typename cv::Vec3d cvtype;

        /// GeoImage Type
        typedef typename IMG::PixelRGB_d geotype;

        /**
         * @brief Convert GeoImage Pixel to OpenCV Pixel.
         *
         * @param[in] input Input pixel value.
         * @param[out] output Output pixel value.
         */
        static void Pix2CV( IMG::PixelRGB_d const& input, cvtype& output ){
            output[0] = input[2];
            output[1] = input[1];
            output[2] = input[0];
        }
}; 


/**
 * @class Pixel2OpenCVType
 *
 * @brief Convert from RGB UInt8 to Vec3b
*/
template <>
class Pixel2OpenCVType<IMG::PixelRGB_u8>{
    
    public:
    
        /// OpenCV Type
        typedef typename cv::Vec3b cvtype;
    
        
        /// GeoImage Type
        typedef typename IMG::PixelRGB_u8 geotype;

        
        /**
         * @brief Convert a GeoImage Pixeltype to OpenCV Pixel Type.
         *
         * @param[in] input Input pixel value.
         * @param[out] output Output pixel value.
         */
        static void Pix2CV( IMG::PixelRGB_u8 const& input, cvtype& output ){
            output[0] = input[2];
            output[1] = input[1];
            output[2] = input[0];
        }
}; 


/**
 * @class Pixel2OpenCVType
 *
 * @brief Convert from RGBA UInt8 to Vec3b.
*/
template <>
class Pixel2OpenCVType<IMG::PixelRGBA_u8>{
    
    public:
    
        /// OpenCV Type
        typedef typename cv::Vec3b cvtype;
        
        /// GeoImage Type
        typedef typename IMG::PixelRGBA_u8 geotype;

        /**
         * @brief Convert PixelType to the OpenCV PixelType.
         *
         * @param[in] input Input pixel type.
         * @param[in] output Output pixel value.
        */
        static void Pix2CV( IMG::PixelRGBA_u8 const& input, 
                            cvtype& output )
        {
            output[0] = input[2];
            output[1] = input[1];
            output[2] = input[0];
        }

}; 


/**
 * @class ImageDriverOpenCV 
*/
template <typename ResourceType>
class ImageDriverOpenCV : public ImageDriverBase<ResourceType>
{

    public:
        
        /// Pixel Type
        typedef typename ResourceType::pixel_type pixel_type;
        
        
        /// Pointer Type
        typedef std::shared_ptr<ImageDriverOpenCV<pixel_type>> ptr_t;
        
        
        /**
         * Open the driver
        */
        virtual void Open()
        {
        }


        /**
         * @brief Open the driver given an image.
         *
         * @param[in] pathname Image pathname.
        */
        virtual void Open( const FS::FilesystemPath& pathname )
        {
        }

        
        /**
         * @brief Check if the driver is supported for write.
         *
         * @param[in] pathname Pathname to check.
         *
         * @return True if supported, false otherwise.
        */
        static bool Is_Write_Supported( FS::FilesystemPath const& pathname )
        {
            // Get file type
            FS::FileType file_type = FS::Get_File_Type(pathname);

            // Check JPEG
            if( file_type == FS::FileType::JPEG ){ return true; }

            // Check PNG
            if( file_type == FS::FileType::PNG ){ return true; }

            // Check TIFF
            if( file_type == FS::FileType::TIFF ){ return true; }

            // otherwise, return false
            return false;
        }
        
        
        /**
         * @brief Check if the driver is supported for reading.
         *
         * @param[in] pathname to check.
         *
         * @return True if supported, false otherwise.
        */
        static bool Is_Read_Supported( FS::FilesystemPath const& pathname ){
            
            // Get file type
            FS::FileType file_type = FS::Get_File_Type(pathname);

            // Check JPEG
            if( file_type == FS::FileType::JPEG ){ return true; }

            // Check PNG
            if( file_type == FS::FileType::PNG ){ return true; }

            // Check TIFF
            if( file_type == FS::FileType::TIFF ){ return true; }

            // otherwise, return false
            return false;
        }


        /**
         * @brief Get the pixel value
         *
         * @param[in] row Row to fetch.
         * @param[in] col Column to fetch.
         *
         * @return Pixel value at image(row,column).
        */
        pixel_type Get_Pixel( const int& row, 
                             const int& col )
        {
            return pixel_type();
        }

    
        /**
         * @brief Get the number of rows.
         *
         * @return Number of rows in image.
        */
        virtual int Rows() const
        {
            return -1;
        }


        /**
         * @brief Get the number of columns.
         *
         * @return Number of columns.
        */
        virtual int Cols() const
        {
            return -1;
        }


        /**
         * @brief Get the image driver type.
         *
         * @return ImageDriverType enumeration.
        */
        virtual ImageDriverType Get_ImageDriverType()const
        {
            return ImageDriverType::OPENCV;
        }
        
        
        /**
         * @brief Read an image from file.
         *
         * @param[in] pathname Image pathname.
         *
         * @return Image resource.
        */
        virtual typename IMG::MemoryResource<pixel_type>::ptr_t Read_Image(  FS::FilesystemPath const& pathname )
        {

            // Make sure the image exists
            if( pathname.Exists() == false ){
                return nullptr;
            }

            // Open the OpenCV Image
            cv::Mat cv_image = cv::imread( pathname.ToString().c_str() );

            // Create the image resource
            typename IMG::MemoryResource<pixel_type>::ptr_t new_resource( new IMG::MemoryResource<pixel_type>(cv_image.rows, cv_image.cols));
            
            // set the pixel values
            for( int r=0; r<cv_image.rows; r++ )
            for( int c=0; c<cv_image.cols; c++ ){
                
                // cast the pixel
                new_resource->operator()(r,c) = IMG::pixel_cast<pixel_type>(IMG::PixelRGB_u8( cv_image.at<cv::Vec3b>(r,c)[2],
                                                                                              cv_image.at<cv::Vec3b>(r,c)[1],
                                                                                              cv_image.at<cv::Vec3b>(r,c)[0]));

            }

            return new_resource;
        }



        /**
         * @brief Write an image to file.
         *
         * @param[in] output_image Image to write to file.
         * @param[in] pathname Image path to write to.
        */
        void Write_Image( IMG::Image_<pixel_type,ResourceType>const& output_image, 
                          FS::FilesystemPath const& pathname )
        {
            
            // convert the output image to an opencv structure
            cv::Mat_<cv::Vec3b> image( output_image.Rows(), output_image.Cols());
    
            // start loading the output image
            for( size_t y=0; y<output_image.Rows(); y++ )
            for( size_t x=0; x<output_image.Cols(); x++ ){
                Pixel2OpenCVType<IMG::PixelRGB_u8>::Pix2CV( IMG::pixel_cast<IMG::PixelRGB_u8>( output_image(y,x)), 
                                                                                               image(y,x) );
            }

            // run imwrite
            cv::imwrite( pathname.ToString().c_str(), image );
        }
        

    private:
        

}; // End of ImageDriverOpenCV Class


} // End of OpenCV Namespace
} // End of IO Namespace
} // End of GEO Namespace

#endif
