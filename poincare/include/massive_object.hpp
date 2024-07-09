#ifndef MASSIVE_OBJECT_H
#define MASSIVE_OBJECT_H

#include "minkowski.hpp"

#include <memory>
#include <string>

namespace poincare {

class Sprite;

class MassiveObject {
public:
    /// Time since the object's creation in its own refrence frame.
    double proper_time;

    /// Location of the object in the systems refrence frame.
    minkowski::Point position;

    /// Velocity of the object in the systems refrence frame. This vector
    /// should be normalized so velocity*velocity = -1 (using c = 1 units);
    minkowski::Vector velocity;

    /// Orientation of the object as seen in its own refrence frame. For
    /// now the orientation will not be trated as a kinematic variable
    /// and will not give it a full relativistic treatment.
    /// TODO relativistic version?
    float orientation;

    /// Worldline of the particle in the systems refrance frame.
    minkowski::Worldline worldline;

    MassiveObject(minkowski::Point position, minkowski::Vector velocity, std::string sprite_path);

    void Update(double dtau);
private:
    /// The sprite to render for this object
    std::shared_ptr<Sprite> sprite;
};

} // namespace poincare

#endif
