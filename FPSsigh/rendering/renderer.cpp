#include "renderer.h"
#include <QVector>
#include <QVector3D>
Renderer::Renderer()
{
    qDebug() << "Renderer constructor";
    uniformUpdateRequired = true;
    gameWorld = new World();
    gameCharacter = new Character();

    scale = 10;

    initializeOpenGLFunctions();

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    GLint MaxPatchVertices = 0;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
    qDebug() << "Maximum patch vertices:" << MaxPatchVertices;
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    createShaderPrograms();
    createBuffers();
}

Renderer::~Renderer()
{
    qDebug() << "Renderer destructor";
    glDeleteBuffers(1, &coordinatesBO);
    glDeleteBuffers(1, &normalsBO);

    delete simpleShaderProgram;
}

void Renderer::createShaderPrograms() {
    createSimpleShaderProgram();
}

void Renderer::createBuffers() {
    createSimpleBuffers();
}

void Renderer::updateBuffers() {
    updateSimpleBuffers();
}

void Renderer::updateUniforms() {
    updateSimpleUniforms();
}

void Renderer::render() {
    updateBuffers();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderSimpleObjects(uniformUpdateRequired);
}
