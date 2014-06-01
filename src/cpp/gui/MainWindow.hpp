/**
 * @file    MainWindow.hpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#ifndef __SRC_CPP_GUI_MAINWINDOW_HPP__
#define __SRC_CPP_GUI_MAINWINDOW_HPP__

// Qt Libraries
#include <QApplication>
#include <QDockWidget>
#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QWidget>

// GeoExplore
#include <GeoExplore.hpp>

// GUI Libraries
#include "toolbar/ToolbarWidget.hpp"
#include "utils/coordinate/CoordinateConversionDialog.hpp"

namespace GEO{
namespace GUI{

/**
 * @class MainWindow
 *
 * @brief Main Window for the Application
 */
class MainWindow : public QMainWindow {

    Q_OBJECT


    public:
        
        /**
         * @brief Default Constructor
         */
        MainWindow( QWidget* parent = NULL );
    
    private slots:
        
        /**
         * Open a coordinate conversion window
        */
        void openCoordinateConversionWindow();

    private:
        
        //--------------------------------------//
        //-         Private Functions          -//
        //--------------------------------------//
    
        /**
         * @brief Create the main window
         */
        void create_main_view();

        /**
         * @brief Create the Docked Toolbar
        */
        void create_toolbar_dock();
        
        /**
         * @brief Create Button Connections
        */
        void create_connections();

        //--------------------------------------//
        //-          Private Variables         -//
        //--------------------------------------//

        /// List of widgets
        QDockWidget* m_toolbarDock;

        /// Toolbar Widget
        ToolbarWidget* m_toolbarWidget;
        
        /// Main Window
        QScrollArea* m_mainScrollArea;

        
};  /// End of MainWindow class

} // End of GUI Namespace
} // End of GEO Namespace


#endif

