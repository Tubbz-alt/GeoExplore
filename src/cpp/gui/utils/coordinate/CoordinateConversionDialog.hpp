/**
 * @file    CoordinateConversionDialog.hpp
 * @author  Marvin Smith
 * @date    5/30/2014
*/
#ifndef __COORDINATECONVERSIONDIALOG_HPP__
#define __COORDINATECONVERSIONDIALOG_HPP__

// Qt Libraries
#include <QDialog>
#include <QVBoxLayout>

// GeoExplore Libraries
#include "CoordinateConversionWidget.hpp"

namespace GEO{
namespace GUI{

/**
 * @class CoordinateConversionDialog
*/
class CoordinateConversionDialog : public QDialog{

    Q_OBJECT

    public:
        
        /**
         * @constructor
        */
        CoordinateConversionDialog( QWidget* parent = NULL );

    private:
        
        /// Main Layout
        QVBoxLayout* mainLayout;

        /// Main Widget
        CoordinateConversionWidget* mainWidget;

}; // End of CoordinateConversion Dialog


} // End of GUI Namespace
} // End of GEO Namespace

#endif
