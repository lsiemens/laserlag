#include <gtest/gtest.h>
#include <string>

#include "window.hpp"

namespace {

TEST(WindowTest, initalize) {
    poincare::Window window(600, 600, "TEST");
    EXPECT_NE(window.window, nullptr);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
