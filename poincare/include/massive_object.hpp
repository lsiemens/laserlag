#ifndef MASSIVE_OBJECT_HPP
#define MASSIVE_OBJECT_HPP

#include "minkowski.hpp"

#include <memory>
#include <string>

namespace poincare {

class Sprite;

class MassiveObject {
public:
    bool active_buffer;
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
    minkowski::WorldLine world_line;

    /// The sprite to render for this object
    std::shared_ptr<Sprite> sprite;

    MassiveObject(minkowski::Point position, minkowski::Vector velocity, std::string vector_sprite_path);

    void UpdateObject(double dtau);

    /// Determine the number of time steps to take to maintain a space
    /// like seporation, as estimated by the estimated intersection with
    /// past and future light cones.
    void ManageWorldLineBuffer(double dtau, double t_past, double t_future);
private:
    /// Number of time steps to take during an update
    int time_step_num;
};

} // namespace poincare

#endif
