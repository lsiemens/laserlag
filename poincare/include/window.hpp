#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <memory>

// keep this befor all other OpenGL libraries
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "controls.hpp"

struct GLFWwindow;

namespace poincare {

class Camera;
class Controls;

enum class ViewMode {
    kView2D,
    kView3D,
};

class Window {
public:
    int width;
    int height;
    GLFWwindow* glfw_window;
    GLuint vertex_array_id;

    ViewMode view_mode;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Controls> controls;

    Window(int width, int height, std::string title, ViewMode view_mode, bool vsync=true, GLFWwindow* primary_window=nullptr);
    ~Window();

    void MakeCurrentContext();
    void SetColor(glm::vec3 color=glm::vec3(0.5f));
private:
    GLFWwindow* primary_window;

    void InitializeWindow(int with, int height, std::string title);
    static void FramebufferSizeCallback(GLFWwindow* glfw_window, int width, int height);
    static void WindowCloseCallback(GLFWwindow* glfw_window);
};

} // namespace poincare

#endif

