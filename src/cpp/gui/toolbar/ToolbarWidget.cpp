/**
 * @file    ToolbarWidget.cpp
 * @author  Marvin Smith
 * @date    5/29/2014
*/
#include "ToolbarWidget.hpp"

/*
 * Default constructor
*/
ToolbarWidget::ToolbarWidget( QWidget* parent ) : QWidget(parent){

    // set the main layout
    m_mainLayout = new QGridLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setAlignment( Qt::AlignTop | Qt::AlignRight );

    this->setLayout( this->m_mainLayout );
    
    // create the coordinate conversion button
    m_coordinateConversionButton = new QToolButton(this);
    m_coordinateConversionButton->setText("Coordinate\nConversion");
    m_coordinateConversionButton->setIcon(QIcon("icons/coordinate_conversion_widget.png"));
    m_coordinateConversionButton->setIconSize(QSize(85,55));
    m_coordinateConversionButton->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    m_coordinateConversionButton->setFixedSize(QSize(90,100));
    m_mainLayout->addWidget( m_coordinateConversionButton, 0, 0 );
    
    // set the size
    setFixedWidth(100);
}

