#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QVector>
#include <QVector3D>

#include "logic/world.h"
#include "logic/character.h"

class Renderer: protected QOpenGLFunctions_4_1_Core
{
public:
    Renderer();
    ~Renderer();

    World *gameWorld;
    Character *gameCharacter;
    int scale;
    bool uniformUpdateRequired;

    void render();

private:
    void createShaderPrograms();
    void createSimpleShaderProgram();
    void createBuffers();
    void createSimpleBuffers();
    void updateBuffers();
    void updateSimpleBuffers();
    void updateUniforms();
    void updateSimpleUniforms();

    void renderSimpleObjects(bool uniformUpdateRequired);
    void renderWorld();

    // Shader programs
    QOpenGLShaderProgram *simpleShaderProgram;

    // Vertex array objects
    GLuint worldVAO;
    // Buffer objects
    GLuint coordinatesBO, normalsBO;
    // IBO
    unsigned int worldIBOsize;
};

#endif // RENDERER_H
