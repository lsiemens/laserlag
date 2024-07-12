#version 330 core
out vec4 fragment_color;
in vec4 geometry_color;

void main() {
    fragment_color = geometry_color;
}
