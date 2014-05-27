/**
 * @file    MainWindow.hpp
 * @author  Marvin Smith
 * @date    4/28/2014
 */
#ifndef __SRC_CPP_GUI_MAINWINDOW_HPP__
#define __SRC_CPP_GUI_MAINWINDOW_HPP__

/// Qt Libraries
#include <QApplication>
#include <QGridLayout>
#include <QMainWindow>
#include <QWidget>

/// GeoExplore
#include <GeoExplore.hpp>

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
        
        /// Main Layout
        QGridLayout*  mainLayout;

        /// List of widgets



};  /// End of MainWindow class

#endif

