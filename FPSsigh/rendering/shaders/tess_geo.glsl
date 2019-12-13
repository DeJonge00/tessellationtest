#version 410

layout(triangles) in;
in vec3 vertnormal_world_geo[];

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;

layout(triangle_strip, max_vertices = 3) out;
layout (location = 1) out vec3 vertnormal_world_fs;

void main() {
    for (int i = 0; i < gl_in.length(); i++) {
        vec4 p = gl_in[i].gl_Position;
        gl_Position = projectionmatrix * modelviewmatrix * p;
        vertnormal_world_fs = vertnormal_world_geo[i];
        EmitVertex();
    }

    EndPrimitive();
}
