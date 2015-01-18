/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    4/14/2014
 */

/// Qt Libraries
#include <QApplication>

/// GeoExplore library
#include <GeoExplore.hpp>

/// GUI Libraries
#include "MainWindow.hpp"

/// C++ Libraries
#include <iostream>
#include <string>

using namespace std;


/**
 * Main Function
 */
int main( int argc, char* argv[] ){

    try{

        /// set the filename for the config file
        string filename;
        filename = string(getenv("HOME")) + string("/.geoexplore/options.cfg");

        // load the config file parser
        //settings.load( argc, argv, filename );

    } catch ( exception& e ){
        cout << e.what() << endl;
    }

    /// Create the application
    QApplication app(argc, argv);

    /// Create main window
    MainWindow* mainWindow = new MainWindow();
    
    /// Display the main window
    mainWindow->show();

    /// Execute the application
    return app.exec();

} 


