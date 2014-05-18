/**
 * @file    TerrainViewer.cpp
 * @author  Josh Gleason
 * @date    5/17/2014
 */

/// Include Prototype Headers
#include "TerrainViewer.hpp"

/**
 * Default constructor
 */
TerrainViewer::TerrainViewer(QWidget* parent) :
    QGLWidget(parent)
{
    glewInit();
}

