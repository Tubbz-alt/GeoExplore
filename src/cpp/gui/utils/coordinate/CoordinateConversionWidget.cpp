/**
 * @file    CoordinateConversionWidget.cpp
 * @author  Marvin Smith
 * @date    5/31/2014
*/
#include "CoordinateConversionWidget.hpp"

namespace GEO{
namespace GUI{

/*
 * Constructor
*/
CoordinateConversionWidget::CoordinateConversionWidget( QWidget* parent ) : QWidget(parent){

    // create the main layout
    mainLayout = new QVBoxLayout();

    // create the combo box for the from coordinate
    initialize_coordinate_type_combos();
    


    // set the main layout
    this->setLayout( mainLayout );

}
    
void CoordinateConversionWidget::initialize_coordinate_type_combos(){

    // create main widget
    coordinateTypeSelectionWidget = new QWidget(this);

    // create layout
    coordinateTypeSelectionLayout = new QVBoxLayout();

    // create widgets
    originalCoordinateTypeComboBox  = new QComboBox(coordinateTypeSelectionWidget);
    convertedCoordinateTypeComboBox = new QComboBox(coordinateTypeSelectionWidget);

    // load conversion types
    

    // add to gui
    coordinateTypeSelectionLayout->addWidget( originalCoordinateTypeComboBox );
    coordinateTypeSelectionLayout->addWidget( convertedCoordinateTypeComboBox );
    
    // set layout
    coordinateTypeSelectionWidget->setLayout( coordinateTypeSelectionLayout );

    // add to gui
    mainLayout->addWidget( coordinateTypeSelectionWidget);
}

} // End of GUI Namespace
} // End of GEO Namespace

