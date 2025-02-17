#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#include <glm/glm.hpp>

#include "camera.hpp"

#include "minkowski.hpp"

namespace poincare {

class Camera3D : public Camera {
public:
    minkowski::Vector direction;
    float fov;

    Camera3D(double aspect_ratio);

    void UpdateCamera(double dtau) override;
private:
    glm::mat4 GetViewMatrix() override;
    glm::mat4 GetProjectionMatrix() override;
};

} // namespace poincare

#endif
