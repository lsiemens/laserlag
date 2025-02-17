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
    window_manager->OpenWindow(600, 400, "Sprite example", poincare::ViewMode::kView2D);

    window_manager->window_list[0]->SetColor(glm::vec3(0.5, 0.5, 0.5));

    poincare::Shader shader("resources/basic.vs", "resources/basic.fs");
    poincare::Sprite sprite("resources/basic.vsprite");

    do {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader.shader_id);
        sprite.DrawSprite();

        glfwSwapBuffers(window_manager->window_list[0]->glfw_window);
        glfwPollEvents();
    } while (glfwWindowShouldClose(window_manager->window_list[0]->glfw_window) == 0);
    return 0;
}
