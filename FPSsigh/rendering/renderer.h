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
    bool enableLineShader;
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
    void createLineShaderProgram();

    void createBuffers();
    void createSimpleBuffers();
    void createTessBuffers();
    void createLineBuffers();

    void updateSimpleBuffers(WorldObject* wo);
    void updateTessBuffers(WorldObject* wo);
    void updateLineBuffers(WorldObject* wo);

    void updateSimpleUniforms(WorldObject* wo);
    void updateTessUniforms(WorldObject* wo);
    void updateLineUniforms(WorldObject* wo);

    void renderSimpleObjects();
    void renderQuads();
    void renderNormals();
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

    // Tessellation shader program
    QOpenGLShaderProgram *lineShaderProgram;
    GLuint lineVAO;
    GLuint lineCoordinatesBO;
    unsigned int lineIBOsize;
};

#endif // RENDERER_H
