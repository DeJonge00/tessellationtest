#version 410
// Vertex shader

layout (location = 0) in vec3 vertcoords_world_vs;
layout (location = 1) in vec3 vertnormal_world_vs;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;
uniform float scale;

layout (location = 0) out vec3 vertcoords_camera_tcs;
layout (location = 1) out vec3 vertnormal_camera_tcs;

void main() {
//    vertcoords_camera_tcs = vec3(modelviewmatrix * vec4(scale * vertcoords_world_vs, 1.0));
//    vertnormal_camera_tcs = normalize(normalmatrix * vertnormal_world_vs);
    vertcoords_camera_tcs = scale * vertcoords_world_vs;
    vertnormal_camera_tcs = normalize(vertnormal_world_vs);
}
