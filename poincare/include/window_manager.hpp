#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <memory>
#include <vector>
#include <string>

#include "window.hpp"

namespace poincare {

//class Window;

class WindowManager {
public:
    /// Vector of unique pointers to the Windows that are currently active.
    /// Initaliy this was a vector of Window but after lots of debugging
    /// I found that side effects of `std::vector.push_back` would break
    /// the OpenGL context setup by `Window` even if the vector was not
    /// used. Unique pointers are being used to isolate Window from vector
    /// while allowing appropriate memory management.
    std::vector<std::unique_ptr<Window>> window_list;

    /// Gets and instance of the WindowManager singleton.
    /// return Pointer to an instance of WindowManager.
    static WindowManager* GetInstance();

    void OpenWindow(int width, int height, std::string title);
    bool HasContext();
    void SetVsync(bool vsync);
private:
    static WindowManager* instance;
    bool vsync;

    WindowManager();

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;
};

} // namespace poincare

#endif
