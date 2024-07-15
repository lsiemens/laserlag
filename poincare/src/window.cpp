#include "window.hpp"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "camera.hpp"
#include "camera2d.hpp"
#include "camera3d.hpp"

namespace poincare {

Window::Window(int width, int height, std::string title, ViewMode view_mode, bool vsync, GLFWwindow* primary_window) : width(width), height(height), glfw_window(nullptr), view_mode(view_mode), primary_window(primary_window) {
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

    double aspect_ratio = static_cast<double>(width)/static_cast<double>(height);
    if (view_mode == ViewMode::kView2D) {
        camera = std::make_shared<Camera2D>(aspect_ratio);
    } else {
        camera = std::make_shared<Camera3D>(aspect_ratio);
    }

    controls = std::make_shared<KeyboardMouse>(this);

    // Window callbacks
    glfwSetWindowUserPointer(glfw_window, this);
    glfwSetFramebufferSizeCallback(glfw_window, FramebufferSizeCallback);
    glfwSetWindowCloseCallback(glfw_window, WindowCloseCallback);
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

void Window::FramebufferSizeCallback(GLFWwindow* glfw_window, int width, int height) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    if (window == nullptr) {
        std::cerr << "No window instance found.\n";
        throw std::runtime_error("Failed to update on window resize.");
    }

    window->width = width;
    window->height = height;
    window->camera->aspect_ratio = static_cast<double>(width)/static_cast<double>(height);

    window->MakeCurrentContext();
    glViewport(0, 0, width, height);
}

void Window::WindowCloseCallback(GLFWwindow* glfw_window) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    if (window == nullptr) {
        std::cerr << "No window instance found.\n";
        throw std::runtime_error("Failed to close window.");
    }

    window->controls->actions.close = true;
    window->controls->close_action_override = true;
}

} // namespace poincare
