/** 
 * @file    CoordinateConversionGeodeticPanelWidget.cpp
 * @author  Marvin Smith
 * @date    6/4/2014
*/
#include "CoordinateConversionGeodeticPanelWidget.hpp"

namespace GEO{
namespace GUI{

/**
 * Constructor
*/
CoordinateConversionGeodeticPanelWidget::CoordinateConversionGeodeticPanelWidget( QWidget* parent ) : 
                                                                                  QWidget(parent){

    // create the main layout
    mainLayout = new QGridLayout();

    // initialize the datum widget
    initialize_datum_widget();

    // set the main layout
    setLayout( mainLayout );
}

/**
 * Initialize the datum widget
*/
void CoordinateConversionGeodeticPanelWidget::initialize_datum_widget(){

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


} // End of GUI Namespace
} // End of GEO Namespace


