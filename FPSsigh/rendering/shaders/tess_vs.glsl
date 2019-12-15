#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_vs;
layout (location = 1) in vec3 vertnormal_vs;
layout (location = 2) in uint vertmode_vs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;
uniform float scale;

layout (location = 0) out vec3 vertcoords_tcs;
layout (location = 1) out vec3 vertnormal_tcs;
layout (location = 2) out uint vertmode_tcs;

void main() {
    vertcoords_tcs = scale * vertcoords_vs;
    vertnormal_tcs = normalize(vertnormal_vs);
    vertmode_tcs = vertmode_vs;
}
