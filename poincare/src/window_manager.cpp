#include "window_manager.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

namespace poincare {

WindowManager* WindowManager::instance = nullptr;

WindowManager* WindowManager::GetInstance() {
    if (instance == nullptr) {
        instance = new WindowManager();
    }
    return instance;
}

void WindowManager::OpenWindow(int width, int height, std::string title) {
    // Find pointer to pimary_window for contex sharing
    GLFWwindow* primary_window = nullptr;
    if (window_list.size() > 0) {
        primary_window = window_list[0]->glfw_window;
    }

    std::unique_ptr<Window> window(new Window(width, height, title, vsync, primary_window));
    window_list.push_back(std::move(window));

    if (!HasContext()) {
        std::cerr << "No openGL context found\n";
    }
}

bool WindowManager::HasContext() {
    if (window_list.size() == 0) {
        std::cerr << "window_list size is zero: " << window_list.size() << "\n";
        return false;
    }

    if (glfwGetCurrentContext() == nullptr) {
        std::cerr << "glfwGetCurrentContext() is a null pointer: " << glfwGetCurrentContext() << "\n";
        return false;
    }
    return true;
}

void WindowManager::SetVsync(bool vsync) {
    if (!HasContext()) {
        this->vsync = vsync;
    } else {
        std::cerr << "Cannot change vsync setting. An OpenGL context is already active.\n";
    }
}

WindowManager::WindowManager() : vsync(true) {
}

} // namespace poincare
