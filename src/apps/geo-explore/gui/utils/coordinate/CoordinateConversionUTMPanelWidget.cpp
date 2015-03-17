/**
 * @file    CoordinateConversionUTMPanelWidget.cpp
 * @author  Marvin Smith
 * @date    6/4/2014
*/
#include "CoordinateConversionUTMPanelWidget.hpp"

namespace GEO{
namespace GUI{

/**
 * Constructor
*/
CoordinateConversionUTMPanelWidget::CoordinateConversionUTMPanelWidget(QWidget* parent ) 
                                                                     : QWidget(parent){

    
    // create the main layout
    mainLayout = new QGridLayout();
    
    // Initialize the title widget
    Initialize_Title_Widget();

    // initialize the datum combo
    initialize_datum_widget();

    // set the main layout  
    setLayout( mainLayout );

}

/**
 * Initialize the Title Widget
*/
void CoordinateConversionUTMPanelWidget::Initialize_Title_Widget(){
    
    // Create the widget
    titleWidget = new QWidget(this);

    // Create the layout
    titleLayout = new QHBoxLayout();

    // Create the label
    titleLabel = new QLabel("Universal Transverse Mercator Coordinate Panel");
    titleLayout->addWidget(titleLabel);

    // Set the layout
    titleWidget->setLayout(titleLayout);

    // add to widget
    mainLayout->addWidget( titleWidget );

}

/**
 * Initialize the datum widget
*/
void CoordinateConversionUTMPanelWidget::initialize_datum_widget(){

    // create the widget
    datumWidget = new QWidget(this);

    // create the layout
    datumLayout = new QHBoxLayout();

    // create the label
    datumLabel = new QLabel("Datum:");
    datumLayout->addWidget( datumLabel );

    // create the combo box
    datumComboBox = new QComboBox();
    datumLayout->addWidget( datumComboBox );

    // set the layout
    datumWidget->setLayout( datumLayout );

    // add the widget
    mainLayout->addWidget( datumWidget );

}


} // End of GUI Namespace
} // End of GEO Namespace


