#ifndef WORLDLINE_HPP
#define WORLDLINE_HPP

#include <vector>

#include "point.hpp"

namespace minkowski {

class Worldline {
public:
    Worldline();
    std::vector<Point> points;

    void AddPoint(Point point);
    int size() const;

    Point operator[](int i) const;
    Point& operator[](int i);
};

} // namespace minkowski

#endif
