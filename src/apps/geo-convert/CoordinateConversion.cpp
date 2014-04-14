/**
 * @file    CoordinateConversion.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#include "CoordinateConversion.hpp"

#include <GeoExplore.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;


/**
 * Convert coordinates
 */
void convert_coordinates( Options const& options ){

    // get each input and parse
    for( size_t i=0; i<options.inputs.size(); i++ ){
        
        // convert the input to a coordinate
        vector<string> components = GEO::string_split( options.inputs[i], ":");
       
        // get the conversion type
        string ctype = components[0];
        
        // convert the string to utm
        if( ctype == "-utm" ){
            

        }

        // convert the string to geodetic dd
        else if( ctype == "-geod-dd" ){

        }

        // convert the string to geodetic dm
        else if( ctype == "-geod-dm" ){


        }

        // convert the string to geodetic dms
        else if( ctype == "-geod-dms" ){


        }

        // otherwise we won't know the conversion and must throw an error
        else{


        }

    }

}

