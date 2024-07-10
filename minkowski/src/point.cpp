#include "point.hpp"

#include "vector.hpp"

namespace minkowski {

Point::Point(double t, double x, double y) {
    coordinates[0] = t;
    coordinates[1] = x;
    coordinates[2] = y;
}

bool Point::operator==(Point const& other) const {
    bool result = (coordinates[0] == other.coordinates[0]) && (coordinates[1] == other.coordinates[1]) && (coordinates[2] == other.coordinates[2]);
    return result;
}

Vector Point::operator-(Point const& other) const {
    double t = coordinates[0] - other.coordinates[0];
    double x = coordinates[1] - other.coordinates[1];
    double y = coordinates[2] - other.coordinates[2];
    return Vector(t, x, y);
}

Point Point::operator+(Vector const& other) const {
    double t = coordinates[0] + other.components[0];
    double x = coordinates[1] + other.components[1];
    double y = coordinates[2] + other.components[2];
    return Point(t, x, y);
}

std::vector<float> Point::ToFloat() {
    std::vector<float> values(3);
    for (int i=0; i<3; i++) {
        values[i] = static_cast<float>(coordinates[i]);
    }
    return values;
}

} // namespace minkowski
