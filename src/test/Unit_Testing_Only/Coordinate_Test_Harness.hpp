/** 
 * @file    Coordinate_Test_Harness.hpp
 * @author  Marvin Smith
 * @date    3/25/2015
*/
#ifndef __GEOEXPLORE_TEST_COORDINATE_TEST_HARNESS_HPP__
#define __GEOEXPLORE_TEST_COORDINATE_TEST_HARNESS_HPP__

// Boost Libraries
#include <boost/filesystem.hpp>

// C++ Standard Libraries
#include <memory>

// GeoExplore Libraries
#include "../../lib/coordinate/CoordinateGeographic.hpp"
#include "../../lib/coordinate/CoordinateUTM.hpp"
#include "../../lib/core/A_Status.hpp"
#include "../../lib/core/Enumerations.hpp"

/**
 * @class Coordinate_Test_Set
*/
class Coordinate_Test_Set{

    public:

        /** 
         * @brief Constructor
         *
         * @param[in] coordinate_name Name of the coordinate.
         * @param[in] coordinate_list List of coordinates.
        */
        Coordinate_Test_Set( std::string const&                                           coordinate_name,
                             std::vector<GEO::CRD::CoordinateBase<double>::ptr_t> const&  coordinate_list );

        
        /**
         * @brief Get the Coordinate Name
         *
         * @return Coordinate Name
         */
        inline std::string Get_Coordinate_Name()const{
            return m_coordinate_name;
        }


    private:
        
        /// Coordinate Name
        std::string m_coordinate_name;

        /// Coordinate List
        std::vector<GEO::CRD::CoordinateBase<double>::ptr_t> m_coordinate_list;

}; // End of Coordinate_Test_Set Class

/**
 * @class Coordinate_Test_Harness
*/
class Coordinate_Test_Harness{

    public:

        /// Pointer Type
        typedef std::shared_ptr<Coordinate_Test_Harness> ptr_t;
        

        /**
         * @brief Initialize the Harness
         *
         * @param[in] config_pathname Path to coordinate configuration file.
         *
         * @return Status of the operation.
         */
        GEO::Status Initialize( boost::filesystem::path const& config_pathname );


        /**
         * @brief Get an instance of the test harness
         *
         * @return Instance of the Coordinate_Test_Harness
        */
        static Coordinate_Test_Harness::ptr_t Instance_Of();


    private:

        /**
         * @brief Constructor
        */
        Coordinate_Test_Harness();
        
        
        /**
         * @brief Parse the configuration file
        */
        GEO::Status Parse_Configuration_File( boost::filesystem::path const& pathname );


        /// List of Coordinates
        std::vector<Coordinate_Test_Set> m_coordinate_test_sets;

}; // End of Coordinate_Test_Harness Class


#endif
