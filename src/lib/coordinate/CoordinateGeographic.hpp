/**
 * @file    CoordinateGeographic.hpp
 * @author  Marvin Smith
 * @date    4/16/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEGEODETIC_HPP__
#define __SRC_COORDINATE_COORDINATEGEODETIC_HPP__

// C++ Standard Libraries
#include <cmath>

// GeoExplore Libraries
#include "../core/Enumerations.hpp"
#include "CoordinateBase.hpp"

namespace GEO{
namespace CRD{


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
         * @brief Constructor
         */
        CoordinateGeographic() 
          :  CoordinateBase<DATATYPE>(0, Datum::WGS84),
             m_latitude_degrees(0), 
             m_longitude_degrees(0)
        {
        }
        
        
        /**
         * @brief Constructor
         *
         * @param[in] datum Datum
        */
        CoordinateGeographic( Datum const& datum ) 
          :  CoordinateBase<DATATYPE>( 0, datum ),
             m_latitude_degrees(0),
             m_longitude_degrees(0)
        {
        }


        /**
         * @brief Constructor
         *
         * @param[in] latitude_degrees Latitude in degrees.
         * @param[in] longitude_degrees Longitude in degrees.
         * @param[in] altitude_meters Altitude in meters.
         * @param[in] datum Datum.
         */
        CoordinateGeographic( datatype const& latitude_degrees, 
                              datatype const& longitude_degrees,
                              datatype const& altitude_meters = 0,
                              Datum const& datum = Datum::WGS84 ) 
            :  CoordinateBase<DATATYPE>( 0, datum ),
               m_latitude_degrees(latitude_degrees), 
               m_longitude_degrees(longitude_degrees)
        {
        }


        /**
         * @brief Get the latitude in degrees.
         *
         * @return Latitude in degrees.
         */
        datatype latitude_degrees()const
        { 
            return m_latitude_degrees; 
        }


        /**
         * @brief Get the latitude in radians.
         *
         * @return Latitude in radians
        */
        datatype latitude_radians()const
        {
            return m_latitude_degrees * M_PI / 180.0;
        }


        /**
         * @brief Set the latitude in degrees
         *
         * @return Latitude in degrees.
         */
        datatype& latitude_degrees(){ 
            return m_latitude_degrees;
        }


        /**
         * @brief Get the longitude in degrees.
         *
         * @return Longitude in degrees.
         */
        datatype longitude_degrees()const{ 
            return m_longitude_degrees; 
        }


        /**
         * @brief Set the longitude in degrees.
         *
         * @return longitude in degrees.
         */
        datatype& longitude_degrees(){ 
            return m_longitude_degrees; 
        }

    
        /**
         * @brief Get the x coordinate.
         *
         * @return x coordinate (longitude degrees).
         */
        inline datatype x()const{
            return m_longitude_degrees;
        }


        /**
         * @brief Get the x coordinate reference.
         *
         * @return x coordinate reference (longitude degrees).
         */
        inline datatype& x(){
            return m_longitude_degrees;
        }


        /**
         * @brief Get the y coordinate value.
         *
         * @return y coordinate value (latitude degrees).
        */
        inline datatype y()const{
            return m_latitude_degrees;
        }


        /**
         * @brief Get the y coordinate reference.
         *
         * @return y coordinate reference (latitude degrees).
        */
        inline datatype& y(){
            return m_latitude_degrees;
        }


        /**
         * @brief Clone the data
         * 
         * @return Cloned coordinate.
         */
        CoordinateGeographic<DATATYPE>::ptr_t clone()const{ 
            return CoordinateGeographic<DATATYPE>::ptr_t( 
                new CoordinateGeographic<DATATYPE>(m_latitude_degrees, 
                                                   m_longitude_degrees, 
                                                   this->altitude_meters(), 
                                                   this->datum())); 
        }

        
        /**
         * @brief Return the type.
         *
         * @return Coordinate Type enum.
         */
        virtual CoordinateType Get_Type(){ 
            return CoordinateType::Geographic; 
        }


    protected:
        
        /// Latitude
        datatype m_latitude_degrees;

        /// Longitude
        datatype m_longitude_degrees;

}; /// End of CoordinateGeographic Class

/// Common Typdefs
typedef CoordinateGeographic<double>   CoordinateGeographicDouble;
typedef CoordinateGeographic<double>   CoordinateGeographic_d;

typedef CoordinateGeographic<int32_t>  CoordinateGeographicInt32;
typedef CoordinateGeographic<int32_t>  CoordinateGeographic_i32;

} /// End of CRD Namespace
} /// End of GEO Namespace

#endif
