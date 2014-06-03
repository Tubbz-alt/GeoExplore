/**
 * @file    CoordinateConversionWidget.cpp
 * @author  Marvin Smith
 * @date    5/31/2014
*/
#include "CoordinateConversionWidget.hpp"

// GeoExplore Library
#include "CoordinateConversionReference.hpp"

#include <iostream>

using namespace std;

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
    
    // initialize the stacked widget
    initialize_coordinate_panel_stack();

    // set the main layout
    this->setLayout( mainLayout );

}

/**
 * Coordinate Type Combo Box
*/
void CoordinateConversionWidget::initialize_coordinate_type_combos(){

    // create main widget
    coordinateTypeSelectionWidget = new QWidget(this);

    // create layout
    coordinateTypeSelectionLayout = new QVBoxLayout();

    // create widgets
    originalCoordinateTypeComboBox  = new QComboBox(coordinateTypeSelectionWidget);
    convertedCoordinateTypeComboBox = new QComboBox(coordinateTypeSelectionWidget);

    // load conversion types
    for( size_t i=0; i<The_CoordinateConversionReference::getInstance().Get_Size(); i++ ){
        originalCoordinateTypeComboBox->addItem(  The_CoordinateConversionReference::getInstance().Get_Coordinate_Type_Name(i).c_str() );
        convertedCoordinateTypeComboBox->addItem( The_CoordinateConversionReference::getInstance().Get_Coordinate_Type_Name(i).c_str() );
    }

    // add to gui
    coordinateTypeSelectionLayout->addWidget( originalCoordinateTypeComboBox );
    coordinateTypeSelectionLayout->addWidget( convertedCoordinateTypeComboBox );
    
    // set layout
    coordinateTypeSelectionWidget->setLayout( coordinateTypeSelectionLayout );

    // add to gui
    mainLayout->addWidget( coordinateTypeSelectionWidget);

}

/**
 * Initialize the Coordinate Panel Stacked Widget
*/
void CoordinateConversionWidget::initialize_coordinate_panel_stack(){

    // create widget
    m_conversionPanelStackPre  = new QStackedWidget(this);
    m_conversionPanelStackPost = new QStackedWidget(this);
    
    // create each gui
    for( size_t i=0; i<The_CoordinateConversionReference::getInstance().Get_Size(); i++ ){
            
        switch( The_CoordinateConversionReference::getInstance().Get_Coordinate_Type(i) ){

            case CoordinateType::Geodetic:
                
                // create a Geodetic Conversion Widget
                m_conversionPanelStackPre->addWidget(  new CoordinateConversionGeodeticPanelWidget());
                m_conversionPanelStackPost->addWidget( new CoordinateConversionGeodeticPanelWidget());
                break;

            case CoordinateType::UTM:
                m_conversionPanelStackPre->addWidget(  new CoordinateConversionUTMPanelWidget());
                m_conversionPanelStackPost->addWidget( new CoordinateConversionUTMPanelWidget());
                break;

            default:
                cout << "Error in the coordinate conversion widget" << endl;
                break;
        }

    }
    
    // add to main widget
    mainLayout->addWidget( m_conversionPanelStackPre );
    mainLayout->addWidget( m_conversionPanelStackPost );

}


} // End of GUI Namespace
} // End of GEO Namespace

