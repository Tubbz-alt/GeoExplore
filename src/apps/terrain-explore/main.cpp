/**
 * @file    main.cpp
 * @author  Josh Gleason
 * @date    5/17/2014
 */

/// Include QtGui tools
#include <QApplication>

/// Terrain-Explore Libraries
#include "Options.hpp"
#include "TerrainViewer.hpp"

/// C++ Libraries
#include <exception>
#include <iostream>

using namespace std;

/**
 * Main Function
 */
int main(int argc, char* argv[])
{
    /// Return value
    int retVal = 0;

    try
    {
        /// Parse command line options
        Options options = parse_command_line(argc, argv);

        /// Create main app
        QApplication app(argc, argv);

        /// Create the viewer
        TerrainViewer viewer;
        viewer.show();
        viewer.setWindowTitle(QApplication::translate("terrain-explore", "Terrain-Explore"));

        /// Main loop
        retVal = app.exec();
    }
    catch (exception& e)
    {
        cerr << "error: " << e.what() << endl;
        usage(argv[0]);
        retVal = 1;
    }
    return retVal;
}

