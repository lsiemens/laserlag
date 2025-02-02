#include "camera.hpp"

#include "sprite_manager.hpp"

namespace poincare {

void Camera::ApplyTransform() {
    SpriteManager* sprite_manager = SpriteManager::GetInstance();

    LocationIndices location_indices = sprite_manager->GetCurrentShader().location_indices;

    glm::mat4 transform_matrix = GetProjectionMatrix()*GetViewMatrix();
    glUniformMatrix4fv(location_indices.camera_transform_id, 1, GL_FALSE, &transform_matrix[0][0]);
    glUniform3fv(location_indices.camera_position_id, 1, &position.ToGLM()[0]);
    glUniformMatrix3fv(location_indices.camera_boost_id, 1, GL_FALSE, &velocity.Boost()[0][0]);
}

} // namespace poincare
