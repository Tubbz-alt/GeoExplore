/**
 * @file    Mosaic.hpp
 * @author  Marvin Smith
 * @date    7/17/2014
 */
#ifndef __SRC_MOSAIC_MOSAIC_HPP__
#define __SRC_MOSAIC_MOSAIC_HPP__

// GeoExplore Libraries


// C++ Standard Libraries
#include <deque>
#include <thread>

namespace GEO{
namespace MOS{

/**
 * @class Mosaic
*/
typename <template PixelType>
class Mosaic{

    public:
        
        /**
         * @brief Add Image to Transformer
        */
        void Add_Input_Image( IMG::An_Image<PixelType> const& input_image )
        {


        }

        /**
         * @brief Build Mosaic
        */
        void Generate_Mosaic()const{
        

        }

    private:    
        
        /// List of ground maps
        std::deque<GEOM::Rectangle<double> > m_ground_bboxes;

        /// List of images
        std::deque<IMG::An_Image<PixelType> > m_images;

}; // End of Mosaic Class


} // End of MOS Namespace
} // End of GEO Namespace

#endif
