/**
 * @file    TerrainViewer.hpp
 * @author  Josh Gleason
 * @date    5/17/2014
 */

/// Qt5 Headers
#include <GL/glew.h>
#include <QGLWidget>

class TerrainViewer : public QGLWidget
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    TerrainViewer(QWidget* parent = nullptr);

protected:

};

