#ifndef SPRITE_MANAGER_HPP
#define SPRITE_MANAGER_HPP

#include <memory>
#include <string>
#include <vector>

#include "shader.hpp"

namespace poincare {

class Sprite;

class SpriteManager {
public:
    /// Gets and instance of the SpriteManager singleton.
    /// return Pointer to an instance of SpriteManager.
    static SpriteManager* GetInstance();

    /// Get a shared pointer to the sprite at vector_sprite_path. If it
    /// is not cached the sprite will be loaded and added to the cache.
    std::shared_ptr<Sprite> GetSprite(std::string vector_sprite_path);

    /// The currently active shader
    Shader shader;

    void SetShader(Shader shader);

    void DrawSprites();
private:
    static SpriteManager* instance;

    std::vector<std::shared_ptr<Sprite>> sprite_list;

    SpriteManager();

    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;
};

} // namespace poincare

#endif
