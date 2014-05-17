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

    // get the extension
    std::string ext = string_toLower(pathname.extension().native());
    
    // JPEG 2000
    if( ext == ".jp2" )
        return FileType::JPEG2000;

    // JPEG
    if( ext == ".jpg" || ext == ".jpeg" )
        return FileType::JPEG;
    
    // PNG
    if( ext == ".png" )
        return FileType::PNG;

    // NITF
    if( ext == ".ntf" || ext == ".nitf" )
        return FileType::NITF;

    // DTED
    if( ext == ".dt0" || ext == ".dt1" || ext == ".dt2" )
        return FileType::DTED;


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


