#include <gtest/gtest.h>
#include <string>
#include <fstream>

#include "window.hpp"
#include "shader.hpp"

namespace {

std::string vertex_shader = "#version 330 core\nlayout (location = 0) in vec3 aPos;out vec4 vertexColor;void main() {gl_Position = vec4(aPos, 1.0);vertexColor = vec4(0.5, 0.0, 0.0, 1.0);}";
std::string fragment_shader = "#version 330 core\nout vec4 FragColor;in vec4 vertexColor;void main() {FragColor = vertexColor;}";

TEST(ShaderTest, initalize) {
    std::string vpath = "vert.shader", fpath= "frag.shader";

    std::ofstream vert_file(vpath, std::ios::out);
    if (vert_file.is_open()) {
        vert_file << vertex_shader;
        vert_file.close();
    } else {
        FAIL() << "Failed to write example vertex shader.";
    }

    std::ofstream frag_file(fpath, std::ios::out);
    if (frag_file.is_open()) {
        frag_file << fragment_shader;
        frag_file.close();
    } else {
        FAIL() << "Failed to write example fragment shader.";
    }

    poincare::Window window(600, 600, "Shader Test");
    poincare::Shader test_shader(vpath, fpath);

    EXPECT_NE(test_shader.shader_id, 0);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
