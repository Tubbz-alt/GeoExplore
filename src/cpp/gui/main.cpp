/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */

/// Qt Libraries
#include <QApplication>
#include <QtGui>
#include <QWidget>

/// GeoExplore library
#include <GeoExplore.hpp>

/// GUI Libraries
#include "MainWindow.hpp"

/// C++ Libraries
#include <iostream>
#include <string>


/**
 * Main Function
 */
int main( int argc, char* argv[] ){

    try{

        /// set the filename for the config file
        std::string filename;
        filename = std::string(getenv("HOME")) + std::string("/.geoexplore/options.cfg");

        // load the config file parser
        //settings.load( argc, argv, filename );

    } catch ( std::exception& e ){
        std::cout << e.what() << std::endl;
    }

    /// Create the application
    QApplication app(argc, argv);

    /// Create main window
    GEO::GUI::MainWindow* mainWindow = new GEO::GUI::MainWindow();
    
    /// Display the main window
    mainWindow->show();

    /// Execute the application
    return app.exec();

} 

