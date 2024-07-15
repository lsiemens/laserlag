#include "worldline.hpp"

#include <stdexcept>

namespace minkowski {

Worldline::Worldline() {
}

void Worldline::AddPoint(Point point) {
    points.push_back(point);
}

int Worldline::size() const {
    return points.size();
}

Point Worldline::operator[](int i) const {
    if ((i < 0) || (i > size())) {
        throw std::out_of_range("World line index out of range.");
    }
    return points[size() - (i + 1)];
}

Point& Worldline::operator[](int i) {
    if ((i < 0) || (i >= size())) {
        throw std::out_of_range("World line refrence index out of range.");
    }
    return points[size() - (i + 1)];
}

} // namespace minkowski
