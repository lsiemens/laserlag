#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

in vec4 vertex_color[];
out vec4 geometry_color;

uniform mat4 camera_transform;

void main() {
    vec4 X = vec4(1, 0, 0, 0);
    vec4 Y = vec4(0, 1, 0, 0);
    vec4 Z = vec4(0, 0, 1, 0);

    geometry_color = vec4(0,0,0,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position - Z);
    EmitVertex();

    geometry_color = vec4(1,0,0,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position + X);
    EmitVertex();

    geometry_color = vec4(0,1,0,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position + Y);
    EmitVertex();

    geometry_color = vec4(1,1,1,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position + Z);
    EmitVertex();

    geometry_color = vec4(1,0,1,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position - X);
    EmitVertex();

    geometry_color = vec4(0,1,1,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position - Y);
    EmitVertex();
    EndPrimitive();


    geometry_color = vec4(1,1,1,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position + Z);
    EmitVertex();

    geometry_color = vec4(1,0,0,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position + X);
    EmitVertex();

    geometry_color = vec4(0,1,1,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position - Y);
    EmitVertex();

    geometry_color = vec4(0,0,0,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position - Z);
    EmitVertex();

    geometry_color = vec4(1,0,1,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position - X);
    EmitVertex();

    geometry_color = vec4(0,1,0,1);
    gl_Position = camera_transform*(gl_in[0].gl_Position + Y);
    EmitVertex();
    EndPrimitive();
}
