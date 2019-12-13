#version 410
// Fragment shader

uniform vec3 object_color_default;

out vec4 fColor;

void main() {
    fColor = vec4(object_color_default, 1.0);
}
