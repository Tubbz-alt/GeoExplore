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

/// Boost C++ Libraries
#include <boost/filesystem.hpp>


namespace GEO{
namespace FS{

/**
 * Get the file type
*/
FileType getFileType( const boost::filesystem::path& pathname ){
    
    // parse out the magic number
    std::string magic_number = getMagicNumber( pathname );


    // otherwise return unknown type
    return FileType::UNKNOWN;
}


/**
 * Get the magic number from a file
*/
std::string getMagicNumber( const boost::filesystem::path& pathname ){

    // make sure the file exists
    if( boost::filesystem::exists( pathname ) == false ){
        throw GeneralException(pathname.native() + " does not exist.","FilesystemUtilities.cpp", __LINE__);
    }
    
    /// open the file stream
    std::string output;
    std::ifstream fin;
    fin.open(pathname.c_str());
    
    char tempChar;
    fin >> tempChar;

    for( int i=0; i<11 && !fin.eof(); i++ ){

        output.push_back(tempChar);
        fin >> tempChar;

    }

    //fin.read
    fin.close();


    return output;
}

} /// End of FS Namespace
} /// End of GEO Namespace


