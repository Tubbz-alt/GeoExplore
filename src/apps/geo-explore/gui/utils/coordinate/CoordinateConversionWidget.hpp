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
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

// GeoExplore GUI Libraries
#include "CoordinateConversionGeographicPanelWidget.hpp"
#include "CoordinateConversionUTMPanelWidget.hpp"

namespace GEO{
namespace GUI{

/**
 * @class CoordinateConversionWidget
*/
class CoordinateConversionWidget : public QWidget {

    Q_OBJECT

    public:
        
        /**
         * @brief Constructor
        */
        CoordinateConversionWidget( QWidget* parent = NULL );

    private slots:
        
        /**
         * Change the From Coordinate Dialog
        */
        void changeOriginalCoordinateDialog();

        /**
         * Change the To Coordinate Dialog
        */
        void changeConvertedCoordinateDialog();
        
    private:
        
        //-------------------------------------//
        //-         Private Functions         -//
        //-------------------------------------//
        
        /**
         * @brief Initialize the Coordinate Type Combo Boxes
        */
        void initialize_coordinate_type_combos();

        /**
         * @brief Initialize the Coordinate Panel Stack
        */
        void initialize_coordinate_panel_stack();

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

        /// Stacked Widget
        QStackedWidget* m_conversionPanelStackPre;
        QStackedWidget* m_conversionPanelStackPost;

        

}; /// End of CoordinateConversionWidget

} // End of GUI Namespace
} // End of GEO Namespace

#endif
