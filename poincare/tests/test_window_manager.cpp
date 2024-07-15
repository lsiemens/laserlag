#include <gtest/gtest.h>
#include <string>

#include "window_manager.hpp"

namespace {

TEST(WindowTest, initialize) {
    poincare::WindowManager* window_manager = poincare::WindowManager::GetInstance();
    EXPECT_FALSE(window_manager->HasContext());

    window_manager->OpenWindow(600, 600, "TEST", poincare::ViewMode::kView2D);
    EXPECT_NE(window_manager->window_list[0]->glfw_window, nullptr);
    EXPECT_TRUE(window_manager->HasContext());

    window_manager->OpenWindow(600, 600, "TEST2", poincare::ViewMode::kView3D);
    EXPECT_NE(window_manager->window_list[1]->glfw_window, nullptr);
    EXPECT_TRUE(window_manager->HasContext());
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
