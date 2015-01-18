/**
 * @file    CoordinateConversionUTMPanelWidget.hpp
 * @author  Marvin Smith
 * @date    6/4/2014
*/
#ifndef __COORDINATECONVERSIONUTMPANELWIDGET_HPP__
#define __COORDINATECONVERSIONUTMPANELWIDGET_HPP__

// Qt Libraries
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

namespace GEO{
namespace GUI{

/**
 * @class CoordinateConversionUTMPanelWidget
*/
class CoordinateConversionUTMPanelWidget : public QWidget{

    Q_OBJECT

    public:
        
        /**
         * @brief Constructor
        */
        CoordinateConversionUTMPanelWidget( QWidget* parent = NULL );

    private:

        /**
         * @brief Create the Title Widget
         */
        void Initialize_Title_Widget();

        /**
         * Create the datum widget
        */
        void initialize_datum_widget();

        /************************************/
        /*           Core Elements          */
        /************************************/
        /// Main Layout
        QGridLayout* mainLayout;
        
        /************************************/
        /*       Title Widget Elements      */
        /************************************/
        /// Title Widget
        QWidget* titleWidget;

        /// Title Layout
        QHBoxLayout* titleLayout;

        /// Title Label
        QLabel*   titleLabel;

        /************************************/
        /*       Datum Widget Elements      */
        /************************************/
        /// Datum widget
        QWidget* datumWidget;

        /// Datum Layout
        QHBoxLayout* datumLayout;

        /// Datum Label
        QLabel* datumLabel;

        /// Datum Combo
        QComboBox* datumComboBox;


}; /// End of CoordinateConversionUTMPanelWidget Class

} // End of GUI Namespace
} // End of GEO Namespace

#endif
