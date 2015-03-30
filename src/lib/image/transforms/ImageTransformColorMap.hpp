/**
 * @file    ImageTransformColorMap.hpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#ifndef __GEOEXPLORE_IMAGE_TRANSFORMS_IMAGETRANSFORM_COLORMAP_HPP__
#define __GEOEXPLORE_IMAGE_TRANSFORMS_IMAGETRANSFORM_COLORMAP_HPP__

// GeoExplore Libraries
#include "ImageTransformColor.hpp"

namespace GEO{
namespace IMG{

/**
 * @class A_Color_Map_Pair
 *
 * @brief Maps two pixel values together.
*/
template <typename InputPixelType,
          typename OutputPixelType>
class A_Color_Map_Pair{

    public:
        
        /**
         * @brief Constructor
         *
         * @param[in] input_pixel Input pixel to reference.
         * @param[in] output_pixel Output pixel to map to.
         */
        A_Color_Map_Pair( InputPixelType  const& input_pixel,
                          OutputPixelType const& output_pixel )
          : m_class_name("A_Color_Map_Pair"),
            m_input_pixel(input_pixel),
            m_output_pixel(output_pixel)
        {
        }


    private:

        /// Class Name
        std::string m_class_name;

        /// Input Pixel
        InputPixelType  m_input_pixel;

        /// Output Pixel
        OutputPixelType m_output_pixel;


}; // End of A_Color_Map_Pair Class



/**
 * @class A_Color_Map
 *
 * @brief Contains the mapping between input and output color values.
*/
template <typename InputPixelType,
          typename OutputPixelType>
class A_Color_Map{

    public:
        


    private:



}; // End of A_Color_Map Class

/**
 * @class ImageTransformColorMap
*/
template <typename InputPixelType,
          typename OutputPixelType>
class ImageTransformColorMap : public ImageTransformColor<InputPixelType,OutputPixelType>
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<ImageTransformColorMap<InputPixelType,OutputPixelType>> ptr_t;

        
        /// Point Type
        typedef MATH::A_Point2i point_type;


        /**
         * @brief Constructor
         *
         * @param[in] input_image Input image.
         * @param[in/out] output_image Output image to map.
        */
        ImageTransformColorMap( typename Image<InputPixelType>::ptr_t&   input_image,
                                typename Image<OutputPixelType>::ptr_t&  output_image )
          : ImageTransformColor<InputPixelType,OutputPixelType>( input_image,
                                                                 output_image ),
            m_class_name("ImageTransformColorMap")
        {
        }
    
    
    protected:
        
        
        /**
         * @brief Compute the pixel color.
         *
         * @param[in] input_pixel_location Input pixel location to grab.
         * @param[in] output_pixel Output pixel to set.
         *
         * @return Status of the operation.
        */
        virtual Status Compute_Output_Pixel_Color( point_type const&  input_pixel_location,
                                                   OutputPixelType&   output_pixel )
        {

            // Not implemented yet
            return Status(StatusType::FAILURE, CoreStatusReason::NOT_IMPLEMENTED, "Method not implemented yet.");


            // Return success
            return Status(StatusType::SUCCESS);
        }
        

    private:

        /// Class Name
        std::string m_class_name;



}; // End of ImageTransformColorMap Class


/**
 * @brief Compute Color Map
 *
 * @param[in] input_image Image to evaluate.
 * @param[out] output_image  Resulting color map.
 * @param[in]  number_threads Number of threads to process transform with.
 *
 * @return Status of the operation.
*/
template <typename InputPixelType, typename OutputPixelType>
Status Compute_Color_Map( typename Image<InputPixelType>::ptr_t&    input_image,
                          typename Image<OutputPixelType>::ptr_t&   output_image,
                          const int& number_threads = 1 )
{

    // Create the transform
    ImageTransformColorMap<InputPixelType,OutputPixelType> color_map_transform( input_image,
                                                                                output_image );

    // Pass to base method
    return Process_Transform( color_map_transform, number_threads );

}



} // End of IMG Namespace
} // End of GEO Namespace

#endif
