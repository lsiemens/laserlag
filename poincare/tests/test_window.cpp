#include <gtest/gtest.h>
#include <string>

#include "window.hpp"

namespace {

TEST(WindowTest, initialize) {
    poincare::Window window(600, 600, "TEST", poincare::ViewMode::kView2D);
    EXPECT_NE(window.glfw_window, nullptr);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
