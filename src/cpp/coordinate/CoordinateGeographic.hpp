/**
 * @file    CoordinateGeographic.hpp
 * @author  Marvin Smith
 * @date    4/16/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEGEODETIC_HPP__
#define __SRC_COORDINATE_COORDINATEGEODETIC_HPP__

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>
#include <GeoExplore/coordinate/CoordinateBase.hpp>

namespace GEO{


/**
 * @class CoordinateGeographic
 */
template<typename DATATYPE>
class CoordinateGeographic : public CoordinateBase<DATATYPE>{

    public:
        
        /// Typedef 
        typedef DATATYPE datatype;
        
        /// Pointer type
        typedef std::shared_ptr<CoordinateGeographic<DATATYPE> > ptr_t;

        /**
         * Default Constructor
         */
        CoordinateGeographic() : m_latitude(0), 
                               m_longitude(0), 
                               CoordinateBase<DATATYPE>(0, Datum::WGS84){}
        
        /**
         * Parameterized Constructor
         *
         * @param[in] datum Datum
        */
        CoordinateGeographic( Datum const& datum ) : 
                                m_latitude(0),
                                m_longitude(0),
                                CoordinateBase<DATATYPE>(0, datum){}

        /**
         * Parameterized Constructor
         */
        CoordinateGeographic( datatype const& latitude, 
                            datatype const& longitude,
                            datatype const& altitude = 0,
                            Datum const& datum = Datum::WGS84 ) : 
                                
                                m_latitude(latitude), 
                                m_longitude(longitude),
                                CoordinateBase<datatype>(altitude, datum){}

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
    
        /**
         * Clone the data
         */
        CoordinateGeographic<DATATYPE>::ptr_t clone()const{ 
                    return CoordinateGeographic<DATATYPE>::ptr_t( 
                            new CoordinateGeographic<DATATYPE>(m_latitude, m_longitude, this->altitude(), this->datum())); 
                    }
        
        virtual CoordinateType type(){ return CoordinateType::Geographic; }


    protected:
        
        /// Latitude
        datatype m_latitude;

        /// Longitude
        datatype m_longitude;

}; /// End of CoordinateGeographic Class

/// Common Typdefs
typedef CoordinateGeographic<double>   CoordinateGeographicDouble;
typedef CoordinateGeographic<double>   CoordinateGeographic_d;

typedef CoordinateGeographic<int32_t>  CoordinateGeographicInt32;
typedef CoordinateGeographic<int32_t>  CoordinateGeographic_i32;

} /// End of GEO Namespace

#endif
