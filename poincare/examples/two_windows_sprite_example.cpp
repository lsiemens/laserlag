#include <iostream>
#include <string>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "sprite.hpp"
#include "window_manager.hpp"

int main() {
    poincare::WindowManager* window_manager = poincare::WindowManager::GetInstance();
    window_manager->OpenWindow(600, 400, "Double window sprite example: A", poincare::ViewMode::kView2D);
    window_manager->window_list[0]->SetColor(glm::vec3(0.5f));

    window_manager->OpenWindow(500, 500, "Double window sprite example: B", poincare::ViewMode::kView2D);
    window_manager->window_list[1]->SetColor(glm::vec3(0.25f));

    poincare::Shader shader("resources/basic.vs", "resources/basic.fs");
    poincare::Sprite sprite("resources/basic.vsprite");

    do {
        for (auto& window : window_manager->window_list) {
            window->MakeCurrentContext();
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shader.shader_id);
            sprite.DrawSprite();

            glfwSwapBuffers(window->glfw_window);
        }
        glfwPollEvents();
    } while (glfwWindowShouldClose(window_manager->window_list[0]->glfw_window) == 0);
    return 0;
}
