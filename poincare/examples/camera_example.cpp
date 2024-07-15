#include <cmath>
#include <memory>
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
    window_manager->OpenWindow(600, 400, "Camera example", poincare::ViewMode::kView3D);
    window_manager->window_list[0]->SetColor(glm::vec3(0.25));

    SpriteManager* sprite_manager = SpriteManager::GetInstance();
    sprite_manager->render_shaders.object = Shader("resources/basic.vs", "resources/basic.fs");
    sprite_manager->render_shaders.light_cone = Shader("resources/light_cone.vs", "resources/light_cone.fs", "resources/light_cone.gs");
    sprite_manager->render_shaders.world_line = Shader("resources/world_line.vs", "resources/world_line.fs", "resources/world_line.gs");
    sprite_manager->null_sprite = sprite_manager->GetSprite("resources/light_cone.vsprite");

    ObjectManager* object_manager = ObjectManager::GetInstance();
    MassiveObject object(Point(0, 0, 0), Vector(1, 0, 0), "resources/basic.vsprite");
    object_manager->massive_object_list.push_back(object);

    object_manager->massive_object_list.push_back(MassiveObject(Point(0, 0, 0), 1.89*Vector(1, 0.6, 0.6), "resources/basic.vsprite"));

    object_manager->massive_object_list.push_back(MassiveObject(Point(0, 10, -10), Vector(1, 0, 0), "resources/basic.vsprite"));

    std::shared_ptr<Camera3D> camera = std::dynamic_pointer_cast<Camera3D>(window_manager->window_list[0]->camera);
    camera->position = Point(20, -60, 0);
    camera->direction = Vector(-20, 60, 0);

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

        double camera_rate = 0.3;
        double camera_distance = 60;
        camera->position = Point(10, camera_distance*std::cos(camera_rate*time), camera_distance*std::sin(camera_rate*time));
        camera->direction = Vector(-10, -camera_distance*std::cos(camera_rate*time), -camera_distance*std::sin(camera_rate*time));

        double speed = 0.9;
        double gamma = 1/std::sqrt(1 - speed*speed);
        double rate = 3;
        object_manager->massive_object_list[2].velocity = gamma*Vector(1, speed*std::cos(rate*time), speed*std::sin(rate*time));

        object_manager->UpdateObjects(dtau);

        sprite_manager->Draw3D(camera);

        glfwSwapBuffers(window_manager->window_list[0]->glfw_window);
        glfwPollEvents();
        logger->Flush();
    } while (glfwWindowShouldClose(window_manager->window_list[0]->glfw_window) == 0);
    return 0;
}
