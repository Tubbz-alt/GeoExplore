/**
 * @file    CoordinateBase.hpp
 * @author  Marvin Smith
 * @date    4/12/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEBASE_HPP__
#define __SRC_COORDINATE_COORDINATEBASE_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>

/// Boost
#include <boost/shared_ptr.hpp>

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

        /// Pointer type
        typedef boost::shared_ptr<CoordinateBase<DATATYPE> > ptr_t;

        /**
         * Default Constructor
         */
        CoordinateBase() : m_altitude(0), m_coordinateSystem(CoordinateSystem::WGS84){};

        /**
         * Parameterized Constructor Given only the CoordinateSystem and altiutude
         */
        CoordinateBase( const DATATYPE& altitude, const CoordinateSystem& coordinateSystem ) : m_altitude(altitude), m_coordinateSystem(coordinateSystem){}

        /**
         * Get the altitude
         */
        DATATYPE altitude()const{ return m_altitude; }

        /**
         * Set the altitude
         */
        DATATYPE& altitude(){ return m_altitude; }
        
        /**
         * Get the coordinate system
         */
        CoordinateSystem coordinateSystem()const{ return m_coordinateSystem; }

        /**
         * Set the coordinate system
         */
        CoordinateSystem& coordinateSystem(){ return m_coordinateSystem; }


    protected:
        
        /// Coordinate Information
        DATATYPE m_altitude;
        
        /// Projection Type
        CoordinateSystem m_coordinateSystem;
        

}; /// End of CoordinateBase class

/// Common Typdefs
typedef CoordinateBase<double> CoordinateBaseDouble;
typedef CoordinateBase<double> CoordinateBase_d;


} /// End of GEO Namespace

#endif
