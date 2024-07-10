#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>

#include "point.hpp"

namespace minkowski {

class Vector {
public:
    Vector(double t, double x, double y);

    bool operator==(Vector const& other) const;
    double operator*(Vector const& other) const;
    friend Vector operator*(double scalar, Vector const& self);
    Vector operator+(Vector const& other) const;
    Vector operator-(Vector const& other) const;

    std::vector<float> ToFloat();
private:
    double components[3];

    friend Point Point::operator+(Vector const& other) const;
};

} // namespace minkowski

#endif
