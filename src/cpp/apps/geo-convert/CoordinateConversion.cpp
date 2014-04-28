/**
 * @file    CoordinateConversion.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#include "CoordinateConversion.hpp"

/// GeoExplore Library
#include <GeoExplore.hpp>

/// C++ Libraries
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/// Geo-Convert Libraries
#include "Utilities.hpp"

using namespace std;


/**
 * Convert coordinates
 */
void convert_coordinates( Options const& options ){

    // create a list of input coordinates
    std::vector<GEO::CoordinateBaseDouble::ptr_t> input_coordinates;


    // get each input and parse
    for( size_t i=0; i<options.inputs.size(); i++ ){
        
        // convert the input to a coordinate
        vector<string> components = GEO::string_split( options.inputs[i], ":");
       
        // get the conversion type
        string ctype = components[0];
        
        // convert the string to utm
        if( ctype == "-utm" ){
            
            // make sure there are spots for easting and northing
            if( components.size() < 3 ){
                throw std::runtime_error("(UTM) Not enough components in the input line to provide easting and northing at a minimum.");
            }

            // create our coordinate
            GEO::CoordinateUTM_d::ptr_t point( new GEO::CoordinateUTM_d());

            // set easting
            point->easting() = GEO::str2num<double>(components[1]);

            // set northing
            point->northing() = GEO::str2num<double>(components[2]);

            // set altitude if given
            if( components.size() >= 4 ){
                point->altitude() = GEO::str2num<double>(components[3]);
            }
            
            // add the point to our list
            input_coordinates.push_back(point);

        }

        // convert the string to geodetic dd
        else if( ctype == "-geod-dd" ){
            
            // make sure there are spots for latitude and longitude
            if( components.size() < 3 ){
                throw std::runtime_error("(Geod-DD) Not enough components in the input line to provide latitude and longitude.");
            }

            // create our coordinate
            GEO::CoordinateGeodetic_d::ptr_t point( new GEO::CoordinateGeodetic_d());

            // set the latitude
            point->latitude() = GEO::str2num<double>(components[1]);

            // set the longitude
            point->longitude() = GEO::str2num<double>(components[2]);

            // set the altitude if given
            if( components.size() >= 4 ){
                point->altitude() = GEO::str2num<double>(components[3]);
            }

            //add the point to our list
            input_coordinates.push_back(point);

        }

        // convert the string to geodetic dm
        else if( ctype == "-geod-dm" ){
            
            throw std::runtime_error("Not implemented yet.");

        }

        // convert the string to geodetic dms
        else if( ctype == "-geod-dms" ){

            throw std::runtime_error("Not implemented yet.");

        }

        // otherwise we won't know the conversion and must throw an error
        else{

            throw std::runtime_error((string(ctype) + string(" is not a supported conversion type.")).c_str());

        }

    }

    // now run coordinate conversion on each coordinate
    for( size_t i=0; i<input_coordinates.size(); i++ ){

        // check the output type
        GEO::CoordinateType outputCoordinateType;
        
        //GEO::CoordinateType 
        if( options.outputs.size() == 1 ){
            outputCoordinateType = String2CoordinateType(options.outputs[0]); 
        }
        else{
            throw std::runtime_error("Only 1 output type must be specified.");
        }

        // convert the coordinate
        //GEO::CoordinateBaseDouble::ptr_t converted_coordinate = GEO::convert_coordinate( input_coordinates[i], output_types[i], 

    }


}

