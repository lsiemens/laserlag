#ifndef CONTROLS_HPP
#define CONTROLS_HPP

struct GLFWwindow;

namespace poincare {

class Window;

/// Continuos control axes
struct Continuous {
    double x = 0;
    double y = 0;
    double z = 0;
    double u = 0;
    double v = 0;
};

/// Discrete button inputs
struct Discrete {
    bool close = false;
    bool trigger = false;
    bool uv_interact = false;
};


class Controls {
public:
    Continuous axes;
    Discrete actions;

    /// If `close_action_override` is true then actions.close should be
    /// locked on inresponse to clicking the close button.
    bool close_action_override;

    void LogState();
    private:
};

class KeyboardMouse : public Controls {
public:
    KeyboardMouse(Window* window);
private:
    static void KeyCallback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
    static void CursorPositionCallback(GLFWwindow* glfw_window, double xpos, double ypos);
    static void MouseButtonCallback(GLFWwindow* glfw_window, int button, int action, int mods);
};

} // namespace poincare

#endif
