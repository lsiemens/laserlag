#include <sstream>
#include <iostream>
#include <regex>

#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

#include "frame_timer.hpp"
#include "update_logger.hpp"

namespace {

int BasicTimerStringMatching(std::string input, std::string& output, double& fps, double& dt) {
    // Regular expression to match the numbers in the format
    std::regex re("FPS: ([0-9]*\\.?[0-9]+) Δt \\(in ms\\): ([0-9]*\\.?[0-9]+)");
    std::smatch match;

    if (std::regex_search(input, match, re)) {
        // Extract the numbers as strings
        std::string fpsStr = match[1].str();
        std::string dtStr = match[2].str();

        // Convert the extracted strings to doubles
        fps = std::stod(fpsStr);
        dt = std::stod(dtStr);

        // Replace the numbers in the original string in reverse order to
        // preserve the match points
        output = input;
        output.replace(match.position(2), dtStr.length(), "DT_VALUE");
        output.replace(match.position(1), fpsStr.length(), "FPS_VALUE");
    } else {
        return 0;
    }
    return 1;
}

TEST(FrameTimerTest, timming) {
    if (!glfwInit()) {
        FAIL() << "GLFW Faild to initalize.";
    }
    glfwSetTime(0);

    poincare::BasicTimer timer = poincare::BasicTimer();

    double t_0 = glfwGetTime();
    double dt = timer.Timer();
    EXPECT_NEAR(dt, t_0, 1e-5);

    while (glfwGetTime() < 0.001) {
        // delay
    }
    double t_1 = glfwGetTime();

    dt = timer.Timer();
    EXPECT_NEAR(dt, t_1 - t_0, 1e-5);
    EXPECT_NE(t_1, t_0);
}

TEST(FrameTimerTest, printing) {
    // move std::cout to a string stream
    std::stringstream buffer;
    std::streambuf* cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    if (!glfwInit()) {
        FAIL() << "GLFW Faild to initalize.";
    }
    glfwSetTime(0);

    poincare::BasicTimer timer = poincare::BasicTimer();
    poincare::UpdateLogger* logger = poincare::UpdateLogger::GetInstance();

    double t = glfwGetTime();
    double dt = timer.Timer();
    while (glfwGetTime() < 1.5L) {
        while (glfwGetTime() - t < 0.001L) {
            // delay
        }
        t = glfwGetTime();
        dt = timer.Timer();
    }
    logger->Flush();

    std::string buffer_stripped;
    double dt_stripped, fps_stripped;
    if (!BasicTimerStringMatching(buffer.str(), buffer_stripped, fps_stripped, dt_stripped)) {
        FAIL() << "REGEX Failed to match the string: " << buffer.str();
    }
    EXPECT_EQ(buffer_stripped, "FPS: FPS_VALUE Δt (in ms): DT_VALUE\n\033[A");
    EXPECT_NEAR(fps_stripped, 1000, 1);
    EXPECT_NEAR(dt_stripped, 0.001L, 1e-5);

    // return std::cout to its propper buffer
    std::cout.rdbuf(cout_buffer);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
