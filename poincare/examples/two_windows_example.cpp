#include <iostream>
#include <string>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.hpp"

int main() {
    poincare::Window window(600, 400, "Double window example: A", true);
    window.SetColor(glm::vec3(0.5f));

    poincare::Window window2(500, 500, "Double window example: B", true, &window);
    window2.SetColor(glm::vec3(0.25f));

    // initalize triangle VBO
    GLuint VBO;
    GLfloat vertices[] = {0, 0.5f, 0, -0.5f, -0.5f, 0, 0.5f, -0.5f, 0};
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    window.MakeCurrentContext();
    // Add VBO once
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    do {
        window.MakeCurrentContext();
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window2.MakeCurrentContext();
        glClear(GL_COLOR_BUFFER_BIT);

        // Manualy add VBO each frame
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window.glfw_window);
        glfwSwapBuffers(window2.glfw_window);
        glfwPollEvents();
    } while (glfwWindowShouldClose(window.glfw_window) == 0);
    return 0;
}
