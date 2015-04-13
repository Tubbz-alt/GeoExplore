/**
 * @file    CoordinateGeographic.hpp
 * @author  Marvin Smith
 * @date    4/16/2014
 */
#ifndef __SRC_COORDINATE_COORDINATEGEODETIC_HPP__
#define __SRC_COORDINATE_COORDINATEGEODETIC_HPP__

// C++ Standard Libraries
#include <cmath>
#include <iostream>

// GeoExplore Libraries
#include "../core/Enumerations.hpp"
#include "../math/A_Point.hpp"
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
                              Datum const& datum ) 
            :  CoordinateBase<DATATYPE>( 0, datum ),
               m_latitude_degrees(latitude_degrees), 
               m_longitude_degrees(longitude_degrees)
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
            :  CoordinateBase<DATATYPE>( altitude_meters, datum ),
               m_latitude_degrees(latitude_degrees), 
               m_longitude_degrees(longitude_degrees)
        {
        }

        
        /**
         * @brief Build a coordinate from an ND point.
         *
         * @param[in] point Point to set. If the point has more than 2 dimensions, it will set the z.
         * @param[in] datum Datum to use.
         */
        template <int Dimensions>
        CoordinateGeographic( MATH::A_Point<datatype,Dimensions> const& point, 
                              Datum const& datum = Datum::WGS84 )
          :  CoordinateBase<DATATYPE>( 0, datum ),
             m_latitude_degrees( point.y() ),
             m_longitude_degrees( point.x() )
        {
            if( point.Dims() >= 3 ){
                this->altitude_meters() = point.z();
            }
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
         * @brief Get the Longitude in Radians.
         *
         * @return Longitude in radians.
         */
        datatype longitude_radians()const
        {
            return m_longitude_degrees * M_PI / 180.0;
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
         * @brief Addition Operator
         *
         * @param[in] other Other coordinate to add.
         *
         * @return Added Coordinate.
        */
        CoordinateGeographic<DATATYPE> operator+ ( CoordinateGeographic<DATATYPE> const& other )const
        {
            // Create output
            CoordinateGeographic<DATATYPE> output;
            output.m_latitude_degrees  = m_latitude_degrees      + other.m_latitude_degrees;
            output.m_longitude_degrees = m_longitude_degrees     + other.m_longitude_degrees;
            output.m_altitude_meters   = this->m_altitude_meters + other.m_altitude_meters;
            output.m_datum = this->m_datum;
            return output;
        }
        
        /**
         * @brief Subtraction Operator
         *
         * @param[in] other Other coordinate to subtract
         *
         * @return Subtracted Coordinate.
        */
        CoordinateGeographic<DATATYPE> operator - ( CoordinateGeographic<DATATYPE> const& other )const
        {
            // Create output
            CoordinateGeographic<DATATYPE> output;
            output.m_latitude_degrees  = m_latitude_degrees  - other.m_latitude_degrees;
            output.m_longitude_degrees = m_longitude_degrees - other.m_longitude_degrees;
            output.m_altitude_meters   = this->m_altitude_meters - other.m_altitude_meters;
            output.m_datum = this->m_datum;
            return output;
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
        

        /**
         * @brief Distance using the Vincenty Formula
         *
         * @param[in] coordinate1 First coordinate.
         * @param[in] coordinate2 Second coordinate.
         *
         * @return Distance between two in meters.
         */
        static double  Distance_Vincenty( CoordinateGeographic<DATATYPE> const& coordinate1,
                                          CoordinateGeographic<DATATYPE> const& coordinate2 )
        {

            if( std::fabs(coordinate1.latitude_degrees()  - coordinate2.latitude_degrees())  < 0.1 &&
                std::fabs(coordinate1.longitude_degrees() - coordinate2.longitude_degrees()) < 0.1 )
            {
                return std::sqrt(std::pow(coordinate1.altitude_meters() - coordinate2.altitude_meters(), 2.0));
            }

            //  Create output
            double distance = 0;

            // Get the ellipsoid parameters 
            const double a = 6378137.0;
            const double f_inv = 298.257223563;
            const double f = 1/f_inv;
            const double b = (1-f) * a;

            // Get the latitude and longitudes in radians
            const double lat1 = coordinate1.latitude_radians();
            const double lat2 = coordinate2.latitude_radians();

            const double lon1 = coordinate1.longitude_radians();
            const double lon2 = coordinate2.longitude_radians();

            // Compute Reduced Latitude
            const double U1 = std::atan((1-f) * std::tan(lat1));
            const double U2 = std::atan((1-f) * std::tan(lat2));
            const double L = lon2 - lon1;

            double lambda = L;
            double lambda0;
            double sigma;
            double sin_sigma, cos_sigma, sin_lambda, cos_lambda;
            double cos_alpha_sq, sin_alpha;
            double cosU2_sinlambda_sq;
            double cos_2sigma_m, cos_2sigma_m_sq;
            double C;
            double eps = 0.00001;

            while( true ){

                // Compute cos U2 sin Lambda squared
                cosU2_sinlambda_sq = std::pow(std::cos(U2) * std::sin(lambda), 2.0);

                // Compute Sin Sigma
                sin_sigma = std::sqrt(cosU2_sinlambda_sq + std::pow( std::cos(U1) * std::sin(U2) - std::sin(U1) * std::cos(U2) * std::cos(lambda), 2.0));
                cos_sigma = std::sin(U1) * std::sin(U2) + std::cos(U1) * std::cos(U2) * std::cos(lambda);

                // Compute sigma
                sigma = std::atan2( sin_sigma, cos_sigma );

                // Compute alpha
                sin_alpha = (std::cos(U1) * std::cos(U2) * std::sin(lambda)) / sin_sigma;

                // cos2 sigma
                cos_alpha_sq = 1 - ( sin_alpha * sin_alpha );

                // cos_2sigma_m 
                cos_2sigma_m = cos_sigma - (2 * std::sin(U1) * std::sin(U2)) / (cos_alpha_sq);
                cos_2sigma_m_sq = cos_2sigma_m * cos_2sigma_m;

                // C 
                C = (f / 16) * cos_alpha_sq * (4 + f * (4 - 3 * cos_alpha_sq));

                // lambda
                lambda0 = lambda;
                lambda = L + (1-C) * f * sin_alpha * (sigma + C * sin_sigma * ( cos_2sigma_m + C * cos_sigma * (-1 + 2 * cos_2sigma_m_sq )));

                // Check lambda
                std::cout << "Lambda: " << lambda << std::endl;
                if( lambda < eps || (lambda >= lambda0) ){
                    break;
                }
            }

            double u2 = cos_alpha_sq * (a*a - b*b)/(b*b);

            double A = 1 + (u2 / 16384) * ( 4096 + u2 * (-768 + u2 * (320 - 175*u2)));
            double B = (u2 / 1024.0) * (256 + u2 * (-128 + u2 * (74 - 47*u2)));

            double sigma_diff = B * sin_sigma * (cos_2sigma_m + 0.25 * B * ( cos_sigma * (-1 + 2*cos_2sigma_m_sq ) - (1/6.0) * B * cos_2sigma_m * (-3 + 4 * sin_sigma * sin_sigma)*(-3 + 4 * cos_2sigma_m_sq)));

            distance = b * A * ( sigma - sigma_diff );

            
            // return distance
            return distance;

        }
        
        /**
         * @brief Print as a GE string
         *
         * @return Google Earth Friendly String
        */
        std::string ToGoogleEarthString()const{
            std::stringstream sin;
            sin << "CoordinateGeographic: " << std::fixed << m_latitude_degrees;
            sin <<  " " << m_longitude_degrees << " " << this->altitude_meters();
            return sin.str();
        }


        /**
         * @brief Print as a pretty string
         *
         * @return Pretty String
        */
        std::string ToPrettyString()const{
            std::stringstream sin;
            sin << "CoordinateGeographic( latitude: " << std::fixed << m_latitude_degrees;
            sin << ", longitude: " << m_longitude_degrees << " )";
            return sin.str();
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
