#include "rendering/renderer.h"

void Renderer::createSimpleShaderProgram() {
    simpleShaderProgram = new QOpenGLShaderProgram();
    simpleShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simple/rendering/shaders/simple_vs.glsl");
    simpleShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simple/rendering/shaders/simple_fs.glsl");

    simpleShaderProgram->link();
}

void Renderer::createSimpleBuffers() {
    glGenVertexArrays(1, &simpleVAO);
    glBindVertexArray(simpleVAO);

    glGenBuffers(1, &simpleCoordinatesBO);
    glBindBuffer(GL_ARRAY_BUFFER, simpleCoordinatesBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &simpleNormalsBO);
    glBindBuffer(GL_ARRAY_BUFFER, simpleNormalsBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void Renderer::updateSimpleBuffers() {
    QVector<QVector3D> vertices = QVector<QVector3D>();
    QVector<QVector3D> normals = QVector<QVector3D>();

    gameWorld->getSimpleWorldObjects(vertices, normals);

    glBindBuffer(GL_ARRAY_BUFFER, simpleCoordinatesBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, simpleNormalsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*normals.size(), normals.data(), GL_DYNAMIC_DRAW);

    simpleIBOsize = vertices.size();
}

void Renderer::updateSimpleUniforms() {
    simpleShaderProgram->setUniformValue("object_color_default", QVector3D(25.0/255.0, 104.0/255.0, 16.0/255.0));
    simpleShaderProgram->setUniformValue("modelviewmatrix", gameCharacter->modelViewMatrix);
    simpleShaderProgram->setUniformValue("projectionmatrix", gameCharacter->projectionMatrix);
    simpleShaderProgram->setUniformValue("normalmatrix", gameCharacter->normalMatrix);
    simpleShaderProgram->setUniformValue("scale", scale);
}

void Renderer::renderSimpleObjects(bool uniformUpdateRequired) {
    simpleShaderProgram->bind();

    if (uniformUpdateRequired) {
        updateSimpleUniforms();
        uniformUpdateRequired = false;
    }

    glBindVertexArray(simpleVAO);
    // Draw triangles
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, simpleIBOsize);

    // Draw vertices
    if (false) {
        glPointSize(12.0);
        glDrawArrays(GL_POINTS, 0, simpleIBOsize);
    }

    glBindVertexArray(0);

    simpleShaderProgram->release();
}
