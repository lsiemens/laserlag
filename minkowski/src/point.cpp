#include "minkowski.hpp"

namespace minkowski {

Point::Point() {
    coordinates[0] = 0;
    coordinates[1] = 0;
    coordinates[2] = 0;
}

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

glm::vec3 Point::ToGLM() {
    glm::vec3 values(0.0f);
    values.x = static_cast<float>(coordinates[1]);
    values.y = static_cast<float>(coordinates[2]);
    values.z = static_cast<float>(coordinates[0]);
    return values;
}

} // namespace minkowski
