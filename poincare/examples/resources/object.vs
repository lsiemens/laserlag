#version 330 core
layout (location = 0) in vec2 vsprite_position;
layout (location = 1) in vec3 vsprite_color;

out vec4 vertex_color;

uniform vec3 position;
uniform vec3 velocity;
uniform mat3 object_inv_boost;
uniform mat4 camera_transform;
uniform vec3 camera_position;
uniform mat3 camera_boost;

vec4 DebugVectorToColor(vec3 vector);

// space time coorinates are orginized as (x, y, t). The minkowski metric
// in this space is then represented as the matrix,
//     |1, 0, 0|
// g = |0, 1, 0|
//     |0, 0,-1|
//
// After relitivistic calculations are complete the result should be rendered
// on the x-y plane at z = 0. The camera will use an orthographic projection
// to transform into screen space.

float Dot(vec3 vectorA, vec3 vectorB) {
    return vectorA.x*vectorB.x + vectorA.y*vectorB.y - vectorA.z*vectorB.z;
}

void main() {
    vec3 vertex_position = object_inv_boost*vec3(vsprite_position, 0) + position;

    // Extruding the sprite along its local time axis `velocity` gives an
    // estimate of the world line for each vertex given by
    // `point_t = vertex_position + t*velocity`. Note, the center of the
    // object is on the past light cone so when looking for intersections
    // we will want the smaller of the two solutions for t.

    // Finding the intersection of the camera's past light cone with these
    // rays will be analagous to the function minkowski::WorldLine::GetIntersectionEstimates()

    vec3 offset = vertex_position - camera_position;

    // The world line in the region of interest is parameterized by the
    // variable t, `point_t = vertex_position + t*velocity`. The estimated
    // intersection with the past light cone is at t < 0.

    // the line intersects with the light cone when the seporation between
    // the tip of the cone and point_t is a null seporation, so when
    // (point_t - x_0)^2 = 0, where x_0 is the tip of the light cone.
    // Expanding out this equation (position - x_0 + t*velocity)^2 = 0
    // gives, velocity^2*t^2 + 2*velocity*(position - x_0)*t + (position - x_0)^2 = 0.
    // This is a quadratic equation with the coefficents

    float a = Dot(velocity, velocity);
    float b = 2*Dot(velocity, offset);
    float c = Dot(offset, offset);

    // the solutions are given by,
    // t_2 = (-b + sqrt(b^2 - 4a*c))/(2a)
    // t_1 = (-b - sqrt(b^2 - 4a*c))/(2a)
    // Note, world_line_vector is time like so a < 0, due to the geometry
    // of the world line it must intersect once with the future and past
    // light cones so the term in the square root is positive. The intersection
    // of interest is the smaller of the two.

    float intersection_t = (-b + sqrt(b*b - 4*a*c))/(2*a);

    // So the acctual point of intersection is then,

    vec3 intersection_point = vertex_position + intersection_t*velocity;

    // Finally transform the intersection points into the refrence frame
    // of the camera and then record the x and y locations, projecting on
    // to the z = 0 plane.

    gl_Position = camera_transform*vec4((camera_boost*(intersection_point - camera_position)).xy, 0, 1.0);
    vertex_color = vec4(vsprite_color, 1.0);
}

// Debugging

vec4 DebugVectorToColor(vec3 vector) {
    float error_size = 0.0001;

    float norm = Dot(vector, vector);

    // null vector: white
    if (abs(norm) <= error_size) {
        return vec4(1, 1, 1, 1);
    }

    // time like vector: blue
    if (norm < -error_size) {
        return vec4(0, 0, 1, 1);
    }

    // space like vector: green
    if (norm > error_size) {
        return vec4(0, 1, 0, 1);
    }

    // error
    return vec4(1, 0, 0, 1);
}
