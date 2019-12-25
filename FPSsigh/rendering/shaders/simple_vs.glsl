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

layout (location = 0) out vec3 vertcoords_fs;
layout (location = 1) out vec3 vertnormal_fs;

#define PI 3.14159265358979

void main() {
    vec3 coord = vertcoords_vs;
    if (phase_type == 1) { // Beating / breathing
        float l = 2;
        if (phase < (1/l)) {
            coord += phase_strength * sin(phase * l*2*PI) * normalize(coord);
        }
    } else if (phase_type == 2) { // Hovering / slow up-down motion
        coord += phase_strength * vec3(0, sin(phase * 2*PI), 0);
    }
    vertcoords_fs = translation + coord;
    vertnormal_fs = vertnormal_vs;
    gl_Position = projectionmatrix * modelviewmatrix * vec4(scale * vertcoords_fs, 1.0);
}
