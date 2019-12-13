#version 410 core

layout(quads, equal_spacing, ccw) in;

layout (location = 0) in vec3 vertcoords_world_tes[];
layout (location = 1) in vec3 vertnormal_world_tes[];

layout (location = 1) out vec3 vertnormal_world_fs;


vec3 interpolate(vec3 v0, vec3 v1, float w) {
    return v0 + (v1-v0) * w;
}

vec3 interpolate2D(vec3 v0, vec3 v1, vec3 v2, vec3 v3, float w1, float w2) {
    vec3 p1 = interpolate(v0, v1, w1);
    vec3 p2 = interpolate(v3, v2, w2);
    return interpolate(p1, p2, w2);
}

void main()
{
    vec3 v0 = vertcoords_world_tes[0];
    vec3 v1 = vertcoords_world_tes[1];
    vec3 v2 = vertcoords_world_tes[2];
    vec3 v3 = vertcoords_world_tes[3];

    vec3 p1 = mix(v1, v0, gl_TessCoord.x);
    vec3 p2 = mix(v2, v3, gl_TessCoord.x);
    gl_Position = vec4(mix(p1, p2, gl_TessCoord.y), 1);


    v0 = vertnormal_world_tes[0];
    v1 = vertnormal_world_tes[1];
    v2 = vertnormal_world_tes[2];
    v3 = vertnormal_world_tes[3];

    p1 = mix(v1, v0, gl_TessCoord.x);
    p2 = mix(v2, v3, gl_TessCoord.x);
    vertnormal_world_fs = mix(p1, p2, gl_TessCoord.y);

}
