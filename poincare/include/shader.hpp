#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
// keep this before all other OpenGL libraries
#define GLEW_STATIC
#include <GL/glew.h>

namespace poincare {

struct LocationIndices {
    /// Object position for vertex shader
    int position_id = -1;
    /// Object velocity for vertex shader
    int velocity_id = -1;
    /// World line of a massive object
    int world_line_id = -1;
    /// Camera transform for vertex shader
    int camera_transform_id = -1;
    /// Camera position for vertex shader
    int camera_position_id = -1;
    /// Camera boost for transforming from the system frame to the camera's
    /// frame in the vertex shader
    int camera_boost_id = -1;
};

class Shader {
public:
    GLuint shader_id;
    std::string vertex_path;
    std::string geometry_path;
    std::string fragment_path;

    LocationIndices location_indices;

    Shader();
    Shader(std::string vertex_path, std::string fragment_path, std::string geometry_path = "");

    void SetActive();
private:
    void LoadShaderProgram();
    GLuint CompileShader(std::string shader_path, GLenum shader_type);
};

} // namespace poincare

#endif
