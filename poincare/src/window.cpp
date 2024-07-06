#include "window.hpp"

#include <stdexcept>

//// keep this before all other OpenGL libraries
//#define GLEW_STATIC
//#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace poincare {

Window::Window(int width, int height, std::string title, bool wait_vsync, Window* primary_window) : glfw_window(nullptr), primary_window(primary_window) {
    if (primary_window == nullptr) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW.");
        }
    }

    InitializeWindow(width, height, title);
    glfwMakeContextCurrent(glfw_window);

    if (primary_window == nullptr) {
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW.");
        }
    }

    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    if (wait_vsync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
}

Window::~Window() {
    glfwDestroyWindow(glfw_window);
    if (primary_window == nullptr) {
        glfwTerminate();
    }
}

void Window::MakeCurrentContext() {
    glfwMakeContextCurrent(glfw_window);
    glBindVertexArray(vertex_array_id);
}

void Window::SetColor(glm::vec3 color) {
    MakeCurrentContext();
    glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::InitializeWindow(int width, int height, std::string title) {
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    GLFWwindow* glfw_primary_window = nullptr;
    if (primary_window != nullptr) {
        glfw_primary_window = primary_window->glfw_window;
    }

    glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, glfw_primary_window);
    if (glfw_window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }
}

} // namespace poincare
