#version 330 core
layout (location = 0) in vec2 vsprite_position;
layout (location = 1) in vec3 vsprite_color;

out vec4 vertexColor;

uniform vec3 position;
uniform vec3 velocity;

uniform mat4 camera_transform;

void main() {
    gl_Position = camera_transform*(vec4(position, 1.0) + vec4(vsprite_position, 0, 1.0));
    vertexColor = vec4(vsprite_color, 1.0);
}
