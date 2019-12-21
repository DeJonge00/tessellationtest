#version 410
// Fragment shader

uniform vec3 object_color_default;

layout (location = 0) in vec3 vertcoords_fs;
layout (location = 1) in vec3 vertnormal_fs;

uniform vec3 player_position;
uniform int mode;

out vec4 fColor;

void main() {
    if (mode == 1) { // 1065353216
        fColor = vec4(dot(vec3(1, 0, 0), vertnormal_fs),
                      dot(vec3(0, 1, 0), vertnormal_fs),
                      dot(vec3(0, 0, 1), vertnormal_fs),
                      1);
    } else if (mode == 2) { // 1073741824
        fColor = vec4(dot(player_position, vertnormal_fs), 0, 0, 1);
    } else {
        fColor = vec4(object_color_default, 1.0);
    }
}
