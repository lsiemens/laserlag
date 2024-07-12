#include "camera.hpp"

#include "sprite_manager.hpp"

namespace poincare {

void Camera::ApplyTransform() {
    SpriteManager* sprite_manager = SpriteManager::GetInstance();

    LocationIndices location_indices = sprite_manager->shader.location_indices;

    glm::mat4 transform_matrix = GetProjectionMatrix()*GetViewMatrix();
    glUniformMatrix4fv(location_indices.camera_transform_id, 1, GL_FALSE, &transform_matrix[0][0]);
}

} // namespace poincare
