#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include <memory>
#include <glm/glm.hpp>

#include "camera.hpp"
#include "minkowski.hpp"

namespace poincare {

class MassiveObject;

class Camera2D : public Camera {
public:
    std::shared_ptr<MassiveObject> target_object;
    Camera2D(double aspect_ratio);

    void SetTarget(std::shared_ptr<MassiveObject> target_object);
    void UpdateCamera(double dtau) override;
private:
    glm::mat4 GetViewMatrix() override;
    glm::mat4 GetProjectionMatrix() override;
};

} // namespace poincare

#endif
