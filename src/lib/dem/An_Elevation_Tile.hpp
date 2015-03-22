/**
 * @file    Elevation_Tile.hpp
 * @author  Marvin Smith
 * @date    3/8/2015
*/
#ifndef __GEOEXPLORE_DEM_ELEVATION_TILE_HPP__
#define __GEOEXPLORE_DEM_ELEVATION_TILE_HPP__

// GeoExplore Libraries
#include "../core/A_Size.hpp"
#include "../image/ChannelType.hpp"
#include "../image/Image.hpp"
#include "../image/MemoryResource.hpp"
#include "../image/PixelGray.hpp"
#include "../math/A_Point.hpp"


// C++ Standard Libraries
#include <memory>


namespace GEO{
namespace DEM{

/**
 * @class DEM
*/
template <typename CoordinateType,
          typename ElevationDataType>
class An_Elevation_Tile {

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<An_Elevation_Tile> ptr_t;

        
        /**
         * @brief Constructor
        */
        An_Elevation_Tile( const CoordinateType&    bottom_left_corner,
                           const A_Size<int>&       elevation_tile_size,
                           const double&            gsd )
            : m_elevation_data(new IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df> >(elevation_tile_size, 
                                                                                                          IMG::PixelGray_df(0))),
              m_gsd(gsd),
              m_bottom_left_corner(bottom_left_corner)
        {
        }


        /**
         * @brief Constructor given default elevation value.
         *
         * @param[in] bottom_left_corner Bottom left corner.
         * @param[in] gsd Ground sampling distance in meters-per-pixel.
         * @param[in] elevation_tile_size Size of elevation tile in pixels.
         * @param[in] default_elevation_value_meters Elevation in meters.
        */
        An_Elevation_Tile( const CoordinateType&       bottom_left_corner,
                           const A_Size<int>&          elevation_tile_size,
                           const double&               gsd,
                           const ElevationDataType&    default_elevation_value_meters )
            : m_elevation_data(new IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df>>( elevation_tile_size,        
                                                                                                         IMG::PixelGray_df(default_elevation_value_meters))),
              m_gsd(gsd),
              m_bottom_left_corner(bottom_left_corner)
        {
        }


        /**
         * @brief Get the number of rows.
         *
         * @return Number of columns in pixels.
        */
        int Rows()const{
            return m_elevation_data->Rows();
        }


        /**
         * @brief Get the number of columns.
         *
         * @return Number of columns in pixels.
        */
        int Cols()const{
            return m_elevation_data->Cols();
        }
        
        
        /**
         * @brief Get the GSD In meters per pixel.
         *
         * @return GSD (meters per pixel).
        */
        double Get_GSD()const{
            return m_gsd;
        }


        /**
         * @brief Get the Top-Left Corner
         *
         * @return Top-Left Corner
        */
        CoordinateType Get_Corner_TL()const{
            
            // Create new coordinate
            CoordinateType add_coord;

            // Update the x and y values
            add_coord.x() = 0;
            add_coord.y() = Rows() * Get_GSD();

            // Add the coordinate
            return (m_bottom_left_corner + add_coord);

        }

        
        /**
         * @brief Get the Top-Right Corner
         *
         * @return Top-Right Corner
        */
        CoordinateType Get_Corner_TR()const{
            
            // Create new coordinate
            CoordinateType add_coord;

            // Update the x and y values
            add_coord.x() = Cols() * Get_GSD();
            add_coord.y() = Rows() * Get_GSD();

            // Add the coordinate
            return (m_bottom_left_corner + add_coord);

        }


        /**
         * @brief Get the Bottom-Left Corner
         *
         * @return Bottom-Left Corner.
        */
        CoordinateType Get_Corner_BL()const{
            return m_bottom_left_corner;
        }


        /**
         * @brief Get the Bottom-Right Corner
         *
         * @return Bottom-Right Corner
        */
        CoordinateType Get_Corner_BR()const{
            
            // Create new coordinate
            CoordinateType add_coord;

            // Update the x and y values
            add_coord.x() = Cols() * Get_GSD();
            add_coord.y() = 0;

            // Add the coordinate
            return (m_bottom_left_corner + add_coord);

        }


        /**
         * @brief Get a pixel value.
         * 
         * @param[in] row Row value in pixels.
         * @param[in] col Column value in pixels.
         * 
         * @return Elevation at row/col.
        */
        double operator()( const int& row,
                           const int& col )const
        {
            return m_elevation_data->operator()(row,col)[0];
        }
    

    private:

        /// Elevation Data
        IMG::Image_<IMG::PixelGray_df,IMG::MemoryResource<IMG::PixelGray_df>>::ptr_t m_elevation_data; 
        
        /// GSD
        double m_gsd;

        /// Bottom-Left Corner
        CoordinateType m_bottom_left_corner;

}; /// End of An_Elevation_Tile Class

// Typedef
typedef An_Elevation_Tile<CRD::CoordinateUTM<double>,double> ElevationTileUTM_d;


} /// End of DEM Namespace
} /// End of GEO Namespace

#endif
