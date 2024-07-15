#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include <glm/glm.hpp>

#include "camera.hpp"

#include "minkowski.hpp"

namespace poincare {

class Camera2D : public Camera {
public:

    Camera2D(double aspect_ratio);

    void UpdateCamera(double dtau) override;
private:
    glm::mat4 GetViewMatrix() override;
    glm::mat4 GetProjectionMatrix() override;
};

} // namespace poincare

#endif
