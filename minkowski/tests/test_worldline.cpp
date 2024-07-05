#include <gtest/gtest.h>

#include <stdexcept>

#include "worldline.hpp"
#include "point.hpp"

namespace {

TEST(WorldlineTest, size_and_add_point) {
    minkowski::Worldline worldline;
    minkowski::Point pointA = minkowski::Point(0, 0, 0);
    minkowski::Point pointB = minkowski::Point(3, 1, 2);

    EXPECT_EQ(worldline.size(), 0);
    worldline.AddPoint(pointA);
    EXPECT_EQ(worldline.size(), 1);
    worldline.AddPoint(pointB);
    EXPECT_EQ(worldline.size(), 2);
}

TEST(WorldlineTest, order_and_bounds) {
    minkowski::Worldline worldline;
    minkowski::Point pointA = minkowski::Point(0, 0, 0);
    minkowski::Point pointB = minkowski::Point(3, 1, 2);

    worldline.AddPoint(pointA);
    worldline.AddPoint(pointB);

    EXPECT_EQ(worldline[0], pointB);
    EXPECT_EQ(worldline[worldline.size() - 1], pointA);
    EXPECT_NO_THROW(worldline[worldline.size() - 1]);
    EXPECT_THROW(worldline[worldline.size()], std::out_of_range);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
