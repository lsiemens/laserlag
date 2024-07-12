#ifndef POINT_HPP
#define POINT_HPP

#include <glm/glm.hpp>

namespace minkowski {

class Vector;

class Point {
public:
    Point();
    Point(double t, double x, double y);

    bool operator==(Point const& other) const;
    Vector operator-(Point const& other) const;
    Point operator+(Vector const& other) const;

    /// Convert to glm 3D vector where (t, x, y) maps to (x, y, z) with
    /// t going to z.
    glm::vec3 ToGLM();
private:
    double coordinates[3];
};

} // namespace minkowski

#endif
