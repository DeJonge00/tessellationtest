#version 410
// Fragment shader

layout (location = 0) in vec3 vertcoords_camera_fs;
layout (location = 1) in vec3 vertnormal_camera_fs;

uniform vec3 object_color_default;

out vec4 fColor;

void main() {
    fColor = vec4(object_color_default, 1.0);
}
