/**
 * @file    FilesystemPath.cpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#include "FilesystemPath.hpp"

// Boost Regex
#include <boost/regex.hpp>

// C++ Standard Libraries
#include <iostream>

namespace GEO{
namespace FS{

/************************************************/
/*                  Constructor                 */
/************************************************/
FilesystemPath::FilesystemPath()
  : m_pathname()
{
}


/************************************************/
/*                  Constructor                 */
/************************************************/
FilesystemPath::FilesystemPath( const char* pathname )
  : m_pathname(pathname)
{
}

/************************************************/
/*                  Constructor                 */
/************************************************/
FilesystemPath::FilesystemPath( std::string const& pathname )
  : m_pathname(pathname)
{
}

/************************************************/
/*                  Constructor                 */
/************************************************/
FilesystemPath::FilesystemPath( boost::filesystem::path const& pathname )
  : m_pathname(pathname.native())
{
}


/********************************************/
/*           Assignment Operator            */
/********************************************/
FilesystemPath& FilesystemPath::operator = ( FilesystemPath const& pathname )
{
    // Set the path
    m_pathname = pathname.m_pathname;

    // return this
    return (*this);
}

/********************************************/
/*                 Append Path              */
/********************************************/
FilesystemPath  FilesystemPath::Append( FilesystemPath const& other )const{
    boost::filesystem::path pathname = m_pathname;
    return FilesystemPath(pathname /= other.m_pathname);
}

/*******************************************************/
/*                 Less-Than Operator                  */
/*******************************************************/
bool FilesystemPath::operator < (FilesystemPath const& other) const{
    return (m_pathname.native() < other.m_pathname.native());
}

/*******************************************************/
/*                Equivalent Operator                  */
/*******************************************************/
bool FilesystemPath::operator == ( FilesystemPath const& other )const{

    // Check if the names are the same
    if( m_pathname == other.m_pathname ){
        return true;
    }

    // If the files exist, then call canonical
    if( Exists() == true && other.Exists() == true ){
        return( Get_Canonical().ToString() == other.Get_Canonical().ToString() );
    }

    // Otherwise, return false
    return false;
}


/*******************************************************/
/*                Check if file exists                 */
/*******************************************************/
bool FilesystemPath::Exists()const{
    return (boost::filesystem::exists(m_pathname));
}


/*******************************************************/
/*                Check if path is a file              */
/*******************************************************/
bool FilesystemPath::Is_Regular_File()const{
    return (boost::filesystem::is_regular_file(m_pathname));
}


/*******************************************************/
/*             Check if path is a directory             */
/*******************************************************/
bool FilesystemPath::Is_Directory()const{
    return (boost::filesystem::is_directory(m_pathname));
}


/*****************************************/
/*           Get the Extension           */
/*****************************************/
FilesystemPath FilesystemPath::Get_Extension()const{
    return FilesystemPath(m_pathname.extension());
}

/*****************************************/
/*           Get the Basename            */
/*****************************************/
FilesystemPath FilesystemPath::Get_Basename()const{
    return FilesystemPath(m_pathname.filename());
}

/********************************************/
/*          Get the Canonical Name          */
/********************************************/
FilesystemPath FilesystemPath::Get_Canonical()const{
    
    // Do not call canonical if the file does not exist.
    if( Exists() == false ){ return FilesystemPath(); }

    return FilesystemPath( boost::filesystem::canonical(m_pathname));
}

/******************************************/
/*          Get the Relative Path         */
/******************************************/
FilesystemPath FilesystemPath::Get_Relative()const{
    return FilesystemPath( m_pathname.relative_path() );
}

/****************************************/
/*          Get the Parent Path         */
/****************************************/
FilesystemPath FilesystemPath::Get_Parent()const{
    return FilesystemPath( m_pathname.parent_path() );
}

/*************************************************/
/*       Get the contents of the directory       */
/*************************************************/
std::vector<FilesystemPath> FilesystemPath::Get_Contents( PathFormatType const& path_format )const
{
    return Get_Contents( ".*", false, path_format );
}

/*************************************************/
/*       Get the contents of the directory       */
/*************************************************/
std::vector<FilesystemPath> FilesystemPath::Get_Contents( std::string const& pattern,
                                                          bool const& recursive_search,
                                                          PathFormatType const& path_format )const
{

    // Create output list
    std::vector<FilesystemPath> output;

    // Make sure we exist and are a directory
    if( Exists() == false ){
        return output;
    }
    if( Is_Directory() == false ){
        return output;
    }
    boost::regex rpattern(pattern);

    // Iterate over the directory
    boost::cmatch what;
    if( recursive_search == true ){
    
        boost::filesystem::recursive_directory_iterator rdit(m_pathname);
        for(; rdit != boost::filesystem::recursive_directory_iterator(); rdit++ ){

            // Check file path
            if( boost::regex_match( rdit->path().c_str(), what, rpattern ) == true){
                if( path_format == PathFormatType::ABSOLUTE ){
                    output.push_back(FilesystemPath(rdit->path()));
                }
                else{
                    output.push_back(FilesystemPath(rdit->path()).Get_Basename());
                }
            }

        }


    }
    else{

        boost::filesystem::directory_iterator dit(m_pathname);
        for(; dit != boost::filesystem::directory_iterator(); dit++ )
        {
            // Check file path
            if( boost::regex_match( dit->path().c_str(), what, rpattern ) == true){
                if( path_format == PathFormatType::ABSOLUTE ){
                    output.push_back(FilesystemPath(dit->path()));
                }
                else{
                    output.push_back(FilesystemPath(dit->path()).Get_Basename());
                }
            }
        }
    }

    // Sort the list
    std::sort( output.begin(), output.end() );

    return output;
}

/****************************************/
/*            Print to String           */
/****************************************/
std::string FilesystemPath::ToString()const{
    return m_pathname.native();
}

/*******************************************/
/*           Get the Current Path          */
/*******************************************/
FilesystemPath FilesystemPath::Get_Current_Path()
{
    return FilesystemPath(boost::filesystem::current_path());
}



} // End of FS  Namespace
} // End of GEO Namespace

