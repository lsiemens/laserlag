#include "window.hpp"

#include <stdexcept>

// keep this before all other OpenGL libraries
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace poincare {

Window::Window(int width, int height, std::string title, GLFWwindow* primary_window) : window(nullptr), primary_window(primary_window) {
    if (primary_window == nullptr) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW.");
        }
    }

    InitializeWindow(width, height, title);

    if (primary_window == nullptr) {
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW.");
        }
    }

    glfwSwapInterval(0);
}

Window::~Window() {
    glfwDestroyWindow(window);
    if (primary_window == nullptr) {
        glfwTerminate();
    }
}

void Window::MakeCurrentContext() {
    glfwMakeContextCurrent(window);
}

void Window::InitializeWindow(int width, int height, std::string title) {
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, primary_window);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }

    if (primary_window != nullptr) {
        glfwMakeContextCurrent(primary_window);
    } else {
        glfwMakeContextCurrent(window);
    }
}

} // namespace poincare
