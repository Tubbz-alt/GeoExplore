/**
 * @file    CoordinateUTM.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEUTM_HPP__
#define __SRC_COORDINATE_COORDINATEUTM_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>
#include <GeoExplore/coordinate/CoordinateBase.hpp>

namespace GEO{

/**
 * @class CoordinateUTM
 */
template<typename DATATYPE>
class CoordinateUTM : public CoordinateBase<DATATYPE>{

    public:
        
        /// Typedef 
        typedef DATATYPE datatype;
        
        /// Pointer type
        typedef boost::shared_ptr<CoordinateUTM<DATATYPE> > ptr_t;

        /**
         * Default Constructor
         */
        CoordinateUTM() : m_easting(0), 
                          m_northing(0), 
                          CoordinateBase<DATATYPE>(0, Datum::WGS84){}

    /**
     * Get the Easting
     */
    datatype easting()const{ return m_easting; }

    /**
     * Set the Easting
     */
    datatype& easting(){ return m_easting; }

    /**
     * Get the northing
     */
    datatype northing()const{ return m_northing; }

    /**
     * Set the northing
     */
    datatype& northing(){ return m_northing; }

    private:

        /// Easting
        datatype m_easting;

        /// Northing
        datatype m_northing;


}; /// End of CoordinateUTM Class

/// Common Typedefs
typedef CoordinateUTM<double> CoordinateUTMDouble;
typedef CoordinateUTM<double> CoordinateUTM_d;


} /// End of GEO Namespace


#endif
