#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QVector>
#include <QVector3D>

#include "logic/world.h"
#include "logic/character.h"
#include "logic/fpscounter.h"


class Renderer: protected QOpenGLFunctions_4_1_Core
{
public:
    Renderer();
    ~Renderer();
    bool running;

    World *gameWorld;
    Character *gameCharacter;
    float scale;
    bool uniformUpdateRequired;

    void render();
    bool enableSimpleShader;
    bool enableTessShader;

    int tessellationInner;
    int tessellationOuter;

    bool simpleWireframeMode;
    bool tessWireframeMode;

    bool bicubicInterpolation;

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
    GLuint simpleCoordinatesBO, simpleNormalsBO, simpleModeBO;
    unsigned int simpleIBOsize;

    // Tessellation shader program
    QOpenGLShaderProgram *tessShaderProgram;
    GLuint tessVAO;
    GLuint tessCoordinatesBO, tessNormalsBO, tessModeBO;
    unsigned int tessIBOsize;
};

#endif // RENDERER_H
