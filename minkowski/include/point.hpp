#ifndef POINT_HPP
#define POINT_HPP

//#include "vector.hpp"

namespace minkowski {

class Vector;

class Point {
public:
    Point(double t, double x, double y);

    bool operator==(Point const& other) const;
    Vector operator-(Point const& other) const;
    Point operator+(Vector const& other) const;
private:
    double coordinates[3];
};

} // namespace minkowski

#endif
