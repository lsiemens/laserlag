#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 128) out;
//layout (points, max_vertices = 200) out;

in vec4 vertex_color[];
out vec4 geometry_color;

uniform vec3 position;
uniform mat4 camera_transform;
uniform vec3 world_line[128];

void main() {
    float height = position.z;

    for (int i=0; i < gl_in.length(); i++) {
        for (int j=0; j<128; j++) {
            geometry_color = vertex_color[i];
            gl_Position = camera_transform*(gl_in[i].gl_Position + vec4(world_line[j], 0));
            EmitVertex();
        }
        EndPrimitive();
    }
}
