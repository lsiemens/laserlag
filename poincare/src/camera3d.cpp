#include "camera3d.hpp"

#include <iostream>
#include <glm/gtx/transform.hpp>

namespace poincare {

Camera3D::Camera3D(double aspect_ratio) {
    fov = 50;
    this->aspect_ratio = aspect_ratio;
}

void Camera3D::UpdateCamera(double dtau) {
    position = position + dtau*velocity;
}

glm::mat4 Camera3D::GetViewMatrix() {
    glm::vec3 up(0, 0, 1);
    return glm::lookAt(position.ToGLM(), (position + direction).ToGLM(), up);
}

glm::mat4 Camera3D::GetProjectionMatrix() {
    return glm::perspective(glm::radians(fov), static_cast<float>(aspect_ratio), 0.1f, 1000.0f);
}

} // namespace poincare
