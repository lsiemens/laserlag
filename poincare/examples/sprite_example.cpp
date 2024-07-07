#include <iostream>
#include <string>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.hpp"
#include "shader.hpp"
#include "sprite.hpp"

int main() {
    poincare::Window window(600, 400, "Sprite example");

    window.SetColor(glm::vec3(0.5, 0.5, 0.5));
    window.MakeCurrentContext();

    poincare::Shader shader("resources/vertex.shader", "resources/fragment.shader");
    poincare::Sprite sprite("resources/vector_sprite.dat");

    do {
        window.MakeCurrentContext();
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader.shader_id);
        sprite.DrawSprite();

        glfwSwapBuffers(window.glfw_window);
        glfwPollEvents();
    } while (glfwWindowShouldClose(window.glfw_window) == 0);
    return 0;
}
