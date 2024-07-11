#version 330 core
layout (location = 0) in vec2 vsprite_position;
layout (location = 1) in vec3 vsprite_color;

out vec4 vertexColor;

uniform vec3 position;
uniform vec3 velocity;

void main() {
    gl_Position = vec4(position.yz + vsprite_position, 0, 1.0);
    vertexColor = vec4(vsprite_color, 1.0);
}
