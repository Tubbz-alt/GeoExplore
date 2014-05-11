/**
 * @file    Exceptions.hpp
 * @author  Marvin Smith
 * @date    5/8/2014
*/
#ifndef __SRC_CPP_CORE_EXCEPTIONS_HPP__
#define __SRC_CPP_CORE_EXCEPTIONS_HPP__

/// C++ Standard Libraries
#include <exception>
#include <string>

/// GeoExplore Libraries
#include <GeoExplore/utilities/StringUtilities.hpp>

namespace GEO{

/**
 * @class NotImplementedException
 *
 * Error which is thrown when a function is not implemented.
*/
class NotImplementedException : public std::exception {
    
    public:
        
        /**
         * Constructor
        */
        NotImplementedException( const std::string& function_name, 
                                 const std::string& filename, 
                                 const int& line_number );

        /**
         * Message
        */
        virtual const char* what()const throw(){
            return std::string(m_module + std::string(" does not exist.  File: ") + m_filename + std::string(", Line: ") + num2str(m_lineNumber)).c_str();
        }

    private:
        
        /// Function Name
        std::string m_module;

        /// Filename
        std::string m_filename;

        /// Line Number
        int m_lineNumber;


}; /// End of NotImplementedException

/**
 * @class MemoryResourceNotInitializedException
 * This is thrown when a resource is access that has not been allocated.
*/
class MemoryResourceNotInitializedException : public std::exception {

    public:
        
        /**
         * Constructor
        */
        MemoryResourceNotInitializedException( const std::string& filename, const int& line_number );

        /**
         * Message
        */
        virtual const char* what()const throw(){
            return std::string(std::string("error: MemoryResource accessed without being initialized. File: ") +
                               std::string(", Line: ") + num2str(m_lineNumber)).c_str();
        }
    
    private:
        
        /// Filename
        std::string m_filename;

        /// Line Number
        int m_lineNumber;
}; /// End of MemoryResourceNotInitializedException

} /// End of GEO Namespace

#endif
