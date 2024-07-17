#include "massive_object.hpp"

#include "sprite.hpp"
#include "sprite_manager.hpp"

namespace poincare {

MassiveObject::MassiveObject(minkowski::Point position, minkowski::Vector velocity, std::string vector_sprite_path) : proper_time(0), position(position), velocity(velocity), orientation(0) {
    SpriteManager* sprite_manager = SpriteManager::GetInstance();
    sprite = sprite_manager->GetSprite(vector_sprite_path);

    world_line.AddPoint(position, velocity);
}

void MassiveObject::UpdateObject(double dtau) {
    position = position + dtau*velocity;
    proper_time += dtau;

    world_line.AddPoint(position, velocity);
}

} // namespace poincare
