#include "sprite_manager.hpp"

#include "sprite.hpp"

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

SpriteManager::SpriteManager() {
}

} // namespace poincare
