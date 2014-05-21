/**
 * @file    OpenCV_Driver.hpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#ifndef __SRC_CPP_IO_OPENCVDRIVER_HPP__
#define __SRC_CPP_IO_OPENCVDRIVER_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>
#include <GeoExplore/image/ChannelType.hpp>
#include <GeoExplore/image/Image.hpp>
#include <GeoExplore/image/PixelCast.hpp>
#include <GeoExplore/image/PixelGray.hpp>
#include <GeoExplore/image/PixelRGB.hpp>

/// OpenCV Libraries
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace GEO{
namespace IO{
namespace OPENCV{

/**
 * Generic Conversion Definition between 3d points and opencv points
*/
template <typename PixelType>
struct Pixel2OpenCVType{
    typedef typename PixelType::channeltype cvtype;
}; /// End of Pixel2OpenCVType

/**
 * Convert from grayscale double to double
*/
template <>
struct Pixel2OpenCVType<PixelGray_d>{
    typedef double cvtype;

    static void Pix2CV( PixelGray_d const& input, cvtype& output ){
        output = input[0];
    }
}; 

/**
 * Convert from RGB Double to Vec3d
*/
template <>
struct Pixel2OpenCVType<PixelRGB_d>{
    typedef typename cv::Vec3d cvtype;

    static void Pix2CV( PixelRGB_d const& input, cvtype& output ){
        output[0] = input[2];
        output[1] = input[1];
        output[2] = input[0];
    }
}; 

/**
 * Convert from RGB UInt8 to Vec3b
*/
template <>
struct Pixel2OpenCVType<PixelRGB_u8>{
    typedef typename cv::Vec3b cvtype;

    static void Pix2CV( PixelRGB_u8 const& input, cvtype& output ){
        output[0] = input[2];
        output[1] = input[1];
        output[2] = input[0];
    }
}; 


/**
 * @class ImageDriverOpenCV 
*/
class ImageDriverOpenCV : public ImageDriverBase {

    public:
        
        /**
         * Get the pixel value
        */
        template <typename PixelType>
        PixelType getPixel( const int& x, const int& y )const{
            return PixelType();
        }
    
        /**
         * Get the number of rows
        */
        virtual int rows()const;

        /**
         * Get the number of columns
        */
        virtual int cols()const;

        /**
         * Get the image driver type
        */
        virtual ImageDriverType type()const;
        
        /**
         * Write an image to file
        */
        template <typename PixelType, typename ResourceType>
        static void write_image( Image_<PixelType,ResourceType>const& output_image, boost::filesystem::path const& pathname ){
            
            // convert the output image to an opencv structure
            cv::Mat_<cv::Vec3b> image( output_image.rows(), output_image.cols());
    
            // start loading the output image
            for( size_t y=0; y<output_image.rows(); y++ ){
            for( size_t x=0; x<output_image.cols(); x++ ){
                Pixel2OpenCVType<PixelRGB_u8>::Pix2CV( pixel_cast<PixelRGB_u8>(output_image(y,x)), image(y,x) );
            }}

            // run imwrite
            cv::imwrite( pathname.c_str(), image );
        }
        
        /**
         * Open the driver
        */
        void open();

        /**
         * Open the driver given an image filename
        */
        void open( const boost::filesystem::path& pathname );
    private:
        
        /// open the file


}; /// End of ImageDriverOpenCV Class


} /// End of OpenCV Namespace
} /// End of IO Namespace
} /// End of GEO Namespace

#endif
