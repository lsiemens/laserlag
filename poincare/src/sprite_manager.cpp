#include "sprite_manager.hpp"

#include <iostream>
#include <stdexcept>

#include "sprite.hpp"
#include "camera.hpp"
#include "camera2d.hpp"
#include "camera3d.hpp"
#include "window.hpp"
#include "massive_object.hpp"
#include "object_manager.hpp"

namespace poincare {

SpriteManager* SpriteManager::instance = nullptr;

SpriteManager* SpriteManager::GetInstance() {
    if (instance == nullptr) {
        instance = new SpriteManager();
    }
    return instance;
}

std::shared_ptr<Sprite> SpriteManager::GetSprite(std::string vector_sprite_path) {
    // Return shared pointer if it already exists
    for (std::shared_ptr<Sprite> &sprite : sprite_list) {
        if (sprite->vector_sprite_path == vector_sprite_path) {
            return std::shared_ptr<Sprite>(sprite);
        }
    }

    // Load sprite and return a shared pointer to it while adding it to sprite_list
    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(vector_sprite_path);
    sprite_list.push_back(sprite);
    return std::shared_ptr<Sprite>(sprite);
}

Shader SpriteManager::GetCurrentShader() {
    switch (current_shader) {
        case ShaderTypes::kObjectShader: {
            return render_shaders.object;
        }
        case ShaderTypes::kLightConeShader: {
            return render_shaders.light_cone;
        }
        case ShaderTypes::kWorldLineShader: {
            return render_shaders.world_line;
        }
        case ShaderTypes::kEventShader: {
            return render_shaders.event;
        }
        default: {
            std::cerr << "Error: Shader type of the current shader not recognized.\n";
            throw std::runtime_error("Could not find the current shader.");
        }
    }
}

void SpriteManager::Draw(std::shared_ptr<Window> window) {
    switch (window->view_mode) {
        case ViewMode::kView3D: {
            std::shared_ptr<Camera3D> camera = std::dynamic_pointer_cast<Camera3D>(window->camera);
            if (camera == nullptr) {
                std::cerr << "Error: Failed to cast Camera as Camera3D.\n";
                throw std::runtime_error("Failed to cast Camera as Camera3D in window designated as 3D.");
            }
            Draw3D(camera);
            break;
        }
        case ViewMode::kView2D: {
            std::shared_ptr<Camera2D> camera = std::dynamic_pointer_cast<Camera2D>(window->camera);
            if (camera == nullptr) {
                std::cerr << "Error: Failed to cast Camera as Camera2D.\n";
                throw std::runtime_error("Failed to cast Camera as Camera2D in window designated as 2D.");
            }
            Draw2D(camera);
            break;
        }
        default: {
            std::cerr << "Only Camera3D and Camera2D are implemented\n";
            throw std::runtime_error("Unrecognized view mode.");
        }
    }
}

void SpriteManager::Draw3D(std::shared_ptr<Camera3D> camera) {
    ObjectManager* object_manager = ObjectManager::GetInstance();

    if (null_sprite == nullptr) {
        std::cerr << "No sprite has been loaded as null_sprite.\n";
        throw std::runtime_error("Could not draw light cones.");
    }

    // Draw light cones
    SetShader(ShaderTypes::kLightConeShader);
    camera->ApplyTransform();

    for (std::shared_ptr<MassiveObject> &object : object_manager->massive_object_list) {
        glUniform3fv(render_shaders.light_cone.location_indices.position_id, 1, &object->position.ToGLM()[0]);
        null_sprite->DrawSprite();
    }

    // Draw world lines
    SetShader(ShaderTypes::kWorldLineShader);
    camera->ApplyTransform();

    std::vector<float> world_line_data;

    double target_interval = 0.25;
    for (std::shared_ptr<MassiveObject> &object : object_manager->massive_object_list) {
        world_line_data = object->world_line.Resample(target_interval, 128);

        glUniform3fv(render_shaders.world_line.location_indices.position_id, 1, &object->position.ToGLM()[0]);
        glUniform3fv(render_shaders.world_line.location_indices.world_line_id, 128, &world_line_data[0]);
        object->sprite->DrawSprite();
    }

    if (show_world_line_intersections) {
        // Draw intersection events
        SetShader(ShaderTypes::kEventShader);
        camera->ApplyTransform();

        int num_objects = object_manager->massive_object_list.size();
        for (int i=0; i < num_objects; i++) {
            for (int j=0; j < num_objects; j++) {
                if (i == j) {
                    continue;
                }

                minkowski::Point position_i = object_manager->massive_object_list[i]->position;
                minkowski::Point position_j;
                minkowski::Vector velocity_j;
                object_manager->massive_object_list[j]->world_line.GetLightConeIntersection(position_i, position_j, velocity_j);

                glUniform3fv(render_shaders.event.location_indices.position_id, 1, &position_j.ToGLM()[0]);
                null_sprite->DrawSprite();
            }
        }
    }
}

void SpriteManager::Draw2D(std::shared_ptr<Camera2D> camera) {
    ObjectManager* object_manager = ObjectManager::GetInstance();

    // Draw MassiveObjects
    SetShader(ShaderTypes::kObjectShader);
    camera->ApplyTransform();

    for (std::shared_ptr<MassiveObject> &object : object_manager->massive_object_list) {
        minkowski::Point position;
        minkowski::Vector velocity;
        object->world_line.GetLightConeIntersection(camera->position, position, velocity);

        glUniform3fv(render_shaders.object.location_indices.position_id, 1, &position.ToGLM()[0]);
        glUniform3fv(render_shaders.object.location_indices.velocity_id, 1, &velocity.ToGLM()[0]);
        object->sprite->DrawSprite();
    }
}

void SpriteManager::DrawSprites() {
    ObjectManager* object_manager = ObjectManager::GetInstance();

    SetShader(ShaderTypes::kObjectShader);
    for (std::shared_ptr<MassiveObject> &object : object_manager->massive_object_list) {
        glUniform3fv(render_shaders.object.location_indices.position_id, 1, &object->position.ToGLM()[0]);
        object->sprite->DrawSprite();
    }
}

void SpriteManager::SetShader(ShaderTypes shader_type) {
    switch (shader_type) {
        case ShaderTypes::kObjectShader: {
            render_shaders.object.SetActive();
            current_shader = ShaderTypes::kObjectShader;
            break;
        }
        case ShaderTypes::kLightConeShader: {
            render_shaders.light_cone.SetActive();
            current_shader = ShaderTypes::kLightConeShader;
            break;
        }
        case ShaderTypes::kWorldLineShader: {
            render_shaders.world_line.SetActive();
            current_shader = ShaderTypes::kWorldLineShader;
            break;
        }
        case ShaderTypes::kEventShader: {
            render_shaders.event.SetActive();
            current_shader = ShaderTypes::kEventShader;
            break;
        }
        default: {
            std::cerr << "Error: Shader type not recognized.\n";
            throw std::runtime_error("Could not set shader.");
        }
    }
}

SpriteManager::SpriteManager() {
    show_world_line_intersections = false;
}

} // namespace poincare
