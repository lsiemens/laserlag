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

void WorldLine::GetLightConeIntersection(Point cone_position, Point &intersection_position, Vector &intersection_velocity) {
    // TODO
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

    int predicted_size = size()/stride;
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
