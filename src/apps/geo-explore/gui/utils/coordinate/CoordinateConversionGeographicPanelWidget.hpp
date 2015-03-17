/**
 * @file    CoordinateConversionGeographicPanelWidget.hpp
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
#include <QLineEdit>
#include <QWidget>


namespace GEO{
namespace GUI{

/**
 * @class CoordinateConversionGeographicPanelWidget
*/
class CoordinateConversionGeographicPanelWidget : public QWidget{

    Q_OBJECT

    public:
        
        /**
         * @brief Default Constructor
        */
        CoordinateConversionGeographicPanelWidget( QWidget* parent = NULL );

    private:
       
        /**
         * @brief Initialize the Title Widget
        */
        void Initialize_Title_Widget();

        /**
         * Create the datum widget
        */
        void initialize_datum_widget();

        /**
         * Create the latitude widget
        */
        void initialize_latlon_widget();


        /// Main Layout
        QGridLayout* mainLayout;
    
    
        /*******************************/
        /*   Title Widget Materials    */
        /*******************************/
        /// Title Widget
        QWidget* titleWidget;

        /// Title Layout
        QHBoxLayout* titleLayout;

        /// Title Text Box
        QLabel* titleLabel;

        /********************************/
        /*    Datum Widget Materials    */
        /********************************/
        /// Datum Widget
        QWidget* datumWidget;

        /// Datum Widget Layout
        QHBoxLayout* datumLayout;

        /// Datum Widget Label
        QLabel* datumLabel;

        /// Datum Widget Combo
        QComboBox* datumComboBox;
        
        /***********************************/
        /*    Latitude Widet Materials     */
        /***********************************/

        /// LatLon Widget
        QWidget* latLonWidget;

        /// LatLon Layout
        QHBoxLayout* latLonLayout;

        /// Latitude Widget Label
        QLabel* latitudeLabel;

        /// Latitude Edit
        QLineEdit* latitudeEdit;

        /// Longitude Widget Label
        QLabel* longitudeLabel;

        /// Longitude Text Edit
        QLineEdit* longitudeEdit;


}; // End of CoordinateConversionGeographicPanelWidget Class

} // End of GUI Namespace
} // End of GEO Namespace

#endif
