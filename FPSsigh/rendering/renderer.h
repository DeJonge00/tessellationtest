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
    float scale;
    bool uniformUpdateRequired;

    void render();
    bool enableSimpleShader;
    bool enableTessShader;

    int tessellationInner;
    int tessellationOuter;

private:
    void createShaderPrograms();
    void createSimpleShaderProgram();
    void createTessShaderProgram();

    void createBuffers();
    void createSimpleBuffers();
    void createTessBuffers();

    void updateBuffers();
    void updateSimpleBuffers();
    void updateTessBuffers();

    void updateUniforms();
    void updateSimpleUniforms();
    void updateTessUniforms();

    void renderSimpleObjects(bool uniformUpdateRequired);
    void renderQuads(bool uniformUpdateRequired);
    void renderWorld();

    // Simple shader program
    QOpenGLShaderProgram *simpleShaderProgram;
    GLuint simpleVAO;
    GLuint simpleCoordinatesBO, simpleNormalsBO;
    unsigned int simpleIBOsize;

    // Tessellation shader program
    QOpenGLShaderProgram *tessShaderProgram;
    GLuint tessVAO;
    GLuint tessCoordinatesBO, tessNormalsBO;
    unsigned int tessIBOsize;
};

#endif // RENDERER_H
