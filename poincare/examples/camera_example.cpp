#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "massive_object.hpp"

#include "update_logger.hpp"
#include "frame_timer.hpp"
#include "window_manager.hpp"
#include "sprite_manager.hpp"
#include "object_manager.hpp"
#include "camera3d.hpp"

using namespace poincare;
using namespace minkowski;

int main() {
    WindowManager* window_manager = WindowManager::GetInstance();
    window_manager->SetVsync(false);
    window_manager->OpenWindow(600, 400, "Sprite example");
    window_manager->window_list[0]->SetColor(glm::vec3(0.25));

    SpriteManager* sprite_manager = SpriteManager::GetInstance();
    sprite_manager->SetShader(Shader("resources/vertex3d.shader", "resources/fragment.shader"));

    ObjectManager* object_manager = ObjectManager::GetInstance();
    MassiveObject object(Point(0, 0, 0), Vector(1, 0, 0), "resources/vector_sprite.dat");
    object_manager->massive_object_list.push_back(object);

    object_manager->massive_object_list.push_back(MassiveObject(Point(0, 0, 0), 1.01*Vector(1, 0.1, 0.1), "resources/vector_sprite.dat"));

    Camera3D camera3d;
    camera3d.position = Point(10, -10, 0);
    camera3d.direction = Vector(-10, 10, 0);

    AdvancedTimer system_clock;

    UpdateLogger* logger = UpdateLogger::GetInstance();

    double dtau;
    do {
        dtau = system_clock.Timer();
        glClear(GL_COLOR_BUFFER_BIT);

        camera3d.ApplyTransform();
        object_manager->UpdateObjects(dtau);

        sprite_manager->DrawSprites();

        glfwSwapBuffers(window_manager->window_list[0]->glfw_window);
        glfwPollEvents();
        logger->Flush();
    } while (glfwWindowShouldClose(window_manager->window_list[0]->glfw_window) == 0);
    return 0;
}
