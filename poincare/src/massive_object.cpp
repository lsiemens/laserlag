#include "massive_object.hpp"



namespace poincare {

MassiveObject::MassiveObject(minkowski::Point position, minkowski::Vector velocity, std::string sprite_path) : proper_time(0), position(position), velocity(velocity) {
    worldline.AddPoint(position);
}

void MassiveObject::Update(double dtau) {
    position = position + dtau*velocity;
    proper_time += dtau;

    worldline.AddPoint(position);
}

} // namespace poincare
