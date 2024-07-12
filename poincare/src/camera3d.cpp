#include "camera3d.hpp"

#include <glm/gtx/transform.hpp>

namespace poincare {

Camera3D::Camera3D() {
    fov = 50;
    aspect_ratio = 1;
}

glm::mat4 Camera3D::GetViewMatrix() {
    glm::vec3 up(0, 0, 1);
    return glm::lookAt(position.ToGLM(), (position + direction).ToGLM(), up);
}

glm::mat4 Camera3D::GetProjectionMatrix() {
    return glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
}

} // namespace poincare
