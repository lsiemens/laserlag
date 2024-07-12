#version 330 core

#define MAX_VERTICES 63 // Must be odd

layout (triangles) in;
layout (triangle_strip, max_vertices = MAX_VERTICES) out;

in vec4 vertex_color[];
out vec4 geometry_color;

uniform mat4 camera_transform;

vec4 colors(float theta) {
    float phase = 6.28318/3;

    return vec4(0.5*(1 + cos(theta)), 0.5*(1 + cos(theta + phase)), 0.5*(1 + cos(theta + 2*phase)), 0.5);
}

vec4 offset(float theta, float height) {
    return height*vec4(cos(theta), sin(theta), -1, 0);
}

void main() {
    int iterations = (MAX_VERTICES + 1)/2;
    float height = gl_in[0].gl_Position.z;
    float dtheta = 6.28318/(iterations - 1);

    geometry_color = vertex_color[0];
    gl_Position = camera_transform*gl_in[0].gl_Position;
    EmitVertex();
    geometry_color = colors(0);
    gl_Position = camera_transform*(gl_in[0].gl_Position + offset(0, height));
    EmitVertex();
    geometry_color = colors(dtheta);
    gl_Position = camera_transform*(gl_in[0].gl_Position + offset(dtheta, height));
    EmitVertex();

    float theta = 0;
    for (int i=2; i<iterations; i++) {
        theta = i*dtheta;
        geometry_color = vertex_color[0];
        gl_Position = camera_transform*(gl_in[0].gl_Position);
        EmitVertex();
        geometry_color = colors(theta);
        gl_Position = camera_transform*(gl_in[0].gl_Position + offset(theta, height));
        EmitVertex();

    }
    EndPrimitive();
}
