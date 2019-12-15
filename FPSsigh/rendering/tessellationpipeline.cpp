#include "rendering/renderer.h"

void Renderer::createTessShaderProgram() {
    tessShaderProgram = new QOpenGLShaderProgram();
    tessShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tess/rendering/shaders/tess_vs.glsl");
    tessShaderProgram->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/tess/rendering/shaders/tess_tcs.glsl");
    tessShaderProgram->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/tess/rendering/shaders/tess_tes.glsl");
    tessShaderProgram->addShaderFromSourceFile(QOpenGLShader::Geometry, ":/tess/rendering/shaders/tess_geo.glsl");
    tessShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tess/rendering/shaders/fs.glsl");

    tessShaderProgram->link();
}

void Renderer::createTessBuffers() {
    glGenVertexArrays(1, &tessVAO);
    glBindVertexArray(tessVAO);

    glGenBuffers(1, &tessCoordinatesBO);
    glBindBuffer(GL_ARRAY_BUFFER, tessCoordinatesBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &tessNormalsBO);
    glBindBuffer(GL_ARRAY_BUFFER, tessNormalsBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &tessModeBO);
    glBindBuffer(GL_ARRAY_BUFFER, tessModeBO);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    glBindVertexArray(0);
}

void Renderer::updateTessBuffers() {
    QVector<QVector3D> vertices = QVector<QVector3D>();
    QVector<QVector3D> normals = QVector<QVector3D>();
    QVector<unsigned int> mode = QVector<unsigned int>();

    gameWorld->getTessWorldObjects(vertices, normals, mode);

    glBindBuffer(GL_ARRAY_BUFFER, tessCoordinatesBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, tessNormalsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*normals.size(), normals.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, tessModeBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int)*mode.size(), mode.data(), GL_DYNAMIC_DRAW);

    tessIBOsize = vertices.size();
}

void Renderer::updateTessUniforms() {
    tessShaderProgram->setUniformValue("object_color_default", QVector3D(0, 0, 1));
    tessShaderProgram->setUniformValue("modelviewmatrix", gameCharacter->modelViewMatrix);
    tessShaderProgram->setUniformValue("projectionmatrix", gameCharacter->projectionMatrix);
    tessShaderProgram->setUniformValue("normalmatrix", gameCharacter->normalMatrix);
    tessShaderProgram->setUniformValue("tessellation_inner", tessellationInner);
    tessShaderProgram->setUniformValue("tessellation_outer", tessellationOuter);
    simpleShaderProgram->setUniformValue("player_position", gameCharacter->position);
    simpleShaderProgram->setUniformValue("scale", scale);
}

void Renderer::renderQuads(bool uniformUpdateRequired) {
    tessShaderProgram->bind();

    if (uniformUpdateRequired) {
        updateTessUniforms();
        uniformUpdateRequired = false;
    }

    glBindVertexArray(tessVAO);
    glDrawArrays(GL_PATCHES, 0, tessIBOsize);

    glBindVertexArray(0);

    tessShaderProgram->release();
}
