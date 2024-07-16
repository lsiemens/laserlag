#include <gtest/gtest.h>

#include <stdexcept>

#include "minkowski.hpp"

namespace {

TEST(WorldLineTest, size_and_add_point) {
    minkowski::WorldLine world_line;
    minkowski::Point pointA = minkowski::Point(0, 0, 0);
    minkowski::Vector vecA = minkowski::Vector(1, 2, 3);
    minkowski::Point pointB = minkowski::Point(3, 1, 2);
    minkowski::Vector vecB = minkowski::Vector(4, 3, 2);

    EXPECT_EQ(world_line.size(), 0);
    world_line.AddPoint(pointA, vecA);
    EXPECT_EQ(world_line.size(), 1);
    world_line.AddPoint(pointB, vecB);
    EXPECT_EQ(world_line.size(), 2);

    EXPECT_EQ(world_line.path, std::vector<double>({0,0,0,1,2,3,3,1,2,4,3,2}));
}

/*TEST(WorldLineTest, resample) {
    minkowski::WorldLine world_line;
    minkowski::Point pointA = minkowski::Point(0, 0, 0);
    minkowski::Vector vecA = minkowski::Vector(1, 2, 3);
    minkowski::Point pointB = minkowski::Point(3, 1, 2);
    minkowski::Vector vecB = minkowski::Vector(4, 3, 2);

    world_line.AddPoint(pointA, vecA);
    world_line.AddPoint(pointB, vecB);

    EXPECT_EQ(worldline[0], pointB);
    EXPECT_EQ(worldline[worldline.size() - 1], pointA);
    EXPECT_NO_THROW(worldline[worldline.size() - 1]);
    EXPECT_THROW(worldline[worldline.size()], std::out_of_range);
}*/

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
