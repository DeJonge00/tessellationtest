#include "renderer.h"
#include <QVector>
#include <QVector3D>

Renderer::Renderer()
    : uniformUpdateRequired(true),
      gameWorld(new World()),
      gameCharacter(new Character()),
      scale(1.0),
      enableSimpleShader(true),
      enableTessShader(true),
      tessellationInner(1),
      tessellationOuter(2)
{
    qDebug() << "Renderer constructor";

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

    createShaderPrograms();
    createBuffers();
}

Renderer::~Renderer()
{
    qDebug() << "Renderer destructor";
    glDeleteBuffers(1, &simpleCoordinatesBO);
    glDeleteBuffers(1, &simpleNormalsBO);

    delete simpleShaderProgram;

    glDeleteBuffers(1, &tessCoordinatesBO);
    glDeleteBuffers(1, &tessNormalsBO);

    delete tessShaderProgram;
}

void Renderer::createShaderPrograms() {
    createSimpleShaderProgram();
    createTessShaderProgram();
}

void Renderer::createBuffers() {
    createSimpleBuffers();
    createTessBuffers();
}

void Renderer::updateBuffers() {
    if (enableSimpleShader) { updateSimpleBuffers(); }
    if (enableTessShader) { updateTessBuffers(); }
}

void Renderer::render() {
    updateBuffers();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (enableSimpleShader) { renderSimpleObjects(uniformUpdateRequired); }
    if (enableTessShader) { renderQuads(uniformUpdateRequired); }
}
