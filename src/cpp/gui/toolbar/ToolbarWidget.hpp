/**
 * @file    ToolbarWidget.hpp
 * @author  Marvin Smith
 * @date    5/29/2014
*/
#ifndef __SRC_CPP_GUI_TOOLBAR_TOOLBARWIDGET_HPP__
#define __SRC_CPP_GUI_TOOLBAR_TOOLBARWIDGET_HPP__

// Qt Libraries
#include <QGridLayout>
#include <QToolButton>
#include <QWidget>


/**
 * @class ToolbarWidget
 *
 * @brief Widget for the main toolbar
*/
class ToolbarWidget : public QWidget {

    Q_OBJECT

    public:
        
        /**
         * @brief Default Constructor
         *
         * @param[in] parent Parent widget
        */
        ToolbarWidget( QWidget* parent = NULL );

    private:
        
        /// Main Layout
        QGridLayout* m_mainLayout;

        /// Coordinate Conversion Button
        QToolButton* m_coordinateConversionButton;

}; /// End of ToolbarWidget Class


#endif
