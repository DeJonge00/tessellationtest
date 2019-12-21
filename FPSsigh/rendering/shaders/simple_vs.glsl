#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_vs;
layout (location = 1) in vec3 vertnormal_vs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;
uniform float scale;
uniform vec3 translation;

layout (location = 0) out vec3 vertcoords_fs;
layout (location = 1) out vec3 vertnormal_fs;


void main() {
    vertcoords_fs = translation + vertcoords_vs;
    vertnormal_fs = vertnormal_vs;
    gl_Position = projectionmatrix * modelviewmatrix * vec4(scale * vertcoords_fs, 1.0);
}
