#include "rendering/renderer.h"

void Renderer::createLineShaderProgram() {
    lineShaderProgram = new QOpenGLShaderProgram();
    lineShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simple/rendering/shaders/vs.glsl");
    lineShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simple/rendering/shaders/fs.glsl");
    lineShaderProgram->link();
}

void Renderer::createLineBuffers() {
    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);

    glGenBuffers(1, &lineCoordinatesBO);
    glBindBuffer(GL_ARRAY_BUFFER, lineCoordinatesBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void Renderer::updateLineBuffers(WorldObject *wo) {
    QVector<QVector3D> vertices = wo->getNormals();

    glBindBuffer(GL_ARRAY_BUFFER, lineCoordinatesBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    lineIBOsize = vertices.size();
}

void Renderer::updateLineUniforms(WorldObject *wo) {
    lineShaderProgram->setUniformValue("modelviewmatrix", gameCharacter->modelViewMatrix);
    lineShaderProgram->setUniformValue("projectionmatrix", gameCharacter->projectionMatrix);
    lineShaderProgram->setUniformValue("normalmatrix", gameCharacter->normalMatrix);
    lineShaderProgram->setUniformValue("object_color_default", QVector3D(1, 1, 1));
    lineShaderProgram->setUniformValue("scale", scale);
    lineShaderProgram->setUniformValue("phase_type", 0);
    lineShaderProgram->setUniformValue("rotation", wo->rotation);
    lineShaderProgram->setUniformValue("translation", wo->translation);
}

void Renderer::renderNormals() {
    lineShaderProgram->bind();

    glBindVertexArray(lineVAO);
    for (WorldObject* wo : gameWorld->worldObjects) {
        updateLineBuffers(wo);
        updateLineUniforms(wo);

        glDrawArrays(GL_LINES, 0, lineIBOsize);
    }
    glBindVertexArray(0);
    lineShaderProgram->release();
}

