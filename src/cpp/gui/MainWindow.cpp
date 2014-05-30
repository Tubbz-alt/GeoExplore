/**
 * @file    MainWindow.cpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#include "MainWindow.hpp"


/**
 * Default Constructor
 */
MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {

    /// set the window title
    setWindowTitle("GeoExplore");

    // create the toolbar
    create_toolbar_dock();

}

/*
 * Create the main window
*/
void MainWindow::create_main_view(){


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

