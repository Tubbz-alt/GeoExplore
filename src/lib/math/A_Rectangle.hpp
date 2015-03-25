#ifndef __GEOEXPLORE_MATH_A_RECTANGLE_HPP__
#define __GEOEXPLORE_MATH_A_RECTANGLE_HPP__

// Geo-Explore Libraries
#include "../coordinate/CoordinateUTM.hpp"
#include "A_Point.hpp"
#include "A_Polygon.hpp"

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
            return (m_min_corner + PointType(0,m_height));
        }


        /**
         * @brief Get the Top-Right Corner.
         *
         * @return Top-Right Corner.
        */
        PointType TR()const{
            return (m_min_corner + PointType(m_width,m_height));
        }


        /**
         * @brief Get the Bottom-Right Corner.
         *
         * @return Bottom-Right Corner.
        */
        PointType BR()const{
            return (m_min_corner + PointType(m_width,0));
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

