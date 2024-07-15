#include "camera2d.hpp"

#include <iostream>
#include <glm/gtx/transform.hpp>

namespace poincare {

Camera2D::Camera2D(double aspect_ratio) {
    this->aspect_ratio = aspect_ratio;
}

void Camera2D::UpdateCamera(double dtau) {
    position = position + dtau*velocity;
}

glm::mat4 Camera2D::GetViewMatrix() {
    glm::vec3 z_direction(0, 0, 1);
    glm::vec3 y_direction(0, 1, 0);
    return glm::lookAt(position.ToGLM(), position.ToGLM() - z_direction, y_direction);
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
