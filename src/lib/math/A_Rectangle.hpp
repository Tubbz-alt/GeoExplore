#ifndef __GEOEXPLORE_MATH_A_RECTANGLE_HPP__
#define __GEOEXPLORE_MATH_A_RECTANGLE_HPP__

// Geo-Explore Libraries
#include "../coordinate/CoordinateUTM.hpp"
#include "A_Point.hpp"
#include "A_Polygon.hpp"

// C++ Standard Libraries
#include <sstream>
#include <string>

namespace GEO{
namespace MATH{

/**
 * @class A_Rectangle
*/
template< typename PointType >
class A_Rectangle : public A_Polygon<PointType> {

    public:

        /// Datatype
        typedef typename PointType::datatype datatype;
        
        /**
         * @brief Constructor
        */
        A_Rectangle()
          : A_Polygon<PointType>()
        {

        }

        
        /**
         * @brief Constructor given a minimum point, height, and width.
         *
         * @param[in] min_corner Minimum corner.
         * @param[in] width Width of rectangle.
         * @param[in] height Height of rectangle.
         */
        A_Rectangle( PointType const& min_corner,
                     datatype  const& width,
                     datatype  const& height )
          : m_min_corner(min_corner),
            m_width(width),
            m_height(height)
        {
        }


        /**
         * @brief Constructor given two points.
         *
         * @param[in] min_corner Min corner.
         * @param[in] max_corner Max corner.
         */
        A_Rectangle( PointType const& min_corner,
                     PointType const& max_corner )
          : A_Polygon<PointType>(),
            m_min_corner(min_corner),
            m_width((max_corner - min_corner).x()),
            m_height((max_corner - min_corner).y())
        {
        }


        /**
         * @brief Get the Minimum Corner
         *
         * @return Min Corner
        */
        PointType BL()const{
            return m_min_corner;
        }


        /**
         * @brief Get the Top-Left Corner.
         *
         * @return Top-Left Corner.
         */
        PointType TL()const{
            return (m_min_corner + A_Point2<typename PointType::datatype>(0,m_height));
        }


        /**
         * @brief Get the Top-Right Corner.
         *
         * @return Top-Right Corner.
        */
        PointType TR()const{
            return (m_min_corner + A_Point2<typename PointType::datatype>(m_width,m_height));
        }


        /**
         * @brief Get the Bottom-Right Corner.
         *
         * @return Bottom-Right Corner.
        */
        PointType BR()const{
            return (m_min_corner + A_Point2<typename PointType::datatype>(m_width,0));
        }


        /**
         * @brief Get the Width
         *
         * @return the width
        */
        datatype Width()const{
            return m_width;
        }


        /**
         * @brief Get the Height.
         *
         * @return Height
        */
        datatype Height()const{
            return m_height;
        }


        /**
         * @brief Get the area.
         *
         * @return Area of rectangle.
        */
        double Area()const{
            return (Width() * Height());
        }
        

        /**
         * @brief Check if point is inside of the rectangle.
         *
         * @param[in] point Point to check.
         *
         * @return True if the point is in the rectangle, false otherwise.
         */
        bool Inside( PointType const& point )const
        {
            // Check if the point is inside the box
            if( point.x() < m_min_corner.x() || point.x() > (m_min_corner.x() + m_width)){
                return false;
            }
            if( point.y() < m_min_corner.y() || point.y() > (m_min_corner.y() + m_height)){
                return false;
            }
            return true;
        }

        /**
         * @brief Get the Intersection of the image.
         *
         * @param[in] other Rectangle to compute intersection of.
         *
         * @return Rectangle composed of the overlap.
         */
        A_Rectangle<PointType> Intersection( A_Rectangle<PointType> const& other )const{

            // First check that they even touch 
            if( BL().x() > other.BR().x() || 
                BL().y() > other.TL().y() || 
                BR().x() < other.BL().x() ||
                TL().y() < other.BL().y() ){
                return A_Rectangle<PointType>();
            }
            
            // Compute the max/min values
            datatype minX = std::max( BL().x(), other.BL().x() );
            datatype maxX = std::min( BR().x(), other.BR().x() );
            datatype minY = std::max( BL().y(), other.BL().y() );
            datatype maxY = std::min( TL().y(), other.TL().y() );

            return A_Rectangle<PointType>( PointType( minX, minY),
                                           maxX-minX, 
                                           maxY-minY);
        }


        /**
         * @brief Compute the Rectangle Union.
         *
         * @param[in] other Rectangle to compute the union of.
         *
         * @return Rectangle union.
        */
        A_Rectangle<PointType> Union( A_Rectangle<PointType>const& other )const{

            // Compute ranges
            datatype minX = std::min( BL().x(), other.BL().x());
            datatype minY = std::min( BL().y(), other.BL().y());
            datatype maxX = std::max( TR().x(), other.TR().x());
            datatype maxY = std::max( TR().y(), other.TR().y());
            
            return A_Rectangle<PointType>( PointType( minX, minY), 
                                           maxX-minX, 
                                           maxY-minY);
        }


        /**
         * @brief Get the Min Corner.
         *
         * @return Min Corner.
        */
        PointType& Get_Min_Corner(){
            return m_min_corner;
        }

        
        /**
         * @brief Print as a string.
         *
         * @return pretty string
         */
        std::string ToPrettyString()const{
            std::stringstream sin;
            sin << std::fixed << "A_Rectangle: Min_Corner: " << m_min_corner.ToPrettyString() << std::endl;
            sin << "             Width: " << m_width << std::endl;
            sin << "             Height: " << m_height << std::endl;
            return sin.str();
        }


    protected:
        
        /// Minimum Corner
        PointType m_min_corner;

        /// Width of Rectangle
        datatype m_width;

        /// Height of Rectangle
        datatype m_height;


}; /// End of A_Rectangle Class

// Typedefs
typedef A_Rectangle<A_Point2i> A_Rectangle2i;
typedef A_Rectangle<A_Point2f> A_Rectangle2f;
typedef A_Rectangle<A_Point2d> A_Rectangle2d;
typedef A_Rectangle<CRD::CoordinateUTM_d> A_RectangleUTMd;

} // End of MATH Namespace
} // End of GEO  Namespace


#endif

