/**
 * @file    ImageTransformNormalize.hpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#ifndef __GEOEXPLORE_LIB_IMAGE_TRANSFORMS_IMAGETRANSFORMNORMALIZE_HPP__
#define __GEOEXPLORE_LIB_IMAGE_TRANSFORMS_IMAGETRANSFORMNORMALIZE_HPP__

// GeoExplore Libraries
#include "../Image_Utilities.hpp"
#include "ImageTransformColor.hpp"


namespace GEO{
namespace IMG{


/** 
 * @brief Normalization Scheme.
 */
enum class NormalizeMode : uint8_t {
    MINMAX = 0,
}; // End of NormalizeMode Enumeration


/**
 * @class ImageTransformNormalize
 *
 * @brief Implements the Normalization methods for the image classes.
 */
template <typename InputPixelType,
          typename OutputPixelType>
class ImageTransformNormalize : public ImageTransformColor<InputPixelType,OutputPixelType>{

    public:

        
        /// Pointer Type
        typedef std::shared_ptr<ImageTransformNormalize<InputPixelType,OutputPixelType>> ptr_t;


        /// Point Type
        typedef MATH::A_Point2i point_type;

        
        /**
         * @brief Constructor
         *
         * @param[in] input_image Input image to process.
         * @param[in/out] output_image Output image to write to.
         * @param[in] min_value Minimum pixel value.
         * @param[in] max_value Maximum pixel value.
         * @param[in] norm_mode Normalization mode.
         */
        ImageTransformNormalize( typename Image<InputPixelType>::ptr_t&   input_image,
                                 typename Image<OutputPixelType>::ptr_t&  output_image,
                                 InputPixelType const&                    min_value,
                                 InputPixelType const&                    max_value,
                                 NormalizeMode  const&                    norm_mode )
          :  ImageTransformColor<InputPixelType,OutputPixelType>( input_image,
                                                                  output_image ),
             m_class_name("ImageTransformNormalize"),
             m_min_value(min_value),
             m_max_value(max_value),
             m_normalization_mode(norm_mode)
         {
         }
        

        /**
         * @brief Set the min and max values.
         *
         * @param[in] min_act_value Min pixel value.
         * @param[in] max_act_value Max pixel value.
        */
        void Set_Actual_Min_Max_Values( InputPixelType const& min_act_value,
                                        InputPixelType const& max_act_value )
        {
            m_actual_min_value = min_act_value;
            m_actual_max_value = max_act_value;

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

            // Generate normalized input pixel
            InputPixelType normalized_pixel;
            InputPixelType input_pixel = (*this->m_input_image)(input_pixel_location);
            double norm_range;
            for( int i=0; i<normalized_pixel.Dims(); i++ ){

                // If we are using minmax
                if( m_normalization_mode == NormalizeMode::MINMAX ){
                    norm_range = m_max_value[i] - m_min_value[i];
                    normalized_pixel[i] = (((double)input_pixel[i] - m_actual_min_value[i])/(m_actual_max_value[i] - m_actual_min_value[i])) * norm_range + m_min_value[i]; 
                }
            }

            // Pixel Cast
            output_pixel = pixel_cast<OutputPixelType>( normalized_pixel );

            // return success
            return Status(StatusType::SUCCESS);
        }


    private:
        
        /// Class Name
        std::string m_class_name;
        
        /// Min Value
        InputPixelType m_min_value;

        /// Max Value
        InputPixelType m_max_value;
        
        /// Min Value
        InputPixelType m_actual_min_value;

        /// Max Value
        InputPixelType m_actual_max_value;


        /// Normalization Mode
        NormalizeMode m_normalization_mode;



}; // End of ImageTransformNormalize Method


/**
 * @brief Normalize the image
 *
 * @param[in] input_image Image to normalize.
 * @param[out] output_image Written result.
 * @param[in] min_value Minimum pixel value.
 * @param[in] max_value Maximum pixel value.
 * @param[in] norm_mode Normalization mode.
 * @param[in] number_threads Number of threads to use.
*/
template <typename InputPixelType, typename OutputPixelType=InputPixelType>
Status Normalize_Image( typename Image<InputPixelType>::ptr_t&    input_image,
                        typename Image<OutputPixelType>::ptr_t&   output_image,
                        InputPixelType const&                     min_value,
                        InputPixelType const&                     max_value,
                        NormalizeMode  const&                     norm_mode,
                        const int&                                number_threads = 1 )
{

    // Status
    Status status;

    // Create the transform
    ImageTransformNormalize<InputPixelType,OutputPixelType>  norm_transform( input_image, 
                                                                             output_image,
                                                                             min_value,
                                                                             max_value,
                                                                             norm_mode );
    
    // Compute Image Min and Max
    InputPixelType actual_min, actual_max;
    status = MinMax( (*input_image), actual_min, actual_max );
    if( status.Get_Status_Type() != StatusType::SUCCESS ){
        return status;
    }
    norm_transform.Set_Actual_Min_Max_Values( actual_min, actual_max );

    // Pass to the base method
    return Process_Transform( norm_transform, 
                              number_threads );




}

} // End of IMG Namespace
} // End of GEO Namespace


#endif
