#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <glm/glm.hpp>

#include "point.hpp"

namespace minkowski {

class Vector {
public:
    Vector();
    Vector(double t, double x, double y);

    bool operator==(Vector const& other) const;
    double operator*(Vector const& other) const;
    friend Vector operator*(double scalar, Vector const& self);
    Vector operator+(Vector const& other) const;
    Vector operator-(Vector const& other) const;

    /// Convert to glm 3D vector where (t, x, y) maps to (x, y, z) with
    /// t going to z.
    glm::vec3 ToGLM();
private:
    double components[3];

    friend Point Point::operator+(Vector const& other) const;
};

} // namespace minkowski

#endif
