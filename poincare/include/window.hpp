#ifndef WINDOW_H
#define WINDOW_H

#include <string>

struct GLFWwindow;

namespace poincare {

class Window {
public:
    GLFWwindow* window;

    Window(int width, int height, std::string title, GLFWwindow* primary_window=nullptr);
    ~Window();

    void MakeCurrentContext();
private:
    GLFWwindow* primary_window;
    void InitalizeWindow(int with, int height, std::string title);
};

} // namespace poincare

#endif
