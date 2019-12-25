#include "rendering/renderer.h"

void Renderer::createTessShaderProgram() {
    tessShaderProgram = new QOpenGLShaderProgram();
    tessShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simple/rendering/shaders/simple_vs.glsl");
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

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    glBindVertexArray(0);
}

void Renderer::updateTessBuffers(WorldObject* wo) {
    QVector<QVector3D> vertices = wo->getTessVertices();
    QVector<QVector3D> normals = wo->getTessNormals();

    glBindBuffer(GL_ARRAY_BUFFER, tessCoordinatesBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, tessNormalsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*normals.size(), normals.data(), GL_DYNAMIC_DRAW);

    tessIBOsize = vertices.size();
}

void Renderer::updateTessUniforms(WorldObject* wo) {
    tessShaderProgram->setUniformValue("object_color_default", QVector3D(0, 0, 1));
    tessShaderProgram->setUniformValue("modelviewmatrix", gameCharacter->modelViewMatrix);
    tessShaderProgram->setUniformValue("projectionmatrix", gameCharacter->projectionMatrix);
    tessShaderProgram->setUniformValue("normalmatrix", gameCharacter->normalMatrix);
    tessShaderProgram->setUniformValue("tessellation_inner", tessellationInner);
    tessShaderProgram->setUniformValue("tessellation_outer", tessellationOuter);
    tessShaderProgram->setUniformValue("player_position", gameCharacter->position);
    tessShaderProgram->setUniformValue("bicubic", bicubicInterpolation);
    tessShaderProgram->setUniformValue("scale", scale);
    tessShaderProgram->setUniformValue("mode", wo->mode);
    tessShaderProgram->setUniformValue("translation", wo->translation);
    tessShaderProgram->setUniformValue("phase_type", wo->phaseType);
    if (wo->phaseType != 0) {
        tessShaderProgram->setUniformValue("phase", wo->phase);
        tessShaderProgram->setUniformValue("phase_strength", wo->phaseStrength);
    }
}

void Renderer::renderQuads(bool uniformUpdateRequired) {
    tessShaderProgram->bind();

    glBindVertexArray(tessVAO);
    for (WorldObject* wo : gameWorld->worldObjects) {
        updateTessBuffers(wo);
        updateTessUniforms(wo);

        if (tessWireframeMode) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        } else {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
        }
        glDrawArrays(GL_PATCHES, 0, tessIBOsize);
    }
    glBindVertexArray(0);
    tessShaderProgram->release();
}
