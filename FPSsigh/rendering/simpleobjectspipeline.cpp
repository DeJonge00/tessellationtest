#include "rendering/renderer.h"

void Renderer::createSimpleShaderProgram() {
    simpleShaderProgram = new QOpenGLShaderProgram();
    simpleShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/rendering/shaders/vertshader_t.glsl");
    simpleShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/rendering/shaders/fragshader.glsl");

    simpleShaderProgram->link();
}

void Renderer::createSimpleBuffers() {
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

void Renderer::updateSimpleBuffers() {
    QVector<QVector3D> vertices = QVector<QVector3D>();
    QVector<QVector3D> normals = QVector<QVector3D>();

    gameWorld->getWorldObjects(vertices, normals);

    glBindBuffer(GL_ARRAY_BUFFER, coordinatesBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*normals.size(), normals.data(), GL_DYNAMIC_DRAW);

    worldIBOsize = vertices.size();
}

void Renderer::updateSimpleUniforms() {
    simpleShaderProgram->setUniformValue("modelviewmatrix", gameCharacter->modelViewMatrix);
    simpleShaderProgram->setUniformValue("projectionmatrix", gameCharacter->projectionMatrix);
    simpleShaderProgram->setUniformValue("normalmatrix", gameCharacter->normalMatrix);
    simpleShaderProgram->setUniformValue("scale", scale);
}

void Renderer::renderSimpleObjects(bool uniformUpdateRequired) {
    simpleShaderProgram->bind();

    if (uniformUpdateRequired) {
        updateUniforms();
        uniformUpdateRequired = false;
    }

    glBindVertexArray(worldVAO);
    glDrawArrays(GL_LINES, 0, worldIBOsize);
    glPointSize(12.0);
    glDrawArrays(GL_POINTS, 0, worldIBOsize);

    glBindVertexArray(0);

    simpleShaderProgram->release();
}
