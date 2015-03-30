/**
 * @file    ImageTransformInvert.hpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#ifndef __GEOEXPLORE_LIB_IMAGE_TRANSFORM_IMAGETRANSFORMINVERT_HPP__
#define __GEOEXPLORE_LIB_IMAGE_TRANSFORM_IMAGETRANSFORMINVERT_HPP__

// GeoExplore Libraries
#include "ImageTransformColor.hpp"
#include "../PixelCast.hpp"

namespace GEO{
namespace IMG{


template <typename InputPixelType,
          typename OutputPixelType>
class ImageTransformInvert : public ImageTransformColor<InputPixelType,OutputPixelType>
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<ImageTransformInvert<InputPixelType,OutputPixelType>> ptr_t;
        
        /// Point Type
        typedef MATH::A_Point2i point_type;

        /**
         * @brief Constructor
        */
        ImageTransformInvert( typename Image<InputPixelType>::ptr_t&   input_image,
                              typename Image<OutputPixelType>::ptr_t&  output_image )
          : ImageTransformColor<InputPixelType,OutputPixelType>( input_image,
                                                                 output_image ),
            m_class_name("ImageTransformInvert")
        {
        }

        
    protected:

        /**
         * @brief Compute the Pixel Color
         *
         * @param[in] input_pixel_location Input pixel location.
         * @param[out] output_pixel Pixel to set.
         *
         * @return status of the operation.
        */
        virtual Status Compute_Output_Pixel_Color( point_type const& input_pixel_location,
                                                   OutputPixelType&  output_pixel )
        {

            // Pixel Cast
            output_pixel = pixel_cast<OutputPixelType>( OutputPixelType::White() - (*this->m_input_image)(input_pixel_location) );

            // return success
            return Status(StatusType::SUCCESS);
        }


    private:
          
        /// Class Name
        std::string m_class_name;

}; // End of ImageTransformInvert Class


/**
 * @brief Invert an image
 *
 * @param[in]   input_image Image to invert.
 * @param[out]  output_image Image result.
 * @param[in] number_threads Number of threads to process with.
 *
 * @return Status of the operation.
*/
template <typename InputPixelType, typename OutputPixelType=InputPixelType>
Status Invert_Image( typename Image<InputPixelType>::ptr_t&   input_image,
                     typename Image<OutputPixelType>::ptr_t&  output_image,
                     const int& number_threads = 1)
{


    // Create the transform
    ImageTransformInvert<InputPixelType,OutputPixelType>  invert_transform( input_image, 
                                                                            output_image );

    // Pass to the base method
    return Process_Transform( invert_transform, 
                              number_threads );
}


} // End of IMG Namespace
} // End of GEO Namespace

#endif
