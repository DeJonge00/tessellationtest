#version 410
// Vertex shader

layout(triangles) in;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;

layout(line_strip, max_vertices = 3) out;

void main() {
    for (int i = 0; i < gl_in.length(); i++) {
        vec4 p = gl_in[i].gl_Position;
        gl_Position = projectionmatrix * modelviewmatrix * p;
        EmitVertex();
    }

//    vec4 p = gl_in[0].gl_Position;
//    gl_Position = projectionmatrix * modelviewmatrix * p;
//    EmitVertex();

    EndPrimitive();
}
