#include "window.hpp"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace poincare {

Window::Window(int width, int height, std::string title, bool vsync, GLFWwindow* primary_window) : glfw_window(nullptr), primary_window(primary_window) {
    if (primary_window == nullptr) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW.");
        } else {
            std::clog << "Initalized GLFW successfully.\n";
        }
    }

    InitializeWindow(width, height, title);
    glfwMakeContextCurrent(glfw_window);

    if (primary_window == nullptr) {
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW.");
        } else {
            std::clog << "Initalized GLEW successfully.\n";
        }
    }

    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    if (vsync) {
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

    glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, primary_window);
    if (glfw_window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }
}

} // namespace poincare
