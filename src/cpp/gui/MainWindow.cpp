/**
 * @file    MainWindow.cpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#include "MainWindow.hpp"

// C++ Standard Libraries
#include <iostream>


namespace GEO{
namespace GUI{

/**
 * Default Constructor
 */
MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {

    /// set the window title
    setWindowTitle("GeoExplore");

    // create the toolbar
    create_toolbar_dock();
    
    // create the main view
    create_main_view();

    // create GUI connections
    create_connections();

}

/*
 * Create the main window
*/
void MainWindow::create_main_view(){

    // create the main scroll area
    m_mainScrollArea = new QScrollArea();
    this->setCentralWidget(m_mainScrollArea);

}


/**
 * Create the Toolbar Dock Widget
*/
void MainWindow::create_toolbar_dock(){

    /// Create the Dock Widget
    this->m_toolbarDock = new QDockWidget(tr("Toolbar"), this);

    // define the allowed areas
    m_toolbarDock->setAllowedAreas( Qt::RightDockWidgetArea );

    m_toolbarDock->setFeatures( QDockWidget::DockWidgetFloatable |
                                QDockWidget::DockWidgetMovable );

    // add the buttons
    this->m_toolbarWidget = new ToolbarWidget();
    m_toolbarDock->setWidget( m_toolbarWidget );
    

    // add the dock widget
    this->addDockWidget( Qt::RightDockWidgetArea, m_toolbarDock );

}

/**
 * Create the gui connections
*/
void MainWindow::create_connections(){

    // connect the toolbar's Coordinate Button to a 
    // Signal to Create A Coordinate Conversion widget
    connect( m_toolbarWidget, SIGNAL(openCoordinateConversionWidgetButtonClicked()), this, SLOT(openCoordinateConversionWindow()));


}

/**
 * Open Coordinate Conversion Window
*/
void MainWindow::openCoordinateConversionWindow(){
    
    // create a dialog
    CoordinateConversionDialog* coordinateConversionDialog = new CoordinateConversionDialog(this);

    // show the dialog
    coordinateConversionDialog->show();
    
}

} // End of GUI Namespace
} // End of GEO Namespace


