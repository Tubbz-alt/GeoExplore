/**
 * @file    CoordinateUTM.hpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEUTM_HPP__
#define __SRC_COORDINATE_COORDINATEUTM_HPP__

// GeoExplore Libraries
#include "../core/Enumerations.hpp"
#include "CoordinateBase.hpp"

// C++ Standard Libraries
#include <cmath>


namespace GEO{
namespace CRD{

/**
 * @class CoordinateUTM
 *
 * @brief UTM Coordinate Class.
 */
template<typename DATATYPE>
class CoordinateUTM : public CoordinateBase<DATATYPE>{

    public:
        
        /// Typedef 
        typedef DATATYPE datatype;
        
        /// Pointer type
        typedef std::shared_ptr<CoordinateUTM<DATATYPE> > ptr_t;

        /**
         * @brief Constructor
         */
        CoordinateUTM() 
          :  CoordinateBase<DATATYPE>(0, Datum::WGS84),
             m_zone(31),
             m_is_northern(true),
             m_easting_meters((DATATYPE)166021.4), 
             m_northing_meters(0) 
        {
        }

        
        /**
         * @brief  Constructor
         *
         * @param[in] datum Datum to use.
        */
        CoordinateUTM( Datum const& datum ) 
          :  CoordinateBase<DATATYPE>(0, datum), 
             m_zone(31),
             m_is_northern(true),
             m_easting_meters(166021.4),
             m_northing_meters(0)
        {
        }


        /**
         * @brief Constructor
         *
         * @param[in] zone UTM Zone to use.
         * @param[in] is_northern True if in northern hemisphere.
         * @param[in] easting_meters Easting (x) value in meters.
         * @param[in] northing_meters Northing (y) value in meters.
         * @param[in] altitude_meters Altitude (z) value in meters.
         * @param[in] datum Datum of coordinate to use.
         */
        CoordinateUTM( int const&      zone,
                       bool const&     is_northern,
                       datatype const& easting_meters, 
                       datatype const& northing_meters, 
                       datatype const& altitude_meters = 0, 
                       Datum const& datum = Datum::WGS84 ) 
            : CoordinateBase<DATATYPE>(altitude_meters, datum ),
              m_zone(zone),
              m_is_northern(is_northern),
              m_easting_meters(easting_meters),
              m_northing_meters(northing_meters)
        {
        }
         

        /**
         * @brief Get the utm zone.
         * 
         * @return UTM Zone.
        */
        int zone()const{ 
            return m_zone; 
        }


        /**
         * @brief Set the utm zone.
         *
         * @return UTM Zone Reference.
        */
        int& zone(){ 
            return m_zone; 
        }


        /**
         * @brief Check if coordinate is in Northern Hemisphere.
         *
         * @return True if in the northern hemisphere, false if in southern.
        */
        bool   Is_Northern_Hemisphere()const{ 
            return m_is_northern; 
        }
        
        
        /**
         * @brief Set if the coordinate is in the northern hemisphere or not.
         *
         * @return Northern hemisphere bool reference.
         */
        bool&  Is_Northern_Hemisphere(){ 
            return m_is_northern; 
        }


        /**
         * @brief Get the Easting in Meters.
         *
         * @return Easting in meters.
         */
        datatype easting_meters()const{ 
            return m_easting_meters; 
        }


        /**
         * @brief Set the Easting in Meters.
         *
         * @return Easting in meters.
         */
        datatype& easting_meters(){ 
            return m_easting_meters; 
        }


        /**
         * @brief Get the northing in meters.
         *
         * @return Northing in meters.
         */
        datatype northing_meters()const{ 
            return m_northing_meters; 
        }


        /**
         * @brief Set the northing in meters.
         *
         * @return Northing in meters.
         */
        datatype& northing_meters(){ 
            return m_northing_meters; 
        }


        /**
         * @brief Get the X Value
         *
         * @return X Value.
        */
        datatype x()const{
            return m_easting_meters;
        }


