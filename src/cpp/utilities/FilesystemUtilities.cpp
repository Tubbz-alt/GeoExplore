/**
 * @file    FilesystemUtilities.cpp
 * @author  Marvin Smith
 * @date    5/11/2014
*/
#include "FilesystemUtilities.hpp"

/// GeoExplore Libraries
#include <GeoExplore/core/Exceptions.hpp>

/// C++ Standard Libraries
#include <fstream>
#include <iostream>

namespace GEO{
namespace FS{

/**
 * Get the magic number from a file
*/
std::string getMagicNumber( const boost::filesystem::path& pathname ){

    // make sure the file exists
    if( boost::filesystem::exists( pathname ) == false ){
        throw GeneralException(pathname.native() + " does not exist.", __FILE__, __LINE__);
    }

    /// open the file stream
    std::ifstream fin;
    fin.open(pathname, std::ios::in | std::ios::binary );
    
    //fin.read
    fin.close();

    return output;
}

} /// End of FS Namespace
} /// End of GEO Namespace


