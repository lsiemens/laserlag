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
    /// Camera transform for vertex shader
    int camera_transform_id = -1;
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
