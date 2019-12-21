#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_vs;
layout (location = 1) in vec3 vertnormal_vs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;
uniform float scale;
uniform vec3 translation;

layout (location = 0) out vec3 vertcoords_tcs;
layout (location = 1) out vec3 vertnormal_tcs;

void main() {
    vertcoords_tcs = scale * (translation + vertcoords_vs);
    vertnormal_tcs = normalize(vertnormal_vs);
}
