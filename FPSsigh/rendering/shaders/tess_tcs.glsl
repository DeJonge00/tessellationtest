#version 410 core

layout (vertices = 4) out;

layout (location = 0) in vec3 vertcoords_world_tcs[];
layout (location = 1) in vec3 vertnormal_world_tcs[];

uniform int tessellation_inner;
uniform int tessellation_outer;

layout (location = 0) out vec3 vertcoords_world_tes[];
layout (location = 1) out vec3 vertnormal_world_tes[];


void main()
{
    if (gl_InvocationID == 0) {
        gl_TessLevelOuter[0] = tessellation_inner;
        gl_TessLevelOuter[1] = tessellation_inner;
        gl_TessLevelOuter[2] = tessellation_inner;
        gl_TessLevelOuter[3] = tessellation_inner;

        gl_TessLevelInner[0] = tessellation_outer;
        gl_TessLevelInner[1] = tessellation_outer;
    }

    vertcoords_world_tes[gl_InvocationID] = vertcoords_world_tcs[gl_InvocationID];
    vertnormal_world_tes[gl_InvocationID] = vertnormal_world_tcs[gl_InvocationID];
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
