#version 410
// Fragment shader

uniform vec3 object_color_default;

layout (location = 0) in vec3 vertcoords_world_fs;
layout (location = 1) in vec3 vertnormal_world_fs;

out vec4 fColor;

void main() {
    if (vertnormal_world_fs == vec3(0, 0, 0)) {
        fColor = vec4(object_color_default, 1.0);
    } else {
        fColor = vec4(dot(vec3(1, 0, 0), vertnormal_world_fs),
                      dot(vec3(0, 1, 0), vertnormal_world_fs),
                      dot(vec3(0, 0, 1), vertnormal_world_fs),
                      1);
    }
}
