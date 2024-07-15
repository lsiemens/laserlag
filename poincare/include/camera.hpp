#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

#include "minkowski.hpp"

namespace poincare {

class Camera {
public:
    minkowski::Point position;
    minkowski::Vector velocity;
    double aspect_ratio;

    void ApplyTransform();
    virtual void UpdateCamera(double dtau) = 0;

private:
    virtual glm::mat4 GetViewMatrix() = 0;
    virtual glm::mat4 GetProjectionMatrix() = 0;
};

} // namespace poincare

#endif
