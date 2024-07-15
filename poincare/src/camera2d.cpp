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
    glm::vec3 up(0, 0, 1);
//    return glm::lookAt(position.ToGLM(), (position + direction).ToGLM(), up);
    return glm::mat4(1.0f);
}

glm::mat4 Camera2D::GetProjectionMatrix() {
//    return glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 1000.0f);
    return glm::mat4(1.0f);
}

} // namespace poincare
