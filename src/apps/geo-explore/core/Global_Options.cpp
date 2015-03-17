#include "Global_Options.hpp"

// Boost Filesystem
#include <boost/filesystem.hpp>

namespace bf=boost::filesystem;

namespace GEO{
namespace GUI{

/**
 * Default Constructor
*/
Global_Options::Global_Options()
{

}

/**
 * Destructor
*/
Global_Options::~Global_Options()
{

}

/**
 * Get Instance of the Options
*/
Global_Options& Global_Options::Get_Instance(){

    // Create Static Instance
    static Global_Options instance;

    // Return
    return instance;
}


/**
 * Load Configuration 
 */
void Global_Options::Load_Configuration( int argc, 
                                         char* argv[],
                                         std::string& filename )
{

    // Convert filename to boost path
    bf::path pathname(filename);
    
    // Make sure path exists
    if( bf::exists( pathname ) == true ){
        qDebug() << "Loading configuration file.";
    } 
    else {
        qDebug() << "Configuration file does not exist.";
    }

}

} /// End of GUI Namespace
} /// End of GEO Namespace

