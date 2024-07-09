#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
// keep this before all other OpenGL libraries
#define GLEW_STATIC
#include <GL/glew.h>

namespace poincare {

class Shader {
public:
    GLuint shader_id;
    std::string vertex_path;
    std::string fragment_path;

    Shader(std::string vertex_path, std::string fragment_path);
private:
    void LoadShaderProgram();
    GLuint CompileShader(std::string shader_path, GLenum shader_type);
};

} // namespace poincare

#endif
