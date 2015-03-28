/**
 * @file    ImageTransformColor.hpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#ifndef __GEOEXPLORE_LIB_IMAGE_TRANSFORMS_IMAGETRANSFORM_COLOR_HPP__
#define __GEOEXPLORE_LIB_IMAGE_TRANSFORMS_IMAGETRANSFORM_COLOR_HPP__

// GeoExplore Libraries
#include "ImageTransformBase.hpp"

namespace GEO{
namespace IMG{

/**
 * @class ImageTransformColor
*/
template < typename InputPixelType,
           typename OutputPixelType >
class ImageTransformColor : public ImageTransformBase<InputPixelType,OutputPixelType>
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<ImageTransformColor<InputPixelType,OutputPixelType>> ptr_t;

        /// Output Image Point Type
        typedef MATH::A_Point2i point_type;
        
        
        /**
         * @brief Constructor
        */
        ImageTransformColor( typename Image<InputPixelType>::ptr_t   input_image,
                             typename Image<OutputPixelType>::ptr_t  output_image )
          : ImageTransformBase<InputPixelType,OutputPixelType>( input_image,
                                                                output_image ),
            m_class_name("ImageTransformColor")
        {
        }
                             
        
    protected:        
        
        /**
         * @brief Compute the Output Pixel Value.
         *
         * @param[in] row Output image row.
         * @param[in] col Output image column.
         * @param[out] output_pixel Output pixel to set.
         *
         * @return Status of the operation.
        */
        virtual Status Compute_Output_Pixel_Value( const point_type&  output_pixel_location,
                                                   OutputPixelType&   output_pixel )
        {
            // Status 
            Status status;

            // Variables
            point_type input_pixel_location;
            
            // Compute the input pixel location
            status = Compute_Input_Pixel_Coordinate( output_pixel_location,
                                                     input_pixel_location );

            if( status.Get_Status_Type() != StatusType::SUCCESS ){
                return status;
            }


            // Compute the output pixel color
            return  Compute_Output_Pixel_Color( input_pixel_location, 
                                                output_pixel );
        
        }

        
        /**
         * @brief Compute the input image pixel coordinate.
         *
         * @param[in] output_pixel_location Pixel location in output image.
         * @param[out] input_pixel_location Pixel location in input image.
         *
         * @return Status of the operation.
         */
        virtual Status Compute_Input_Pixel_Coordinate( point_type const& output_pixel_location,
                                                       point_type&       input_pixel_location ) const
        {
            input_pixel_location = output_pixel_location;
            return Status(StatusType::SUCCESS );
        }
        

        /**
         * @brief Compute the Pixel Color
         *
         * @param[in] input_pixel_location Input pixel location.
         * @param[out] output_pixel Pixel to set.
         *
         * @return status of the operation.
        */
        virtual Status Compute_Output_Pixel_Color( point_type const&  input_pixel_location,
                                                   OutputPixelType&   output_pixel ) = 0;


    private:
        
        /// Class Name
        std::string m_class_name;


}; // End of ImageTransformColor Class


} // End of IMG Namespace
} // End of GEO Namespace


#endif
