#ifndef MASSIVE_OBJECT_H
#define MASSIVE_OBJECT_H

#include "minkowski.h"

namespace poincare {

class MassiveObject {
public:
    /// Time since the object's creation in its own refrence frame.
    double proper_time;

    /// Location of the object in the systems refrence frame.
    minkowski::Point position;

    /// Velocity of the object in the systems refrence frame.
    minkowski::Vector velocity;

    /// Orientation of the object as seen in its own refrence frame.
    /// TODO relativistic version?
    float orientation;

    /// Worldline of the particle in the systems refrance frame.
    minkowski::Worldline worldline

    MassiveObject();
private:
};

} // namespace poincare

#endif
