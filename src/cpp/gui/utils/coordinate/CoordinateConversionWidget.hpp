/**
 * @file    CoordinateConversionWidget.hpp
 * @author  Marvin Smith
 * @date    5/31/2014
*/
#ifndef __COORDINATE_CONVERSION_WIDGET_HPP__
#define __COORDINATE_CONVERSION_WIDGET_HPP__

// Qt Libraries
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace GEO{
namespace GUI{

/**
 * @class CoordinateConversionWidget
*/
class CoordinateConversionWidget : public QWidget {

    public:
        
        /**
         * @brief Constructor
        */
        CoordinateConversionWidget( QWidget* parent = NULL );

        
    private:
        
        //-------------------------------------//
        //-         Private Functions         -//
        //-------------------------------------//
        
        /**
         * @brief Initialize the Coordinate Type Combo Boxes
        */
        void initialize_coordinate_type_combos();

        //-------------------------------------//
        //-         Private Variables         -//
        //-------------------------------------//
        
        /// Main Layout
        QVBoxLayout* mainLayout;

        /// Combo Box Selection Widget
        QWidget* coordinateTypeSelectionWidget;

        /// Coordinate Type Selection Layout
        QVBoxLayout* coordinateTypeSelectionLayout;

        /// Initial Coordinate Combo Box
        QComboBox* originalCoordinateTypeComboBox;
        
        /// Converted Coordinate Combo Box
        QComboBox* convertedCoordinateTypeComboBox;


}; /// End of CoordinateConversionWidget

} // End of GUI Namespace
} // End of GEO Namespace

#endif
