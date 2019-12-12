#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QVector3D>

#include "logic/world.h"
#include "logic/character.h"


class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core
{
public:
    Renderer(QWidget *Parent = 0);
    ~Renderer();

    World *gameWorld;
    Character *gameCharacter;

protected:
    void initializeGL() override;
    void resizeGL(int newWidth, int newHeight) override;
    void paintGL() override;

private:

    void createShaderPrograms();
    void createBuffers();
    void updateBuffers();
    void updateUniforms();

    void initDebugger();
    QOpenGLDebugLogger *debugLogger;

    // Shader programs
    QOpenGLShaderProgram *mainShaderProgram;

    // Vertex array objects
    GLuint worldVAO;
    // Buffer objects
    GLuint coordinatesBO, normalsBO;
    // IBO
    unsigned int worldIBOsize;
};

#endif // RENDERER_H
