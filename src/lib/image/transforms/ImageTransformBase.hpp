/**
 * @file    ImageTransformBase.hpp
 * @author  Marvin Smith
 * @date    3/26/2015
*/
#ifndef __GEOEXPLORE_LIB_IMAGE_TRANSFORMS_IMAGETRANSFORMBASE_HPP__
#define __GEOEXPLORE_LIB_IMAGE_TRANSFORMS_IMAGETRANSFORMBASE_HPP__

// GeoExplore Libraries
#include "../Image.hpp"
#include "../../core/A_Status.hpp"
#include "../../math/A_Point.hpp"

// C++ Standard Libraries
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace GEO{
namespace IMG{


/**
 * @class ImageTransformBase
*/
template <typename InputPixelType, 
          typename OutputPixelType>
class ImageTransformBase{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<ImageTransformBase<InputPixelType,OutputPixelType>> ptr_t;

        /// Point Type
        typedef MATH::A_Point2i point_type;


        /**
         * @brief Constructor
         *
         * @param[in] input_image Input image pointer.
         * @param[out] output_image Output image pointer.
         */
        ImageTransformBase( typename Image<InputPixelType>::ptr_t&  input_image,
                            typename Image<OutputPixelType>::ptr_t& output_image )
          : m_input_image(input_image),
            m_output_image(output_image),
            m_class_name("ImageTransformBase")
        {
        }


        /**
         * @brief Render the image.
         */
        virtual Status Render_Image()
        {

            // Check that we have the required information
            if( m_input_image == nullptr ){
                return Status( StatusType::FAILURE, TransformStatusReason::INPUT_IMAGE_NULL,
                               "Input image is null. Unable to process.");
            }
            if( m_output_image == nullptr ){
                return Status( StatusType::FAILURE, TransformStatusReason::OUTPUT_IMAGE_NULL,
                               "Output image is null. Unable to process.");
            }
            

            // Image Size
            const int number_pixels = m_input_image->Rows() * m_input_image->Cols();

            // Iterate over the image
            return Render_Image_Block( 0, number_pixels );


        }

        
        /**
         * @brief Render Image Block
         *
         * @param[in] start_position Starting index to iterate over.
         * @param[in] number_pixels  Number of pixels to process.
        */
        virtual Status Render_Image_Block( const int& start_position,
                                           const int& number_pixels )
        {
            // variables
            point_type output_pixel_location;
            Status status;
            OutputPixelType output_pixel;
            
            // Start iterating
            for( int pidx = start_position;
                 pidx < start_position + number_pixels; 
                 pidx++ )
            {

                // Compute the row and column
                status = Compute_Output_Pixel_Coordinate( pidx, output_pixel_location );

                if( status.Get_Status_Type() != StatusType::SUCCESS ){
                    std::stringstream sin;
                    sin << "Warning: Compute_Input_Pixel_Coordinate(" << pidx << ", " << output_pixel_location.ToPrettyString() << ") Failed." << std::endl;
                    std::cerr << sin.str() << std::endl;
                    continue;
                }

                // Compute the Output Pixel Value
                status = Compute_Output_Pixel_Value( output_pixel_location, 
                                                     output_pixel );

                if( status.Get_Status_Type() != StatusType::SUCCESS ){
                    continue;
                }

                // Set the output pixel value
                m_output_image->operator()(output_pixel_location) = output_pixel;

            }
            
            // Return success
            return status;
        }

        /**
         * @brief Thread Runner for Render Image Block Method.
         *
         * 
        */
        static void Render_Image_Block_Runner( ptr_t& transform, 
                                               const int& start_position,
                                               const int& number_pixels )
        {

            transform->Render_Image_Block( start_position, 
                                           number_pixels );

        }


        /**
         * @brief Get the number of pixels to render.
         *
         * @return Number of pixels to render.
        */
        int Get_Render_Block_Size()const{
            return (m_output_image->Rows() * m_output_image->Cols());
        }


    protected:
            
        /**
         * @brief Compute the Input Pixel Coordinates from the index.
         *
         * @param[in]  index Index position.
         * @param[out] output_pixel_location Output image pixel location.
         * 
         * @return Status of the operation.
        */
        virtual Status Compute_Output_Pixel_Coordinate( const int& pidx,
                                                        point_type& output_pixel_location )
        {
            // Determine row and column values
            output_pixel_location.x() = pidx % m_output_image->Cols();
            output_pixel_location.y() = pidx / m_output_image->Cols();

            // Return success
            return Status( StatusType::SUCCESS );
        }


        /**
         * @brief Compute the Output Pixel Value.
         *
         * @param[in] output_pixel_location Output pixel location.
         * @param[out] output_pixel Output pixel to set.
         *
         * @return Status of the operation.
        */
        virtual Status Compute_Output_Pixel_Value( const point_type& output_pixel_location,
                                                   OutputPixelType& output_pixel ) = 0;



        /// Input Image
        typename Image<InputPixelType>::ptr_t m_input_image;

        /// Output Image
        typename Image<OutputPixelType>::ptr_t m_output_image;

    private:
        
        /// Class Name
        std::string m_class_name;


}; // End of ImageTransformBase Class


/**
 * @brief Run the transform.
 *
 * @param[in] transform Transform to run.
 * @param[in] number_threads Number of threads to run. If < 1, then it will check the system.
 *
 * @return Status of the operation.
*/
template <typename TransformType>
Status Process_Transform( TransformType&  transform, 
                          const int&      number_threads )
{

    // Check the number of threads
    int num_threads = number_threads;
    if( num_threads <= 0 ){
        num_threads = std::thread::hardware_concurrency();
    }

    if( num_threads <= 0 ){
        return Status( StatusType::FAILURE, TransformStatusReason::INVALID_THREADS,
                       "Cannot have less than 1 threads.");
    }

    // Thread block
    const int render_block_size = transform.Get_Render_Block_Size();
    const int thread_block_size = render_block_size/num_threads;

    // Build the starting position list
    std::vector<int> start_position_list(num_threads, 0);
    std::vector<int> number_pixel_list(num_threads, 0);

    // Start with the first threads
    start_position_list[0] = 0;
    number_pixel_list[0] = thread_block_size;
    for( int i=0; i<num_threads; i++ ){
        start_position_list[i] = start_position_list[i-1] + thread_block_size;
        
        // If we have a non-divisible render size, then we will have smaller end regions.
        if( start_position_list[i] + thread_block_size > (render_block_size-1) )
        {
            number_pixel_list[i] = render_block_size - start_position_list[i] - 1;
            break;
        }
        else{
            number_pixel_list[i] = thread_block_size;
        }
    }
    
    // Create the threads
    std::vector<std::thread> thread_list;

    // Iterate over each thread
    for( int i=0; i<num_threads; i++ ){
        //thread_list.push_back(std::thread(  &ImageTransformBase::Render_Image_Block_Runner, 
        //                                    transform,
        //                                    start_position_list[i],
        //                                    number_pixel_list[i]) );
    }
    transform.Render_Image();

    // Join Each Thread
    for( size_t i=0; i<thread_list.size(); i++ ){
        thread_list[i].join();
    }

    return Status( StatusType::SUCCESS );
}


} // End of IMG Namespace
} // End of GEO Namespace

#endif
