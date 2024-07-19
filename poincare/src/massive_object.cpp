#include "massive_object.hpp"

#include <iostream>

#include "sprite.hpp"
#include "sprite_manager.hpp"

namespace poincare {

MassiveObject::MassiveObject(minkowski::Point position, minkowski::Vector velocity, std::string vector_sprite_path) : proper_time(0), position(position), velocity(velocity), orientation(0) {
    SpriteManager* sprite_manager = SpriteManager::GetInstance();
    sprite = sprite_manager->GetSprite(vector_sprite_path);

    world_line.AddPoint(position, velocity);

    time_step_num = 1;
    active_buffer = true;
}

void MassiveObject::UpdateObject(double dtau) {
    for (int i=0; i < time_step_num; i++) {
        position = position + dtau*velocity;
        proper_time += dtau;

        world_line.AddPoint(position, velocity);
    }
}

void MassiveObject::ManageWorldLineBuffer(double dtau, double t_past, double t_future) {
    double total_buffer = t_future - t_past;
    if (active_buffer) {
        if ((t_future/total_buffer < 0.25) || (t_future/dtau < 10)) {
            time_step_num = 0;
            return;
        }

        if ((t_past/total_buffer < 0.25) || (t_past/dtau < 10)) {
            time_step_num = 4;
            return;
        }
    }

    time_step_num = 1;
}

} // namespace poincare
