#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_vs;
layout (location = 1) in vec3 vertnormal_vs;
layout (location = 2) in uint vertmode_vs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;
uniform float scale;

layout (location = 0) out vec3 vertcoords_fs;
layout (location = 1) out vec3 vertnormal_fs;
layout (location = 2) flat out uint vertmode_fs;


void main() {
    vertcoords_fs = vertcoords_vs;
    vertnormal_fs = vertnormal_vs;
    vertmode_fs = vertmode_vs;
    gl_Position = projectionmatrix * modelviewmatrix * vec4(scale * vertcoords_vs, 1.0);
}
