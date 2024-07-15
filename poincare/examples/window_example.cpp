#include <iostream>
#include <string>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.hpp"

int main() {
    poincare::Window window(600, 400, "Single window example", poincare::ViewMode::kView2D);

    window.SetColor(glm::vec3(0.5, 0.5, 0.5));
    window.MakeCurrentContext();

    // initalize triangle
    GLfloat vertices[] = {0, 0.5f, 0, -0.5f, -0.5f, 0, 0.5f, -0.5f, 0};
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    do {
        window.MakeCurrentContext();
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window.glfw_window);
        glfwPollEvents();
    } while (glfwWindowShouldClose(window.glfw_window) == 0);
    return 0;
}