        /**
         * @brief Get the x reference
         *
         * @return X reference.
        */
        datatype& x(){
            return m_easting_meters;
        }


        /**
         * @brief Get the Y Value.
         *
         * @return Y value.
        */
        datatype y()const{
            return m_northing_meters;
        }


        /**
         * @brief Get the y reference.
         * 
         * @return Y reference value.
        */
        datatype& y(){
            return m_northing_meters;
        }


        /**
         * @brief Mag2 Operator
         *
         * @return { @f{ $x^2 + y^2 + z^2$} }
        */
        DATATYPE Mag2()const{
            return ((easting_meters()  * easting_meters()  ) + 
                    (northing_meters() * northing_meters() ) +
                    (this->altitude_meters() * this->altitude_meters() ));
        }


        /**
         * @brief Mag Operator
         *
         * @return Sqrt of Mag2
        */
        DATATYPE Mag()const{
            return std::sqrt(Mag2());
        }


        /**
         * @brief Clone the data
         *
         * Return coordinate clone.
         */
        CoordinateUTM<DATATYPE>::ptr_t Clone()const{ 
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
         * @brief Addition Operator.
         *
         * Note that the zone and hemisphere are ignored.  The first coordinate (this) is used.
         *
         * @param[in] rhs Coordinate to add to.
         *
         * @return Sum of this coordinate and the other coordinate.
        */
        CoordinateUTM<DATATYPE> operator + ( const CoordinateUTM<DATATYPE>& rhs )const
        {
            return CoordinateUTM<DATATYPE>( m_zone,
                                            m_is_northern,
                                            m_easting_meters + rhs.m_easting_meters,
                                            m_northing_meters + rhs.m_northing_meters,
                                            this->m_altitude_meters + rhs.altitude_meters(),
                                            this->m_datum );
        }
        

        /**
         * @brief Subtraction Operator.
         *
         * Note that the zone and hemisphere are ignored.  The first coordinate (this) is used.
         *
         * @param[in] rhs Other coordinate to subtract.
         *
         * @return difference between this coordinate an the other.
        */
        CoordinateUTM<DATATYPE> operator - ( const CoordinateUTM<DATATYPE>& rhs )const
        {
            return CoordinateUTM<DATATYPE>( m_zone,
                                            m_is_northern,
                                            easting_meters()  - rhs.easting_meters(),
                                            northing_meters() - rhs.northing_meters(),
                                            this->altitude_meters() - rhs.altitude_meters(),
                                            this->datum()   );
        }


        /**
         * @brief Compare the distance between 2 coordinates
         *
         * @param[in] coordinate1 First Coordinate to Compare.
         * @param[in] coordinate2 Second Coordinate to Compare.
         *
         * @return Distance in meters.  -1 if there was an issue.
        */
        static double Distance( CoordinateUTM<DATATYPE> const& coordinate1,
                                CoordinateUTM<DATATYPE> const& coordinate2 ){
            
            // Check zone and hemisphere
            if( coordinate1.zone() != coordinate2.zone() )
            { 
                return -1; 
            }
            if( coordinate1.Is_Northern_Hemisphere() != coordinate2.Is_Northern_Hemisphere() )
            { 
                return -1;
            }

            // Subtrace Points
            CoordinateUTM<DATATYPE> diff_coordinate = coordinate1 - coordinate2;

            // Do the distance formula
            return diff_coordinate.Mag();
        }
        

        /**
         * @brief Return the type
        */
        virtual CoordinateType Get_Type(){ 
            return CoordinateType::UTM; 
        }

    private:
        
        /// Zone
        int      m_zone;
        
        /// Hemisphere
        bool m_is_northern;

        /// Easting
        datatype m_easting_meters;

        /// Northing
        datatype m_northing_meters;
        

}; /// End of CoordinateUTM Class

/// Common Typedefs
typedef CoordinateUTM<double> CoordinateUTMDouble;
typedef CoordinateUTM<double> CoordinateUTM_d;


} /// End of CRD Namespace
} /// End of GEO Namespace


#endif
