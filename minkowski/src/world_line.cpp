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

    // Check if the newest point is space like seporated. If not, then
    // there is an error.
    double distance2_near = (cone_position - GetPosition(size() - 1))*(cone_position - GetPosition(size() - 1));
    if (distance2_near < 0) {
        std::cout << "World line and point are not space like seporated.\n";
        throw std::runtime_error("Causality error");
    }

    // Check if the oldest point is space like seporated. If so, the world
    // line should be extended back untill an intersection occurs
    double distance2_far = (cone_position - GetPosition(0))*(cone_position - GetPosition(0));
    if (distance2_far > 0) {
        // Vector from the cone to the far point
        Vector point_far_cone = GetPosition(0) - cone_position;
        // Vector from the far point to the near point
        Vector velocity_at_far = GetVelocity(0);

        double a = velocity_at_far*velocity_at_far;
        double b = 2*point_far_cone*velocity_at_far;
        double c = point_far_cone*point_far_cone;

        double t1 = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
        double t2 = (-b - std::sqrt(b*b - 4*a*c))/(2*a);

        double t;
        if (t1 <= 0) {
            t = t1;
        } else {
            t = t2;
        }

        // Find position and velocity at the intersection
        intersection_position = GetPosition(0) + t*velocity_at_far;
        intersection_velocity = velocity_at_far;
        return;
    }

    double distance2_pivot;
    int index_pivot;
    int index_far = 0;
    int index_near = size() - 1;
    while ((index_near - index_far) > 1) {
        index_pivot = (index_far + index_near)/2;
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

    // The points between the near and far points are parameterized by
    // Pt = far + t*(near - far) with t in [0, 1]
    // the distance to the cone of the intermidary point is (Pt - x_0)^2
    // which is zero if it is on the light cone. So 0 = (far - x_0 + t*(near - far))^2
    // this can expand to give the expression,
    // (near - far)^2*t^2 + 2*(far - x_0)*(near - far)*t + (far - x_0)^2 = 0.
    // Defining a = (near - far)^2, b = 2*(far - x_0)*(near - far), c = (far - x_0)^2
    // t = (-b+-sqrt(b^2 - 4*a*c))/2a


    // Vector from the cone to the far point
    Vector point_far_cone = GetPosition(index_far) - cone_position;
    // Vector from the far point to the near point
    Vector point_near_point_far = GetPosition(index_near) - GetPosition(index_far);

    double a = point_near_point_far*point_near_point_far;
    double b = 2*point_far_cone*point_near_point_far;
    double c = point_far_cone*point_far_cone;

    double t1 = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
    double t2 = (-b - std::sqrt(b*b - 4*a*c))/(2*a);

    double t;
    if ((t1 >= 0) && (t1 <= 1)) {
        t = t1;
    } else {
        t = t2;
    }

    // Find position and velocity at the intersection
    intersection_position = GetPosition(index_far) + t*point_near_point_far;
    intersection_velocity = GetVelocity(index_far) + t*(GetVelocity(index_near) - GetVelocity(index_far));
}

std::vector<float> WorldLine::Resample(double target_period, int max_size) {
    double dt = path[6*(size() - 1)] - path[0];
    // Rate that points are added to the path from the perspective of the system
    double data_rate = size()/dt;

    int stride = data_rate*target_period;

    std::cout << stride << " Stride.\n";

    if (stride < 1) {
        stride = 1;
    }

    // The extra factor of stride - 1 is used to guarentee that predicted_size
    // rounds upwards
    int predicted_size = (size() + stride - 1)/stride;
    if (predicted_size > max_size) {
        predicted_size = max_size;
    }

    std::vector<float> data(6*predicted_size);

    for (int i=0; i < predicted_size; i++) {
        // position: change to OpenGL format
        data[6*i + 0] = static_cast<float>(path[stride*6*i + 1]);
        data[6*i + 1] = static_cast<float>(path[stride*6*i + 2]);
        data[6*i + 2] = static_cast<float>(path[stride*6*i + 0]);

        // velocity: change to OpenGL format
        data[6*i + 3] = static_cast<float>(path[stride*6*i + 4]);
        data[6*i + 4] = static_cast<float>(path[stride*6*i + 5]);
        data[6*i + 5] = static_cast<float>(path[stride*6*i + 3]);
    }

    return data;
}

} // namespace minkowski
