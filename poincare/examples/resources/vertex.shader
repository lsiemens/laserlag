#version 330 core
layout (location = 0) in vec2 position_2d;
out vec4 vertexColor;

void main() {
    gl_Position = vec4(position_2d, 0, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}
