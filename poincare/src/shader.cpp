#include "shader.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "window_manager.hpp"

namespace poincare {

Shader::Shader() {
    shader_id = 0;
    vertex_path = "";
    fragment_path = "";
}

Shader::Shader(std::string vertex_path, std::string fragment_path) : vertex_path(vertex_path), fragment_path(fragment_path) {
    shader_id = 0;
    LoadShaderProgram();

    location_indices.position_id = glGetUniformLocation(shader_id, "position");
    location_indices.velocity_id = glGetUniformLocation(shader_id, "velocity");
    location_indices.camera_transform_id = glGetUniformLocation(shader_id, "camera_transform");
}

void Shader::SetActive() {
    glUseProgram(shader_id);
}

GLuint Shader::CompileShader(std::string shader_path, GLenum shader_type){
    GLuint shader_id = glCreateShader(shader_type);

    //Get Code
    std::string shader_code;
    std::ifstream shader_stream(shader_path, std::ios::in);
    if (shader_stream.is_open()) {
        std::stringstream shader_code_stream;
        shader_code_stream << shader_stream.rdbuf();
        shader_code = shader_code_stream.str();
        shader_stream.close();
    } else {
        std::cerr << "Failed to open '" << shader_path << "'.\n";
        throw std::runtime_error("Could not load shader source code.");
    }

    GLint result = GL_FALSE;
    int info_log_length;

    //Compile Shader
    char const* source_pointer = shader_code.c_str();
    glShaderSource(shader_id, 1, &source_pointer, NULL);
    glCompileShader(shader_id);

    //Error Check
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> ShaderErrorMessage(info_log_length + 1);
        glGetShaderInfoLog(shader_id, info_log_length, NULL, &ShaderErrorMessage[0]);
        std::cerr << &ShaderErrorMessage[0];
        throw std::runtime_error("Could not compile shader source code.");
    }

    return shader_id;
}

void Shader::LoadShaderProgram() {
    WindowManager* window_manager = WindowManager::GetInstance();
    if (!window_manager->HasContext()) {
        std::cerr << "No OpenGL context found by WindowManager\n";
        throw std::runtime_error("Could not configure shader.\n");
    }

    GLuint vertex_shader_id = CompileShader(vertex_path, GL_VERTEX_SHADER);
    GLuint fragment_shader_id = CompileShader(fragment_path, GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int info_log_length;

    //Link Shaders
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    //Error Check
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> ProgramErrorMessage(info_log_length + 1);
        glGetProgramInfoLog(program_id, info_log_length, NULL, &ProgramErrorMessage[0]);
        std::cerr << &ProgramErrorMessage[0] << "\n";
        throw std::runtime_error("Could not link the shader program.");
    }

    //Cleanup
    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    shader_id = program_id;
}

} // namespace poincare
