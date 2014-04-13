/**
 * @file    CoordinateBase.hpp
 * @author  Marvin Smith
 * @date    4/12/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEBASE_HPP__
#define __SRC_COORDINATE_COORDINATEBASE_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>


namespace GEO{

/**
 * @class CoordinateBase
 *
 * This is just a simple Cartesian Coordinate for abstracting more
 * complicated designs from.
 */
template<typename DATATYPE>
class CoordinateBase{


    public:
        
        /// Typedef 
        typedef DATATYPE datatype;

        /**
         * Default Constructor
         */
        CoordinateBase() : m_data{0,0,0}, m_projection(ProjectionType::WGS84){};

        /**
         * Parameterized Constructor
         */
        CoordinateBase( const DATATYPE& x, const DATATYPE& y, const DATATYPE& z = 0, const ProjectionType projection = ProjectionType::WGS84) 
                           : m_data{x, y, z}, m_projection(projection){}


        /**
         * Get the X Value
         */
        DATATYPE x()const{ return m_data[0]; }

        /**
         * Set the X Value
         */
        DATATYPE& x(){ return m_data[0]; }

        /**
         * Get the Y Value
         */
        DATATYPE y()const{ return m_data[1]; }

        /**
         * Set the Y Value
         */
        DATATYPE& y(){ return m_data[1]; }

        /**
         * Get the Z Value
         */
        DATATYPE z()const{ return m_data[2]; }

        /**
         * Set the Z Value
         */
        DATATYPE& z(){ return m_data[2]; }


    protected:
        
        /// Coordinate Information
        DATATYPE m_data[3];
        
        /// Projection Type
        ProjectionType m_projection;
        

}; /// End of CoordinateBase class

} /// End of GEO Namespace

#endif
