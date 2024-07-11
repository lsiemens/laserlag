#include "sprite_manager.hpp"

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

void SpriteManager::SetShader(Shader shader) {
    this->shader = shader;
    shader.SetActive();
}

void SpriteManager::DrawSprites() {
    ObjectManager* object_manager = ObjectManager::GetInstance();

    for (MassiveObject &object : object_manager->massive_object_list) {
        glUniform3fv(shader.position_id, 1, object.position.ToFloat().data());
        object.sprite->DrawSprite();
    }
}

SpriteManager::SpriteManager() {
}

} // namespace poincare
