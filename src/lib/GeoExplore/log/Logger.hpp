/**
 * @file    Logger.hpp
 * @author  Marvin Smith
 * @date    3/30/2015
*/
#ifndef __GEOEXPLORE_LIB_LOG_LOGGER_HPP__
#define __GEOEXPLORE_LIB_LOG_LOGGER_HPP__

// Boost Libraries
#include <boost/log/trivial.hpp>

// C++ Standard Libraries
#include <memory>

namespace GEO{
namespace LOG{

/**
 * @class Logger
 */
class Logger{

    public:

        /// Pointer Type
        typedef std::shared_ptr<Logger> ptr_t;
    

    private:
        


}; /// End of Logger Class

} // End of LOG Namespace
} // End of GEO Namespace

#endif
