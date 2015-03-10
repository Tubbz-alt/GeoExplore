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
        typedef std::shared_ptr<CoordinateUTM<DATATYPE> > ptr_t;

        /**
         * Default Constructor
         */
        CoordinateUTM() : m_zone(31),
                          m_is_northern(true),
                          m_easting(166021.4), 
                          m_northing(0), 
                          CoordinateBase<DATATYPE>(0, Datum::WGS84){}
        
        /**
         * Parameterized Constructor
        */
        CoordinateUTM( Datum const& datum ) : 
                m_zone(31),
                m_is_northern(true),
                m_easting(166021.4),
                m_northing(0),
                CoordinateBase<DATATYPE>(0, datum){}

        /**
         * Parameterized Constructor
         */
        CoordinateUTM( int const&      zone,
                       bool const&     is_northern,
                       datatype const& easting, 
                       datatype const& northing, 
                       datatype const& altitude = 0, 
                       Datum const& datum = Datum::WGS84 ) : 
                                m_zone(zone),
                                m_is_northern(is_northern),
                                m_easting(easting),
                                m_northing(northing),
                                CoordinateBase<DATATYPE>(altitude, datum){}
            
        /**
         * Get the zone
        */
        int zone()const{ return m_zone; }

        /**
         * Set the zone
        */
        int& zone(){ return m_zone; }

        /**
         * Is Northern
        */
        bool   Is_Northern_Hemisphere()const{ return m_is_northern; }
        bool&  Is_Northern_Hemisphere(){ return m_is_northern; }


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

        /**
         * Clone the data
         */
        CoordinateUTM<DATATYPE>::ptr_t clone()const{ 
            return CoordinateUTM<DATATYPE>::ptr_t( 
                    new CoordinateUTM<DATATYPE>(
                                m_zone,
                                m_easting, 
                                m_northing, 
                                this->altitude(), 
                                this->datum())); 
            }

        virtual CoordinateType type(){ return CoordinateType::UTM; }

    private:
        
        /// Zone
        int      m_zone;

        /// Easting
        datatype m_easting;

        /// Northing
        datatype m_northing;
        
        /// Hemisphere
        bool m_is_northern;

}; /// End of CoordinateUTM Class

/// Common Typedefs
typedef CoordinateUTM<double> CoordinateUTMDouble;
typedef CoordinateUTM<double> CoordinateUTM_d;


} /// End of GEO Namespace


#endif
