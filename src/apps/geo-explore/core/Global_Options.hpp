#ifndef __OPTIONS_HPP__
#define __OPTIONS_HPP__

// C++ Standard Libraries
#include <string>

// Qt Libraries
#include <QDebug>

namespace GEO{
namespace GUI{

/**
 * @class Options
*/
class Global_Options{
    
    public:
        
        /**
         * @brief Get Instance of the Options
        */
        static Global_Options& Get_Instance();
        
        /**
         * @brief Load Configuration 
        */
        void Load_Configuration( int argc, 
                                 char* argv[],
                                 std::string& filename );

    private:

        /**
         * @brief Default Constructor
        */
        Global_Options();

        /**
         * @brief Copy-Constructor
        */
        Global_Options( const Global_Options& rhs ) = delete;

        /**
         * @brief Destructor
        */
        ~Global_Options();


}; // End of Options Class

} /// End of GUI Namespace
} /// End of GEO Namespace

#endif
