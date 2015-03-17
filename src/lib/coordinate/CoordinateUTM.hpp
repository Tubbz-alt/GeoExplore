/**
 * @file    CoordinateUTM.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEUTM_HPP__
#define __SRC_COORDINATE_COORDINATEUTM_HPP__

/// GeoExplore Libraries
#include "../core/Enumerations.hpp"
#include "CoordinateBase.hpp"

namespace GEO{
namespace CRD{

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
                          m_easting_meters(166021.4), 
                          m_northing_meters(0), 
                          CoordinateBase<DATATYPE>(0, Datum::WGS84){}
        
        /**
         * Parameterized Constructor
        */
        CoordinateUTM( Datum const& datum ) : 
                m_zone(31),
                m_is_northern(true),
                m_easting_meters(166021.4),
                m_northing_meters(0),
                CoordinateBase<DATATYPE>(0, datum){}

        /**
         * Parameterized Constructor
         */
        CoordinateUTM( int const&      zone,
                       bool const&     is_northern,
                       datatype const& easting_meters, 
                       datatype const& northing_meters, 
                       datatype const& altitude_meters = 0, 
                       Datum const& datum = Datum::WGS84 ) 
            : m_zone(zone),
              m_is_northern(is_northern),
              m_easting_meters(easting_meters),
              m_northing_meters(northing_meters),
              CoordinateBase<DATATYPE>(altitude_meters, datum){}
            
        /**
         * Get the zone
        */
        int zone()const{ return m_zone; }

        /**
         * Set the zone
        */
        int& zone(){ return m_zone; }

        /**
         * @brief Check if coordinate is in Northern Hemisphere
        */
        bool   Is_Northern_Hemisphere()const{ 
            return m_is_northern; 
        }
        
        
        /**
         * Set if the coordinate is in the northern hemisphere or not.
         */
        bool&  Is_Northern_Hemisphere(){ 
            return m_is_northern; 
        }


        /**
         * @brief Get the Easting
         */
        datatype easting_meters()const{ 
            return m_easting_meters; 
        }

        /**
         * Set the Easting
         */
        datatype& easting_meters(){ 
            return m_easting_meters; 
        }

        /**
         * Get the northing
         */
        datatype northing_meters()const{ 
            return m_northing_meters; 
        }

        /**
         * @brief Set the northing
         */
        datatype& northing_meters(){ 
            return m_northing_meters; 
        }

        /**
         * @brief Get the X Value
        */
        datatype x()const{
            return m_easting_meters;
        }


        /**
         * @brief Get the x reference
        */
        datatype& x(){
            return m_easting_meters;
        }


        /**
         * @brief Get the Y Value
        */
        datatype y()const{
            return m_northing_meters;
        }


        /**
         * @brief Get the y reference
        */
        datatype& y(){
            return m_northing_meters;
        }


        /**
         * @brief Clone the data
         */
        CoordinateUTM<DATATYPE>::ptr_t clone()const{ 
            return CoordinateUTM<DATATYPE>::ptr_t( 
                    new CoordinateUTM<DATATYPE>(
                                m_zone,
                                m_is_northern,
                                m_easting_meters, 
                                m_northing_meters, 
                                this->altitude_meters(), 
                                this->datum())); 
            }
        

        /**
         * @brief Addition Operator
        */
        CoordinateUTM<DATATYPE> operator + ( const CoordinateUTM<DATATYPE>& rhs )const{
            return CoordinateUTM<DATATYPE>( m_zone,
                                            m_is_northern,
                                            m_easting_meters + rhs.m_easting_meters,
                                            m_northing_meters + rhs.m_northing_meters,
                                            this->m_altitude_meters + rhs.altitude_meters(),
                                            this->m_datum );
        }


        /**
         * @brief Return the type
        */
        virtual CoordinateType type(){ 
            return CoordinateType::UTM; 
        }

    private:
        
        /// Zone
        int      m_zone;

        /// Easting
        datatype m_easting_meters;

        /// Northing
        datatype m_northing_meters;
        
        /// Hemisphere
        bool m_is_northern;

}; /// End of CoordinateUTM Class

/// Common Typedefs
typedef CoordinateUTM<double> CoordinateUTMDouble;
typedef CoordinateUTM<double> CoordinateUTM_d;


} /// End of CRD Namespace
} /// End of GEO Namespace


#endif
