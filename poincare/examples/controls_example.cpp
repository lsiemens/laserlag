#include <memory>
#include <iostream>
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

namespace {

class CameraControls {
public:
    double old_u = 0;
    double old_v = 0;

    void ControlResponse(double dtau, std::shared_ptr<Window> window) {
        std::shared_ptr<Camera3D> camera = std::dynamic_pointer_cast<Camera3D>(window->camera);
        Continuous axes = window->controls->axes;

        double speed = 5;
        float sensitivity = 0.5;
        glm::vec3 up(0, 0, 1);
        up = glm::normalize(up);
        glm::vec3 direction = glm::normalize(camera->direction.ToGLM());

        glm::vec3 forward = glm::normalize(direction - glm::dot(direction, up)*up);
        glm::vec3 left = glm::cross(up, forward);
        left = glm::normalize(left);

        glm::vec3 acc(0.0f);

        double du = axes.u - old_u;
        double dv = axes.v - old_v;
        old_u = axes.u;
        old_v = axes.v;

        if (window->controls->actions.uv_interact) {
            direction = direction + sensitivity*(-(float)dv*up + (float)du*left);
            direction = glm::normalize(direction);
            camera->direction = Vector(direction.z, direction.x, direction.y);
        }

        acc = (float)axes.x*forward - (float)axes.y*left + (float)axes.z*up;
        if (glm::dot(acc, acc) >= speed*speed) {
            acc = glm::normalize(acc);
        }
        Vector control(acc.z, acc.x, acc.y);
        camera->velocity = camera->velocity + dtau*speed*control;
    }
};

} // namespace

int main() {
    WindowManager* window_manager = WindowManager::GetInstance();
    window_manager->SetVsync(true);
    window_manager->OpenWindow(600, 400, "Controls example", poincare::ViewMode::kView3D);
    window_manager->window_list[0]->SetColor(glm::vec3(0.25));
    window_manager->OpenWindow(600, 400, "Controls example: B", poincare::ViewMode::kView3D);
    window_manager->window_list[1]->SetColor(glm::vec3(0.5));

    SpriteManager* sprite_manager = SpriteManager::GetInstance();
    sprite_manager->render_shaders.object = Shader("resources/basic.vs", "resources/basic.fs");
    sprite_manager->render_shaders.light_cone = Shader("resources/light_cone.vs", "resources/light_cone.fs", "resources/light_cone.gs");
    sprite_manager->render_shaders.world_line = Shader("resources/world_line.vs", "resources/world_line.fs", "resources/world_line.gs");
    sprite_manager->null_sprite = sprite_manager->GetSprite("resources/null.vsprite");

    ObjectManager* object_manager = ObjectManager::GetInstance();
    std::shared_ptr<MassiveObject> object = std::make_shared<MassiveObject>(Point(0, 1, 0), Vector(1, 0, 0), "resources/basic.vsprite");
    object_manager->massive_object_list.push_back(object);

    object = std::make_shared<MassiveObject>(Point(0, 0, 1), 1.89*Vector(1, 0.6, 0.6), "resources/basic.vsprite");
    object_manager->massive_object_list.push_back(object);

    object = std::make_shared<MassiveObject>(Point(0, 10, -10), Vector(1, 0, 0), "resources/basic.vsprite");
    object_manager->massive_object_list.push_back(object);
    object->active_buffer = false;

    // camera setup
    std::shared_ptr<Camera3D> camera = std::dynamic_pointer_cast<Camera3D>(window_manager->window_list[0]->camera);
    camera->position = Point(20, -60, 0);
    camera->direction = Vector(-20, 60, 0);

    camera = std::dynamic_pointer_cast<Camera3D>(window_manager->window_list[1]->camera);
    camera->position = Point(20, 60, 0);
    camera->direction = Vector(-20, -60, 0);

    AdvancedTimer system_clock;

    UpdateLogger* logger = UpdateLogger::GetInstance();

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    CameraControls camera_controls1;
    CameraControls camera_controls2;

    double dtau;
    do {
        window_manager->window_list[0]->controls->LogState();
        dtau = system_clock.Timer();

        double speed = 0.9;
        double gamma = 1/std::sqrt(1 - speed*speed);
        double rate = 3;
        std::shared_ptr<MassiveObject> object = object_manager->massive_object_list[2];
        object->velocity = gamma*Vector(1, speed*std::cos(rate*object->proper_time), speed*std::sin(rate*object->proper_time));

        camera_controls1.ControlResponse(dtau, window_manager->window_list[0]);
        camera_controls2.ControlResponse(dtau, window_manager->window_list[1]);
        object_manager->UpdateObjects(dtau);

        window_manager->window_list[0]->camera->UpdateCamera(dtau);
        window_manager->window_list[1]->camera->UpdateCamera(dtau);

        window_manager->window_list[0]->MakeCurrentContext();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sprite_manager->Draw(window_manager->window_list[0]);
        glfwSwapBuffers(window_manager->window_list[0]->glfw_window);

        window_manager->window_list[1]->MakeCurrentContext();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sprite_manager->Draw(window_manager->window_list[1]);
        glfwSwapBuffers(window_manager->window_list[1]->glfw_window);

        glfwPollEvents();
        logger->Flush();
    } while (!(window_manager->window_list[0]->controls->actions.close || window_manager->window_list[1]->controls->actions.close));
    return 0;
}
