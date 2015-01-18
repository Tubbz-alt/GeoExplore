/** 
 * @file    CoordinateConversionGeographicPanelWidget.cpp
 * @author  Marvin Smith
 * @date    6/4/2014
*/
#include "CoordinateConversionGeographicPanelWidget.hpp"

namespace GEO{
namespace GUI{

/**
 * Constructor
*/
CoordinateConversionGeographicPanelWidget::CoordinateConversionGeographicPanelWidget( QWidget* parent ) : 
                                                                                  QWidget(parent){

    // create the main layout
    mainLayout = new QGridLayout();

    // Initialize the title widget
    Initialize_Title_Widget();

    // initialize the datum widget
    initialize_datum_widget();

    // initialize the latitude widget
    initialize_latlon_widget();

    // set the main layout
    setLayout( mainLayout );
}

/**
 * Initialize the Title Widget
*/
void CoordinateConversionGeographicPanelWidget::Initialize_Title_Widget()
{

    // Create the widget
    titleWidget = new QWidget(this);

    // Create the layout
    titleLayout = new QHBoxLayout();

    // Create the label
    titleLabel = new QLabel("Geographic Coordinate Panel");
    titleLayout->addWidget(titleLabel);

    // Set the layout
    titleWidget->setLayout(titleLayout);

    // add to widget
    mainLayout->addWidget( titleWidget );

}

/**
 * Initialize the datum widget
*/
void CoordinateConversionGeographicPanelWidget::initialize_datum_widget(){

    // create widget
    datumWidget = new QWidget(this);

    // create the layout
    datumLayout = new QHBoxLayout();

    // create the label
    datumLabel = new QLabel("Datum:");
    datumLayout->addWidget(datumLabel);

    // create the combo
    datumComboBox = new QComboBox();
    datumLayout->addWidget( datumComboBox );

    // set the layout
    datumWidget->setLayout( datumLayout );

    // add to widget
    mainLayout->addWidget( datumWidget );

}

/**
 * Initialize the LatLon Widget
*/
void CoordinateConversionGeographicPanelWidget::initialize_latlon_widget(){


    // create widget
    latLonWidget = new QWidget(this);

    // create the layout
    latLonLayout = new QHBoxLayout();

    // create the latitude label
    latitudeLabel = new QLabel("Lat:");
    latLonLayout->addWidget( latitudeLabel );

    // create the latitude edit
    latitudeEdit = new QLineEdit();
    latLonLayout->addWidget(latitudeEdit);

    // create the longitude label
    longitudeLabel = new QLabel("Lon:");
    latLonLayout->addWidget(longitudeLabel);

    // create the longitude edit
    longitudeEdit = new QLineEdit();
    latLonLayout->addWidget( longitudeEdit );

    // set the layout
    latLonWidget->setLayout( latLonLayout );

    // add to main layout
    mainLayout->addWidget( latLonWidget );


}

} // End of GUI Namespace
} // End of GEO Namespace


