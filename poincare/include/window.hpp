#ifndef WINDOW_H
#define WINDOW_H

#include <string>

// keep this befor all other OpenGL libraries
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

struct GLFWwindow;

namespace poincare {

class Window {
public:
    GLFWwindow* glfw_window;
    GLuint vertex_array_id;

    Window(int width, int height, std::string title, bool wait_vsync=true, Window* primary_window=nullptr);
    ~Window();

    void MakeCurrentContext();
    void SetColor(glm::vec3 color=glm::vec3(0.5f));
private:
    Window* primary_window;
    void InitializeWindow(int with, int height, std::string title);
};

} // namespace poincare

#endif
