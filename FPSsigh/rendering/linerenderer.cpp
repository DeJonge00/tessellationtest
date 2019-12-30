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
    updateLineBuffers(wo->getNormals());
}

void Renderer::updateLineBuffers(QVector<QVector3D> vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, lineCoordinatesBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    lineIBOsize = vertices.size();
}

void Renderer::updateLineUniforms(WorldObject *wo) {
    updateLineUniforms();
    lineShaderProgram->setUniformValue("rotation", wo->rotation);
    lineShaderProgram->setUniformValue("translation", wo->translation);
}

void Renderer::updateLineUniforms() {
    lineShaderProgram->setUniformValue("modelviewmatrix", gameCharacter->modelViewMatrix);
    lineShaderProgram->setUniformValue("projectionmatrix", gameCharacter->projectionMatrix);
    lineShaderProgram->setUniformValue("normalmatrix", gameCharacter->normalMatrix);
    lineShaderProgram->setUniformValue("object_color_default", QVector3D(1, 1, 1));
    lineShaderProgram->setUniformValue("scale", scale);
    lineShaderProgram->setUniformValue("phase_type", 0);
}

void Renderer::renderNormals(QVector<Chunk *> chunks) {
    lineShaderProgram->bind();

    glBindVertexArray(lineVAO);
    for (Chunk* c : chunks) {
        for (WorldObject* wo : c->getObjects()) {
            updateLineBuffers(wo);
            updateLineUniforms(wo);

            glDrawArrays(GL_LINES, 0, lineIBOsize);
        }
    }
    glBindVertexArray(0);
    lineShaderProgram->release();
}

void Renderer::renderChunkBoundary(QVector<Chunk *> chunks) {
    lineShaderProgram->bind();

    glBindVertexArray(lineVAO);
    for (Chunk* c : chunks) {
        updateLineBuffers(c->getVisualBoundary(gameCharacter->position.y()));
        updateLineUniforms();
        lineShaderProgram->setUniformValue("rotation", QVector3D(0, 0, 0));
        lineShaderProgram->setUniformValue("translation", c->getOrigin());

        glDrawArrays(GL_LINES, 0, lineIBOsize);
    }
    glBindVertexArray(0);
    lineShaderProgram->release();
}
