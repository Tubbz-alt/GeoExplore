/**
 * @file    CoordinateGeodetic.hpp
 * @author  Marvin Smith
 * @date    4/16/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEGEODETIC_HPP__
#define __SRC_COORDINATE_COORDINATEGEODETIC_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>
#include <GeoExplore/coordinate/CoordinateBase.hpp>

/// Boost
#include <boost/shared_ptr.hpp>

namespace GEO{


/**
 * @class CoordinateGeodetic
 */
template<typename DATATYPE>
class CoordinateGeodetic : public CoordinateBase<DATATYPE>{

    public:
        
        /// Typedef 
        typedef DATATYPE datatype;
        
        /// Pointer type
        typedef boost::shared_ptr<CoordinateGeodetic<DATATYPE> > ptr_t;

        /**
         * Default Constructor
         */
        CoordinateGeodetic() : m_latitude(0), 
                               m_longitude(0), 
                               CoordinateBase<DATATYPE>(0, Datum::WGS84){}

        /**
         * Get the latitude
         */
        datatype latitude()const{ return m_latitude; }

        /**
         * Set the latitude
         */
        datatype& latitude(){ return m_latitude; }

        /**
         * Get the longitude
         */
        datatype longitude()const{ return m_longitude; }

        /**
         * Set the longitude
         */
        datatype& longitude(){ return m_longitude; }


    protected:
        
        /// Latitude
        datatype m_latitude;

        /// Longitude
        datatype m_longitude;

}; /// End of CoordinateGeodetic Class

/// Common Typdefs
typedef CoordinateGeodetic<double> CoordinateGeodeticDouble;
typedef CoordinateGeodetic<double> CoordinateGeodetic_d;

} /// End of GEO Namespace

#endif
