#include "sprite_manager.hpp"

#include <iostream>
#include <stdexcept>

#include "sprite.hpp"
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
        default: {
            std::cerr << "Error: Shader type of the current shader not recognized.\n";
            throw std::runtime_error("Could not find the current shader.");
        }
    }
}

void SpriteManager::Draw3D(Camera &camera) {
    ObjectManager* object_manager = ObjectManager::GetInstance();

    if (null_sprite == nullptr) {
        std::cerr << "No sprite has been loaded as null_sprite.\n";
        throw std::runtime_error("Could not draw light cones.");
    }

    // Draw light cones
    SetShader(ShaderTypes::kLightConeShader);
    camera.ApplyTransform();

    for (MassiveObject &object : object_manager->massive_object_list) {
        glUniform3fv(render_shaders.light_cone.location_indices.position_id, 1, &object.position.ToGLM()[0]);
        null_sprite->DrawSprite();
    }

    // Draw world lines
    SetShader(ShaderTypes::kWorldLineShader);
    camera.ApplyTransform();

    float* wl = new float[128*3];

    for (MassiveObject &object : object_manager->massive_object_list) {
        for (int i=0; i<128; i++) {
            int stride = 2000;
            if (i < object.worldline.size()/stride) {
                glm::vec3 pos = object.worldline[stride*i].ToGLM();
                wl[0 + 3*i] = pos.x;
                wl[1 + 3*i] = pos.y;
                wl[2 + 3*i] = pos.z;
            } else {
                glm::vec3 pos = object.worldline[object.worldline.size() - 1].ToGLM();
                wl[0 + 3*i] = pos.x;
                wl[1 + 3*i] = pos.y;
                wl[2 + 3*i] = pos.z;
            }
        }

        glUniform3fv(render_shaders.world_line.location_indices.position_id, 1, &object.position.ToGLM()[0]);
        glUniform3fv(render_shaders.world_line.location_indices.world_line_id, 128, wl);
        object.sprite->DrawSprite();
    }

    delete [] wl;
}

void SpriteManager::DrawSprites() {
    ObjectManager* object_manager = ObjectManager::GetInstance();

    SetShader(ShaderTypes::kObjectShader);
    for (MassiveObject &object : object_manager->massive_object_list) {
        glUniform3fv(render_shaders.object.location_indices.position_id, 1, &object.position.ToGLM()[0]);
        object.sprite->DrawSprite();
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
        default: {
            std::cerr << "Error: Shader type not recognized. The current shader will not be changed.\n";
        }
    }
}

SpriteManager::SpriteManager() {
}

} // namespace poincare
