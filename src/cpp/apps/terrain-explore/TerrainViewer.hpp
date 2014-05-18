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
    
    /**
     * Destructor
     */
    ~TerrainViewer();

    /* ***********************************************************
     *               Public Overloaded function
     ************************************************************/
    /**
     * Hints for creating window at the correct size
     */
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    /* ***********************************************************
     *               Protected Overloaded function
     ************************************************************/
    /**
     * Initialize OpenGL
     */
    void initializeGL();

    /**
     * Paint function occurs every frame
     */
    void paintGL();

    /**
     * Called when window is resized. Change Viewport, etc...
     */
    void resizeGL(int width, int height);

private:

    /// TODO These are temporary to test OpenGL. They will be abstracted away later
    struct Vertex
    {
        GLfloat position[3];
        GLfloat color[3];
    };
    GLuint m_program;
    GLuint m_vboGeometry;
    GLint m_locPosition;
    GLint m_locColor;
    // END TODO

    /// Holds the current window size
    QSize m_windowSize;
};

