#include "minkowski.hpp"

#include <stdexcept>
#include <iostream>

namespace minkowski {

WorldLine::WorldLine() {
}

void WorldLine::AddPoint(Point position, Vector velocity) {
    // the path is stored in sets of 6 doubles, three for the position
    // and three for the velocity. On of these set of 6 would look like
    // (t, x, y, v_t, v_x, v_y), Note that these values are stored in
    // the format used for OpenGL as produced by `ToGLM()`.
    path.insert(path.end(), position.coordinates, position.coordinates + 3);
    path.insert(path.end(), velocity.components, velocity.components + 3);
}

int WorldLine::size() const {
    return path.size()/6;
}

Point WorldLine::GetPosition(int index) {
    if ((index < 0) || (index >= size())) {
        std::cerr << "The index: " << index << " is out of range.\n";
        throw std::runtime_error("Could not get position from WorldLine.");
    }

    return Point(path[6*index + 0], path[6*index + 1], path[6*index + 2]);
}

Vector WorldLine::GetVelocity(int index) {
    if ((index < 0) || (index >= size())) {
        std::cerr << "The index: " << index << " is out of range.\n";
        throw std::runtime_error("Could not get velocity from WorldLine.");
    }

    return Vector(path[6*index + 3], path[6*index + 4], path[6*index + 5]);
}

/// GetLightConeIntersection calculates the intersection point of the
/// world line with a light cone. This calculation is greatly simplified
/// by noting that the world line of a massive object is allways contianed
/// within the light cone of every point along the path. Given this constraint
/// on the world line, if the rappidity of the world line is bounded it
/// will intersect with a light cone not on the path at exactly two points.
/// One intersection will be on the past light cone and the other intersection
/// will be on the future light cone.
///
/// If the active end of the world line object is space like seperated
/// from the point in question, then the a binary search can be used to
/// find the point along the world line where the distance to the point
/// in question is a light like seporation. That is using a binary search
/// to find the indices of the points on the world line where the sign
/// of the distance changes.
void WorldLine::GetLightConeIntersection(Point cone_position, Point &intersection_position, Vector &intersection_velocity) {
    int index_far = 0;
    int index_near = size() - 1;
    double distance2_near = (cone_position - GetPosition(index_near))*(cone_position - GetPosition(index_near));
    double distance2_far = (cone_position - GetPosition(index_far))*(cone_position - GetPosition(index_far));

    // Check if the newest point is space like seporated. If not, then
    // there is an error.
    if (distance2_near < 0) {
        std::cerr << "World line and point are not space like seporated.\n";
        throw std::runtime_error("Causality error");
    }

    Vector point_far_cone;
    Vector world_line_vector;

    // Check if the oldest point is space like seporated. If so, the world
    // line should be extended back untill an intersection occurs
    if (distance2_far > 0) {
        // Vector from the cone to the far point
        point_far_cone = GetPosition(index_far) - cone_position;
        // Vector of the world line at the far point
        world_line_vector = GetVelocity(index_far);
    } else {
        // The intersection is somewhere along the world line. Find the
        // indices on either side of the intersection point using a binary
        // search.
        double distance2_pivot;
        int index_pivot;
        while ((index_near - index_far) > 1) {
            index_pivot = (index_far + index_near)/2;
            distance2_near = (cone_position - GetPosition(index_near))*(cone_position - GetPosition(index_near));
            distance2_pivot = (cone_position - GetPosition(index_pivot))*(cone_position - GetPosition(index_pivot));

            // if the product of these distance squared is greater than zero
            // then this interval can not contain the intersection, since both
            // distance squared are nonzero and have the same sign.
            if (distance2_pivot*distance2_near > 0) {
                index_near = index_pivot;
            } else {
                index_far = index_pivot;
            }
        }

        // Vector from the cone to the far point
        point_far_cone = GetPosition(index_far) - cone_position;
        // Vector of the world line at the far point
        world_line_vector = GetPosition(index_near) - GetPosition(index_far);
    }

    // The world line in the region of interest is parameterized by the
    // variable t, point_t = point_far + t*world_line_vector. If the
    // intersection is between two points on the world line then t is in
    // the range [0, 1] and the line would intersect with the future light
    // cone at t > 1. If the intersection is past the farthest point then
    // then the intersection is at t < 0 and the line would intersect with
    // the future light cone at t > 0. In both cases we want the intersection
    // with the lesser value of t.

    // the line intersects with the light cone when the seporation between
    // the tip of the cone and point_t is a null seporation, so when
    // (point_t - x_0)^2 = 0, where x_0 is the tip of the light cone.
    // Expanding out this equation (point_far - x_0 + t*world_line_vector)^2 = 0
    // gives, world_line_vector^2*t^2 + 2*world_line_vector*(point_far - x_)*t + (point_far - x_0)^2 = 0.
    // This is a quadratic equation with the coefficents
    double a = world_line_vector*world_line_vector;
    double b = 2*world_line_vector*point_far_cone;
    double c = point_far_cone*point_far_cone;

    // the solutions are given by,
    // t_2 = (-b + sqrt(b^2 - 4a*c))/(2a)
    // t_1 = (-b - sqrt(b^2 - 4a*c))/(2a)
    // Note, world_line_vector is time like so a < 0, due to the geometry
    // of the world line it must intersect once with the future and past
    // light cones so the term in the square root is positive. Since a
    // is a nonzero negative number the lesser of the two solutions is
    double t = (-b + std::sqrt(b*b - 4*a*c))/(2*a);

    // Find position and velocity at the intersection point with the past light cone
    intersection_position = GetPosition(index_far) + t*world_line_vector;
    if (t < 0) {
        intersection_velocity = world_line_vector;
    } else {
        intersection_velocity = GetVelocity(index_far) + t*(GetVelocity(index_near) - GetVelocity(index_far));
    }
}

std::vector<float> WorldLine::Resample(double target_period, int output_size) {
    double dt = path[6*(size() - 1)] - path[0];
    // Rate that points are added to the path from the perspective of the system
    double data_rate = size()/dt;

    int stride = data_rate*target_period;

    if (stride < 1) {
        stride = 1;
    }

    std::vector<float> data(3*output_size);

    int j;
    for (int i=0; i < output_size; i++) {
        j = size() - (stride*i + 1);

        if (j < 0) {
            j = 0;
        }

        // position: change to OpenGL format
        data[3*i + 0] = static_cast<float>(path[6*j + 1]);
        data[3*i + 1] = static_cast<float>(path[6*j + 2]);
        data[3*i + 2] = static_cast<float>(path[6*j + 0]);
    }

    return data;
}

} // namespace minkowski
