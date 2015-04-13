/**
 * @file    ImageTransformColorMap.hpp
 * @author  Marvin Smith
 * @date    3/28/2015
*/
#ifndef __GEOEXPLORE_IMAGE_TRANSFORMS_IMAGETRANSFORM_COLORMAP_HPP__
#define __GEOEXPLORE_IMAGE_TRANSFORMS_IMAGETRANSFORM_COLORMAP_HPP__

// C++ Standard Libraries
#include <sstream>

// GeoExplore Libraries
#include "../../math/Common_Equations.hpp"
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


        /**
         * @brief Get Input Pixel.
         *
         * @return Input pixel value.
        */
        InputPixelType Get_Input_Pixel()const{
            return m_input_pixel;
        }


        /**
         * @brief Get the Output Pixel.
         *
         * @return Output pixel value.
        */
        OutputPixelType Get_Output_Pixel()const{
            return m_output_pixel;
        }

        
        /**
         * @brief Less-Than Operator
         *
         * @param[in] other Color pair to compare.
         *
         * @return True if less than.
        */
        bool operator < ( A_Color_Map_Pair const& other )const{
            return (m_input_pixel[0] < other.m_input_pixel[0]);
        }


        /**
         * @brief Print as a pretty string.
         *
         * @return Pretty string.
        */
        std::string ToPrettyString()const{
            std::stringstream sin;
            sin << "A_Color_Map_Pair( " << m_input_pixel.ToPrettyString() << ", " << m_output_pixel.ToPrettyString() << " )";
            return sin.str();
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
        
        /**
         * @brief Constructor
        */
        A_Color_Map()
          : m_class_name("A_Color_Map")
        {
        }


        /**
         * @brief Constructor
         *
         * @param[in] color_map_pairs Color map pair list.
        */
        A_Color_Map( const std::vector<A_Color_Map_Pair<InputPixelType,OutputPixelType>>& color_map_pairs )
          : m_class_name("A_Color_Map"),
            m_color_map_pairs(color_map_pairs)
        {
        }


        /**
         * @brief Add Color Map Pair.
         *
         * @param[in] input_color Input color.
         * @param[in] output_color Output color.
        */
        void Add_Color_Pair( const InputPixelType&   input_pixel,
                             const OutputPixelType&  output_pixel )
        {
            // Add the color pair
            m_color_map_pairs.push_back( A_Color_Map_Pair<InputPixelType,OutputPixelType>(input_pixel,
                                                                                          output_pixel));
            
            // Sort the color pairs
            std::sort( m_color_map_pairs.begin(), m_color_map_pairs.end() );
        }


        /**
         * @brief Interpolate the color
         *
         * @param[in] input_color Input color to interpolate.
         * 
         * @return Output pixel color.
        */
        OutputPixelType  Interpolate_Color( InputPixelType const& input_color )const
        {
            // Make sure map set is not empty.
            if( m_color_map_pairs.size() <= 0 ){
                std::cerr << "Warning: Should not be here. File: " << __FILE__ << ", Func: " << __func__ << ", " << __LINE__ << ". " << std::endl;
                return OutputPixelType();
            }

            // If there is only one pair, return it
            if( m_color_map_pairs.size() <= 1 ){
                return m_color_map_pairs[0].Get_Output_Pixel();
            }
            
            // Iterate over pairs
            if( input_color[0] < m_color_map_pairs[0].Get_Input_Pixel()[0] ){
                return m_color_map_pairs[0].Get_Output_Pixel();
            }
            if( input_color[0] >= m_color_map_pairs.back().Get_Input_Pixel()[0] ){
                return m_color_map_pairs.back().Get_Output_Pixel();
            }

            int index = -1;
            for( int i=1; i<m_color_map_pairs.size(); i++ ){
                if( input_color[0] < m_color_map_pairs[i].Get_Input_Pixel()[0] ){
                    index = i-1;
                    break;
                }
            }

            const double ratio = (input_color[0] - m_color_map_pairs[index].Get_Input_Pixel()[0])/
                                 (  m_color_map_pairs[index+1].Get_Input_Pixel()[0] - 
                                    m_color_map_pairs[index].Get_Input_Pixel()[0]);

            // Interpolate
            OutputPixelType output;
            for( int i=0; i<output.Dims(); i++ ){
                output[i] = MATH::LERP<typename OutputPixelType::datatype>( m_color_map_pairs[index  ].Get_Output_Pixel()[i],
                                                                            m_color_map_pairs[index+1].Get_Output_Pixel()[i],
                                                                            ratio );

            }
            
            return output;
        }
        

        /**
         * Print as pretty string.
         *
         * @return Pretty String.
        */
        std::string ToPrettyString()const{
            std::stringstream sin;
            sin << "A_Color_Map: " << std::endl;
            for( int i=0; i<m_color_map_pairs.size(); i++ ){
                sin << "  " << m_color_map_pairs[i].ToPrettyString() << std::endl;
            }
            return sin.str();
        }
        

        /**
         * Get Color Map Pair
         *
         * @param[in] index Index to get.
         *
         * @return Color Map Pair.
        */
        A_Color_Map_Pair<InputPixelType,OutputPixelType> Get_Color_Map_Pair( const int& index )const{
            return m_color_map_pairs[index];
        }


        /**
         * @brief Get Number of Color Map Pairs.
         *
         * @return number of color map pairs.
        */
        int Get_Number_Of_Color_Map_Pairs()const{
            return m_color_map_pairs.size();
        }


    private:
        
        /// Class Name
        std::string m_class_name;

        /// List of Color Map Pairs
        std::vector<A_Color_Map_Pair<InputPixelType,OutputPixelType>> m_color_map_pairs;


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

        
        /// Color Map Type
        typedef A_Color_Map<InputPixelType,OutputPixelType> color_map_type;


        /**
         * @brief Constructor
         *
         * @param[in] input_image Input image.
         * @param[in/out] output_image Output image to map.
        */
        ImageTransformColorMap( typename Image<InputPixelType>::ptr_t&   input_image,
                                typename Image<OutputPixelType>::ptr_t&  output_image,
                                color_map_type const&                    color_map )
          : ImageTransformColor<InputPixelType,OutputPixelType>( input_image,
                                                                 output_image ),
            m_class_name("ImageTransformColorMap"),
            m_color_map( color_map )
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

            // Iterpolate the color
            output_pixel = m_color_map.Interpolate_Color( (*this->m_input_image)(input_pixel_location));

            // Return success
            return Status(StatusType::SUCCESS);
        }
        

    private:

        /// Class Name
        std::string m_class_name;

        /// Color Map
        color_map_type m_color_map;


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
Status Compute_Color_Map( typename Image<InputPixelType>::ptr_t&              input_image,
                          typename Image<OutputPixelType>::ptr_t&             output_image,
                          const A_Color_Map<InputPixelType,OutputPixelType>&  color_map,
                          const int&                                          number_threads = 1 )
{
    
    // Check if output image exists, create otherwise
    if( output_image == nullptr )
    {
        output_image = typename Image<OutputPixelType>::ptr_t( new IMG::Image<OutputPixelType>( input_image->Rows(),
                                                                                                input_image->Cols()));
    }

    // Create the transform
    ImageTransformColorMap<InputPixelType,OutputPixelType> color_map_transform( input_image,
                                                                                output_image,
                                                                                color_map );

    // Pass to base method
    return Process_Transform( color_map_transform, number_threads );

}



} // End of IMG Namespace
} // End of GEO Namespace

#endif
