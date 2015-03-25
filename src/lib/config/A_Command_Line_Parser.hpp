/**
 * @file    A_Command_Line_Parser.hpp
 * @author  Marvin Smith
 * @date    3/22/2015
*/
#ifndef __GEOEXPLORE_LIB_CONFIG_A_COMMAND_LINE_PARSER_HPP__
#define __GEOEXPLORE_LIB_CONFIG_A_COMMAND_LINE_PARSER_HPP__

// C++ Standard Libraries
#include <cinttypes>
#include <string>
#include <vector>


namespace GEO{
namespace CONFIG{


/**
 * @class A_Command_Line_Parser
 * 
 * @brief Class for parsing command-line options and flags.
*/
class A_Command_Line_Parser{

    public:
        
        /**
         * @brief Constructor given arguments.
         *
         * @param[in] argc Number of Command-line args
         * @param[in] argv List of command-line args.
        */
        A_Command_Line_Parser( int argc, char* argv[] );

        
        /**
         * @brief Get the application name (argv[0]).
         *
         * @return Application name
        */
        inline std::string Get_Application_Name()const{
            return m_application_name;
        }


        /**
         * @brief Check if flag exists
         * 
         * @param[in] flag Flag to test.
         *
         * @return True if exists, false otherwise.
        */
        bool Check_If_Flag_Exists( const std::string& flag );
    

    private:
        
        /// Application Name
        std::string m_application_name;

        /// Argument List
        std::vector<std::string> m_argument_list;

        /// Reference List
        std::vector<int> m_reference_list;

}; // End of A_Command_Line_Parser Class


} // End of CONFIG Namespace
} // End of GEO Namespace

#endif
