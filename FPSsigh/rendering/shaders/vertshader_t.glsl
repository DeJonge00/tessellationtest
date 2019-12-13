#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_world_vs;
layout (location = 1) in vec3 vertnormal_world_vs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;
uniform int scale;

layout (location = 0) out vec3 vertcoords_camera_vs;
layout (location = 1) out vec3 vertnormal_camera_vs;

void main() {
    gl_Position = projectionmatrix * modelviewmatrix * vec4(vertcoords_world_vs, 1.0);
//    gl_Position = vec4(vertcoords_world_vs, 1.0);
    gl_Position.x *= 0.1*scale;

    vertcoords_camera_vs = vec3(modelviewmatrix * vec4(vertcoords_world_vs, 1.0));
    vertnormal_camera_vs = normalize(normalmatrix * vertnormal_world_vs);
}
