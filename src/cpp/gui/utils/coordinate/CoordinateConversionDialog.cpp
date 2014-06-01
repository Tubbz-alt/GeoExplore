/**
 * @file    CoordinateConversionDialog.cpp
 * @author  Marvin Smith
 * @date    5/30/2014
*/
#include "CoordinateConversionDialog.hpp"

namespace GEO{
namespace GUI{

/**
 * Constructor
*/
CoordinateConversionDialog::CoordinateConversionDialog( QWidget* parent ) : QDialog(parent){


    // create main layout
    mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // create the widget
    mainWidget = new CoordinateConversionWidget();
    mainLayout->addWidget(mainWidget);

    // set the main layout
    setLayout( mainLayout );

    // set the window title
    setWindowTitle("Coordinate Conversion Utility");

}

} // End of GUI Namespace
} // End of GEO Namespace

