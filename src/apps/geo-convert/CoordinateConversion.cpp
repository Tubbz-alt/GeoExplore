/**
 * @file    CoordinateConversion.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#include "CoordinateConversion.hpp"

/// GeoExplore Library
#include <GeoExplore.hpp>

/// C++ Libraries
#include <iomanip>
#include <iostream>
#include <memory>
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
    std::vector<GEO::CRD::CoordinateBaseDouble::ptr_t> input_coordinates;


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
            GEO::CRD::CoordinateUTM_d::ptr_t point( new GEO::CRD::CoordinateUTM_d());

            // set easting
            point->easting_meters() = GEO::str2num<double>(components[1]);

            // set northing
            point->northing_meters() = GEO::str2num<double>(components[2]);

            // set altitude if given
            if( components.size() >= 4 ){
                point->altitude_meters() = GEO::str2num<double>(components[3]);
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
            GEO::CRD::CoordinateGeographic_d::ptr_t point( new GEO::CRD::CoordinateGeographic_d());

            // set the latitude
            point->latitude_degrees() = GEO::str2num<double>(components[1]);

            // set the longitude
            point->longitude_degrees() = GEO::str2num<double>(components[2]);

            // set the altitude if given
            if( components.size() >= 4 ){
                point->altitude_meters() = GEO::str2num<double>(components[3]);
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
        GEO::CRD::CoordinateBaseDouble::ptr_t converted_coordinate = GEO::CRD::convert_coordinate<double>( input_coordinates[i], 
                                                                                                           outputCoordinateType, 
                                                                                                           input_coordinates[i]->datum() ); 
        
        // convert to output
        // utm
        if( converted_coordinate->type() == GEO::CoordinateType::UTM ){
            GEO::CRD::CoordinateUTM_d::ptr_t output = std::dynamic_pointer_cast<GEO::CRD::CoordinateUTM_d>(converted_coordinate);
            cout << output->zone() << ",";
            cout << (int64_t)output->easting_meters() << ",";
            cout << (int64_t)output->northing_meters() << ",";
            cout << (int64_t)output->altitude_meters() << endl;
        }
        // geodetic dd
        else if( converted_coordinate->type() == GEO::CoordinateType::Geographic ){
            GEO::CRD::CoordinateGeographic_d::ptr_t output = std::dynamic_pointer_cast<GEO::CRD::CoordinateGeographic_d>(converted_coordinate);
            cout << std::fixed << output->latitude_degrees() << "," << output->longitude_degrees() << "," << output->altitude_meters() << endl;
        } else {
            throw std::runtime_error("Unknown coordinate type");
        }

    }


}

