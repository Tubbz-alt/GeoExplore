/**
 * @file    ImageConversion.cpp
 * @author  Marvin Smith
 * @date    5/14/2014
*/
#include "ImageConversion.hpp"

/// C++ Standard Libraries
#include <iostream>

/// GeoExplore Library
#include <GeoExplore.hpp>


/**
 * Convert Images
*/
void convert_images( const Options& options ){

    // iterate through each input image in the list
    for( size_t i=0; i<options.inputs.size(); i++ ){

        // read the image
        GEO::Image<GEO::PixelRGB_d> input_image;
        GEO::IO::read_image( options.inputs[i], input_image );

        // write the image
        GEO::IO::write_image( input_image, options.outputs[i] );
    }


}

