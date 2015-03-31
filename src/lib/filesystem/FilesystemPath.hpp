/**
 * @file    FilesystemPath.hpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#ifndef __GEOEXPLORE_LIB_FILESYSTEM_FILESYSTEMPATH_HPP__
#define __GEOEXPLORE_LIB_FILESYSTEM_FILESYSTEMPATH_HPP__

// Boost Libraries
#include <boost/filesystem.hpp>

// C++ Standard Libraries
#include <string>

// GeoExplore Libraries
#include "PathFormatType.hpp"

namespace GEO{
namespace FS{

/**
 * @class FilesystemPath
 *
 * @brief Provides filesystem utilities without the Boost Filesystem Overhead.
*/
class FilesystemPath{

    public:
        
        /**
         * @brief Constructor
        */
        FilesystemPath();

        /**
         * @brief Constructor given path.
        */
        FilesystemPath( const char* pathname );


        /**
         * @brief Constructor given path.
        */
        FilesystemPath( std::string const& pathname );


        /** 
         * @brief Constructor given boost path.
         */
        FilesystemPath( boost::filesystem::path const& pathname );
        

        /** 
         * @brief Assignment Operator
         *
         * @param[in] pathname String pathname.
         *
         * @return Path object.
        */
        FilesystemPath& operator = ( FilesystemPath const& pathname );
        

        /**
         * @brief Equivalent Operator
         *
         * @param[in] other Pathname to test.
         *
         * @return True if equivalent, false otherwise.
        */
        bool operator == ( const FilesystemPath& other )const;


        /**
         * @brief Check if Path Exists.
         *
         * @return True if it exists, false otherwise.
        */
        bool Exists()const;


        /**
         * @brief Check if Regular File.
         *
         * @return True if regular file. False otherwise.
        */
        bool Is_Regular_File()const;


        /**
         * @brief Check if Directory.
         *
         * @brief True if directory. False otherwise.
        */
        bool Is_Directory()const;


        /**
         * @brief Get the extension.
         *
         * @return Extension.
        */
        FilesystemPath Get_Extension()const;

        
        /**
         * @brief Get the parent path.
         *
         * @return Parent Path.
        */
        FilesystemPath Get_Parent()const;


        /**
         * @brief Get Basename
         *
         * @return Basename
        */
        FilesystemPath Get_Basename()const;
        

        /**
         * @brief Get Canonical Path
         * 
         * @return Canonical Path
        */
        FilesystemPath Get_Canonical()const;


        /**
         * @brief Get the Relative Path.
         *
         * @return Relative path.
        */
        FilesystemPath Get_Relative()const;
        

        /**
         * @brief Append another path to the current path.
         *
         * For example, FilesystemPath("foo").Append("bar") will product "foo/bar".
         *
         * @param[in] other Path to append.
         *
         * @return Appended Path.
        */
        FilesystemPath Append( FilesystemPath const& other )const;

        /**
         * @brief Get Contents of Directory. Non-recursive and searches everything.
         *
         * @param[in] pattern Regex pattern to apply in Posix format.
         *
         * @return List of items found.
        */
        std::vector<FilesystemPath> Get_Contents( PathFormatType const& path_format )const;


        /**
         * @brief Get Contents of Directory.
         *
         * @param[in] pattern Regex pattern to apply in Posix format.
         * @param[in] recursive Use a recursive search.
         *
         * @return List of items found.
        */
        std::vector<FilesystemPath> Get_Contents( std::string const& pattern        = ".*",
                                                  bool const& recursive             = false,
                                                  PathFormatType const& path_format = PathFormatType::RELATIVE )const;

        /**
         * @brief Print to a string format.
         * 
         * @return String format.
        */
        std::string ToString()const;
        
        
        /**
         * @brief Get the Current Path
         *
         * @return Current Path
        */
        static FilesystemPath  Get_Current_Path();


    private:
        
        /// Internal Path
        boost::filesystem::path  m_pathname;

}; // End of FilesystemPath class.


} // End of FS  Namespace
} // End of GEO Namespace

#endif
