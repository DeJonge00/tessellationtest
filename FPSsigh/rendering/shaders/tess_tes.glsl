#version 410 core

layout(quads, equal_spacing, ccw) in;
// Order =
//  2  3  5  6
//  1  0  4  7
// 15 12  8  9
// 14 13 11 10
layout (location = 0) in vec3 vertcoords_tes[];
layout (location = 1) in vec3 vertnormal_tes[];
layout (location = 2) in uint vertmode_tes[];

out vec3 vertnormal_geo;
out uint vertmode_geo;

uniform int tessellation_inner;
uniform int tessellation_outer;

struct Point
{
    vec3 pos;
    vec3 nor;
};

vec3 interpolate(vec3 v0, vec3 v1, float w) {
    return v0 + (v1-v0) * w;
}

vec3 interpolate2D(vec3 v0, vec3 v1, vec3 v2, vec3 v3, float w1, float w2) {
    vec3 p1 = interpolate(v0, v1, w1);
    vec3 p2 = interpolate(v3, v2, w2);
    return interpolate(p1, p2, w2);
}

// ---

Point cubicInterpolate (Point p0, Point p1, float x) {
        vec3 a = 2*p0.pos - 2*p1.pos + p0.nor + p1.nor;
        vec3 b = -3*p0.pos + 3*p1.pos - 2*p0.nor - p1.nor;
        vec3 c = p0.nor;
        vec3 d = p0.pos;
        vec3 pr = a*x*x*x + b*x*x + c*x + d;
        vec3 dr = 3*a*x*x + 2*b*x + c;
        return Point(pr, dr);
}


Point bicubicInterpolate (Point p00, Point p01, Point p10, Point p11, float x, float y) {
    Point p0 = cubicInterpolate(p00, p01, x);
    Point p1 = cubicInterpolate(p11, p10, x);
    return cubicInterpolate(p0, p1, y);
}

// ---

void main()
{
    int mode = 1;
    vec3 v0 = vertcoords_tes[0];
    vec3 v1 = vertcoords_tes[1];
    vec3 v2 = vertcoords_tes[2];
    vec3 v3 = vertcoords_tes[3];

    vec3 n0 = vertnormal_tes[0];
    vec3 n1 = vertnormal_tes[1];
    vec3 n2 = vertnormal_tes[2];
    vec3 n3 = vertnormal_tes[3];

    float x = gl_TessCoord.x;
    float y = gl_TessCoord.y;

    if (mode == 1) {
        // Bicubic interpolation
        Point p = bicubicInterpolate(Point(v0, n0), Point(v1, n1), Point(v2, n2), Point(v3, n3), y, x);
        gl_Position = vec4(p.pos, 1);
        vertnormal_geo = p.nor;
    } else {
        // Bilinear interpolation
        vec3 p1 = mix(v1, v0, x);
        vec3 p2 = mix(v2, v3, x);
        gl_Position = vec4(mix(p1, p2, y), 1);

        p1 = mix(n1, n0, x);
        p2 = mix(n2, n3, x);
        vec3 pr = mix(p1, p2, y);
        vertnormal_geo = pr;
    }
    vertmode_geo = vertmode_tes[0];
}
