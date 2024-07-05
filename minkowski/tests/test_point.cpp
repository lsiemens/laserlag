#include "point.hpp"

#include <gtest/gtest.h>

namespace {

TEST(PointTest, foo) {
    minkowski::Point location;

    EXPECT_EQ(location.foo(), 0);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
