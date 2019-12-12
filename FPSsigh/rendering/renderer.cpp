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

    delete mainShaderProgram;
}

void Renderer::createShaderPrograms() {
    mainShaderProgram = new QOpenGLShaderProgram();
    mainShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/rendering/shaders/vertshader_t.glsl");
//    mainShaderProgram->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/rendering/shaders/tcs.glsl");
//    mainShaderProgram->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/rendering/shaders/tes.glsl");
    mainShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/rendering/shaders/fragshader.glsl");

    mainShaderProgram->link();
}

void Renderer::createBuffers() {
    glGenVertexArrays(1, &worldVAO);
    glBindVertexArray(worldVAO);

    glGenBuffers(1, &coordinatesBO);
    glBindBuffer(GL_ARRAY_BUFFER, coordinatesBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &normalsBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void Renderer::updateBuffers() {

    QVector<QVector3D> vertices = QVector<QVector3D>();
    QVector<QVector3D> normals = QVector<QVector3D>();

    gameWorld->getWorldObjects(vertices, normals);
    qDebug() << "updateBuffers:" << vertices.first() << normals.first();

    glBindBuffer(GL_ARRAY_BUFFER, coordinatesBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*normals.size(), normals.data(), GL_DYNAMIC_DRAW);

    worldIBOsize = vertices.size();
}

void Renderer::updateUniforms(QOpenGLShaderProgram *shaderProgram) {
    // update matrices
    for (int i = 0; i < 9; i++) {
        qDebug() << gameCharacter->modelViewMatrix.data()[i];
    }
    shaderProgram->setUniformValue("modelviewmatrix", gameCharacter->modelViewMatrix);
    shaderProgram->setUniformValue("projectionmatrix", gameCharacter->projectionMatrix);
    shaderProgram->setUniformValue("normalmatrix", gameCharacter->normalMatrix);
    shaderProgram->setUniformValue("scale", scale);
}

void Renderer::render() {
    updateBuffers();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainShaderProgram->bind();

    if (uniformUpdateRequired) {
        updateUniforms(mainShaderProgram);
        uniformUpdateRequired = false;
    }

    renderWorld();

    mainShaderProgram->release();
}

void Renderer::renderWorld() {
    glBindVertexArray(worldVAO);
    glPointSize(12.0);
    glDrawArrays(GL_LINES, 0, worldIBOsize);

    glBindVertexArray(0);
}
