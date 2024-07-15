#include "controls.hpp"

#include <iostream>
#include <stdexcept>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.hpp"
#include "update_logger.hpp"

namespace poincare {

void Controls::LogState() {
    UpdateLogger* logger = UpdateLogger::GetInstance();
    logger->log << "Continuos Axes:\n";
    logger->log << "[X: " << axes.x << " Y: " << axes.y << " Z: " << axes.z << "]\n";
    logger->log << "[U: " << axes.u << " V: " << axes.v << "]\n";
    logger->log << "Discrete Actions:\n";
    logger->log << "Close: ";
    if (actions.close) {
        logger->log << "True";
    } else {
        logger->log << "False";
    }

    logger->log << " Trigger: ";
    if (actions.trigger) {
        logger->log << "True";
    } else {
        logger->log << "False";
    }

    logger->log << " UV Interact: ";
    if (actions.uv_interact) {
        logger->log << "True";
    } else {
        logger->log << "False";
    }
    logger->log << "\n";
}

KeyboardMouse::KeyboardMouse(Window* window) {
    glfwSetKeyCallback(window->glfw_window, KeyCallback);
    glfwSetCursorPosCallback(window->glfw_window, CursorPositionCallback);
    glfwSetMouseButtonCallback(window->glfw_window, MouseButtonCallback);
}

void KeyboardMouse::KeyCallback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    std::shared_ptr<KeyboardMouse> keyboard_mouse = std::static_pointer_cast<KeyboardMouse>(window->controls);

    if (keyboard_mouse == nullptr) {
        std::cerr << "No controls found for window.\n";
        throw std::runtime_error("Failed to update user input.");
    }

    // Continuos Axes
    // X axis
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        keyboard_mouse->axes.x += 1;
    }

    if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
        keyboard_mouse->axes.x -= 1;
    }

    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        keyboard_mouse->axes.x -= 1;
    }

    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
        keyboard_mouse->axes.x += 1;
    }

    // Y axis
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        keyboard_mouse->axes.y += 1;
    }

    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
        keyboard_mouse->axes.y -= 1;
    }

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        keyboard_mouse->axes.y -= 1;
    }

    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
        keyboard_mouse->axes.y += 1;
    }

    // Z axis
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        keyboard_mouse->axes.z += 1;
    }

    if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
        keyboard_mouse->axes.z -= 1;
    }

    if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS) {
        keyboard_mouse->axes.z -= 1;
    }

    if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_RELEASE) {
        keyboard_mouse->axes.z += 1;
    }

    // Discrete Actions
    // Close action
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        keyboard_mouse->actions.close = true;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        keyboard_mouse->actions.close = false || keyboard_mouse->close_action_override;
    }

    // Trigger action
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        keyboard_mouse->actions.trigger = true;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        keyboard_mouse->actions.trigger = false;
    }

    // Add this so scancode and mods are used to suppress compiler warnings
    if (key == -1) {
        std::cout << "Unknown key | scancode: " << scancode << " mods: " << mods << "\n";
    }

}

void KeyboardMouse::CursorPositionCallback(GLFWwindow* glfw_window, double xpos, double ypos) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    std::shared_ptr<KeyboardMouse> keyboard_mouse = std::static_pointer_cast<KeyboardMouse>(window->controls);

    if (keyboard_mouse == nullptr) {
        std::cerr << "No controls found for window.\n";
        throw std::runtime_error("Failed to update user input.");
    }

    double width = static_cast<double>(window->width);
    double height = static_cast<double>(window->height);

    keyboard_mouse->axes.u = (2*xpos/width - 1);
    keyboard_mouse->axes.v = (1 - 2*ypos/height);
}

void KeyboardMouse::MouseButtonCallback(GLFWwindow* glfw_window, int button, int action, int mods) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    std::shared_ptr<KeyboardMouse> keyboard_mouse = std::static_pointer_cast<KeyboardMouse>(window->controls);

    if (keyboard_mouse == nullptr) {
        std::cerr << "No controls found for window.\n";
        throw std::runtime_error("Failed to update user input.");
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        keyboard_mouse->actions.uv_interact = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        keyboard_mouse->actions.uv_interact = false;
    }

    // Add this so mods are used to suppress compiler warnings
    if (button == -1) {
        std::cout << "Unknown button | mods: " << mods << "\n";
    }
}

} // namespace poincare
