/**
 * @file    CoordinateBase.hpp
 * @author  Marvin Smith
 * @date    4/12/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEBASE_HPP__
#define __SRC_COORDINATE_COORDINATEBASE_HPP__

/// GeoExplore Libraries
#include "../core/Enumerations.hpp"

// C++ Standard Libraries
#include <memory>

namespace GEO{
namespace CRD{

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
        typedef std::shared_ptr<CoordinateBase<DATATYPE> > ptr_t;
    
        
        /**
         * @brief Constructor
         */
        CoordinateBase() 
            : m_altitude_meters(0), 
              m_datum(Datum::WGS84){};

        /**
         * @brief Constructor Given only the Datum and altiutude
         */
        CoordinateBase( const DATATYPE& altitude_meters, 
                        const Datum& datum ) 
            : m_altitude_meters(altitude_meters), 
              m_datum(datum)
        {
        }
       

        /**
         * @brief Get the altitude in meters.
         *
         * @return Altitude in meters.
         */
        inline DATATYPE altitude_meters()const{ 
            return m_altitude_meters; 
        }


        /**
         * @brief Set the altitude in meters.
         *
         * @return Altitude reference in meters. 
         */
        inline DATATYPE& altitude_meters(){ 
            return m_altitude_meters; 
        }
        

        /**
         * @brief Get the coordinate system datum.
         *
         * @return Coordinate system datum.
         */
        inline Datum datum()const{
            return m_datum; 
        }


        /**
         * @brief Set the coordinate system datum.
         *
         * @return Datum reference.
         */
        inline Datum& datum(){ 
            return m_datum; 
        }

        
        /**
         * @brief Clone the object.
         *
         * @return Cloned coordinate.
         */
        CoordinateBase<DATATYPE>::ptr_t clone()const{ 
            return CoordinateBase<DATATYPE>::ptr_t( new CoordinateBase<DATATYPE>(m_altitude_meters, 
                                                                                 m_datum)); 
        }


        /*
         * @brief Get the type.
         *
         * @return Coordinate type enumeration.
         */
        virtual CoordinateType Get_Type(){ 
            return CoordinateType::Base; 
        }

    protected:
        
        /// Coordinate Altitude in Meters
        DATATYPE m_altitude_meters;
        
        /// Projection Type
        Datum m_datum;
        

}; /// End of CoordinateBase class


/// Common Typdefs
typedef CoordinateBase<double> CoordinateBaseDouble;
typedef CoordinateBase<double> CoordinateBase_d;


} /// End of CRD Namespace
} /// End of GEO Namespace

#endif
