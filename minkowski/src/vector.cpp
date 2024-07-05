#include "vector.hpp"

namespace minkowski {

Vector::Vector(double t, double x, double y) {
    components[0] = t;
    components[1] = x;
    components[2] = y;
}

bool Vector::operator==(Vector const& other) const {
    bool result = (components[0] == other.components[0]) && (components[1] == other.components[1]) && (components[2] == other.components[2]);
    return result;
}

double Vector::operator*(Vector const& other) const {
    double value = -components[0]*other.components[0] + components[1]*other.components[1] + components[2]*other.components[2];
    return value;
}

Vector operator*(double scalar, Vector const& self) {
    double t = scalar*self.components[0];
    double x = scalar*self.components[1];
    double y = scalar*self.components[2];
    return Vector(t, x, y);
}

Vector Vector::operator+(Vector const& other) const {
    double t = components[0] + other.components[0];
    double x = components[1] + other.components[1];
    double y = components[2] + other.components[2];
    return Vector(t, x, y);
}

Vector Vector::operator-(Vector const& other) const {
    double t = components[0] - other.components[0];
    double x = components[1] - other.components[1];
    double y = components[2] - other.components[2];
    return Vector(t, x, y);
}

} // namespace minkowski
