#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_vs;
layout (location = 1) in vec3 vertnormal_vs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;
uniform float scale;
uniform vec3 translation;

uniform int phase_type;
uniform float phase;
uniform float phase_strength;

layout (location = 0) out vec3 vertcoords_tcs;
layout (location = 1) out vec3 vertnormal_tcs;

#define PI 3.14159265358979

void main() {
    vec3 coord = vertcoords_vs;
    if (phase_type == 2) {
        coord += phase_strength * vec3(0, sin(phase * 2 * PI), 0);
    }
    vertcoords_tcs = scale * (translation + coord);
    vertnormal_tcs = normalize(vertnormal_vs);
}
