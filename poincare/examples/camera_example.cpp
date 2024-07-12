#include <cmath>
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
    window_manager->OpenWindow(600, 400, "Camera example");
    window_manager->window_list[0]->SetColor(glm::vec3(0.25));

    SpriteManager* sprite_manager = SpriteManager::GetInstance();
    sprite_manager->SetShader(Shader("resources/light_cone.vs", "resources/light_cone.fs", "resources/light_cone.gs"));

    ObjectManager* object_manager = ObjectManager::GetInstance();
    MassiveObject object(Point(0, 0, 0), Vector(1, 0, 0), "resources/light_cone.vsprite");
    object_manager->massive_object_list.push_back(object);

    object_manager->massive_object_list.push_back(MassiveObject(Point(0, 0, 0), 1.89*Vector(1, 0.6, 0.6), "resources/light_cone.vsprite"));

    Camera3D camera3d;
    camera3d.position = Point(20, -60, 0);
    camera3d.direction = Vector(-20, 60, 0);

    AdvancedTimer system_clock;

    UpdateLogger* logger = UpdateLogger::GetInstance();

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    double dtau, time;
    do {
        dtau = system_clock.Timer();
        time = system_clock.GetTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera3d.position = Point(10, 20*std::cos(time), 20*std::sin(time));
        camera3d.direction = Vector(-10, -20*std::cos(time), -20*std::sin(time));

        camera3d.ApplyTransform();
        object_manager->UpdateObjects(dtau);

        sprite_manager->DrawSprites();

        glfwSwapBuffers(window_manager->window_list[0]->glfw_window);
        glfwPollEvents();
        logger->Flush();
    } while (glfwWindowShouldClose(window_manager->window_list[0]->glfw_window) == 0);
    return 0;
}
