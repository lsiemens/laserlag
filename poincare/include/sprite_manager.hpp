#ifndef SPRITE_MANAGER_HPP
#define SPRITE_MANAGER_HPP

#include <memory>
#include <string>
#include <vector>

#include "shader.hpp"

namespace poincare {

class Sprite;
class Window;
class Camera;
class Camera2D;
class Camera3D;

struct RenderShaders {
    Shader object;
    Shader light_cone;
    Shader world_line;
    Shader event;
};

enum class ShaderTypes {
    kObjectShader,
    kLightConeShader,
    kWorldLineShader,
    kEventShader,
};

class SpriteManager {
public:
    bool show_world_line_intersections;

    /// Gets and instance of the SpriteManager singleton.
    /// return Pointer to an instance of SpriteManager.
    static SpriteManager* GetInstance();

    /// Get a shared pointer to the sprite at vector_sprite_path. If it
    /// is not cached the sprite will be loaded and added to the cache.
    std::shared_ptr<Sprite> GetSprite(std::string vector_sprite_path);

    RenderShaders render_shaders;

    /// Sprite consisting of a single point or triangle with the first
    /// vertex at 0, 0. This is a hack, in the future no sprite will be
    /// used, the objects, a point or set of points will be manualy sent
    /// instead.
    std::shared_ptr<Sprite> null_sprite;

    Shader GetCurrentShader();


// this looks at the window and points to Draw3D or Draw2D
//    void Draw(Window window);

    void Draw(std::shared_ptr<Window> window);

    void Draw3D(std::shared_ptr<Camera3D> camera);
    void Draw2D(std::shared_ptr<Camera2D> camera);

    void DrawSprites();
private:
    static SpriteManager* instance;

    std::vector<std::shared_ptr<Sprite>> sprite_list;
    ShaderTypes current_shader;

    void SetShader(ShaderTypes shader_type);

    SpriteManager();

    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;
};

} // namespace poincare

#endif
