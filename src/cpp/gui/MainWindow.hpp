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
#include <QWidget>

// GeoExplore
#include <GeoExplore.hpp>

// GUI Libraries
#include "toolbar/ToolbarWidget.hpp"

/**
 * Main Window for the Application
 */
class MainWindow : public QMainWindow {

    Q_OBJECT


    public:
        
        /**
         * Default Constructor
         */
        MainWindow( QWidget* parent = NULL );
    
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
        
        //--------------------------------------//
        //-          Private Variables         -//
        //--------------------------------------//

        /// Main View

        /// List of widgets
        QDockWidget* m_toolbarDock;

        /// Toolbar Widget
        ToolbarWidget* m_toolbarWidget;

};  /// End of MainWindow class

#endif

