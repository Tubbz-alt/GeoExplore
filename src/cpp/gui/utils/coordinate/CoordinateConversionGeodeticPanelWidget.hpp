/**
 * @file    CoordinateConversionGeodeticPanelWidget.hpp
 * @author  Marvin Smith
 * @date    6/4/2014
*/
#ifndef __COORDINATECONVERSIONGEODETICPANELWIDGET_HPP__
#define __COORDINATECONVERSIONGEODETICPANELWIDGET_HPP__

// Qt Libraries
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>


namespace GEO{
namespace GUI{

/**
 * @class CoordinateConversionGeodeticPanelWidget
*/
class CoordinateConversionGeodeticPanelWidget : public QWidget{

    Q_OBJECT

    public:
        
        /**
         * @brief Default Constructor
        */
        CoordinateConversionGeodeticPanelWidget( QWidget* parent = NULL );

    private:
        
        /**
         * Create the datum widget
        */
        void initialize_datum_widget();

        /// Main Layout
        QGridLayout* mainLayout;

        /// Datum Widget
        QWidget* datumWidget;

        /// Datum Widget Layout
        QHBoxLayout* datumLayout;

        /// Datum Widget Label
        QLabel* datumLabel;

        /// Datum Widget Combo
        QComboBox* datumComboBox;


}; // End of CoordinateConversionGeodeticPanelWidget Class

} // End of GUI Namespace
} // End of GEO Namespace

#endif
