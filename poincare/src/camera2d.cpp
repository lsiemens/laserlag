#include "camera2d.hpp"

#include <iostream>
#include <stdexcept>
#include <glm/gtx/transform.hpp>

#include "massive_object.hpp"

namespace poincare {

Camera2D::Camera2D(double aspect_ratio) {
    this->aspect_ratio = aspect_ratio;
    target_object = nullptr;
}

void Camera2D::SetTarget(std::shared_ptr<MassiveObject> target_object) {
    this->target_object = target_object;
}

void Camera2D::UpdateCamera(double dtau) {
    if (target_object == nullptr) {
        std::cerr << "Target object has not been set for 2D camera.\n";
        throw std::runtime_error("Could not update 2D camera.");
    }

    position = target_object->position;
    velocity = target_object->velocity;
}

glm::mat4 Camera2D::GetViewMatrix() {
    glm::vec3 z_direction(0, 0, 1);
    glm::vec3 y_direction(0, 1, 0);

    // project the camera to the horizonta plane at z = 0
    glm::vec3 position = this->position.ToGLM();
    position = position - glm::dot(position, z_direction)*z_direction;
    return glm::lookAt(position, position - z_direction, y_direction);
}

glm::mat4 Camera2D::GetProjectionMatrix() {
    float size = 40.0f;
    float height, width;

    if (aspect_ratio > 1.0) {
        height = size;
        width = size*aspect_ratio;
    } else {
        height = size/aspect_ratio;
        width = size;
    }
    return glm::ortho(-width/2, width/2, -height/2, height/2, -1.0f, 1.0f);
}

} // namespace poincare
