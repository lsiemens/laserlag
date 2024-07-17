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

TEST(WorldLineTest, GetPosition) {
    minkowski::WorldLine world_line;
    minkowski::Point pointA = minkowski::Point(0, 1, 2);
    minkowski::Vector vecA = minkowski::Vector(3, 4, 5);
    minkowski::Point pointB = minkowski::Point(1, 1, 0);
    minkowski::Vector vecB = minkowski::Vector(1, 1, 0);
    minkowski::Point pointC = minkowski::Point(2, 2, 0);
    minkowski::Vector vecC = minkowski::Vector(1, 1, 0);
    minkowski::Point pointD = minkowski::Point(3, 3, 0);
    minkowski::Vector vecD = minkowski::Vector(1, 1, 0);
    minkowski::Point pointE = minkowski::Point(4, 4, 0);
    minkowski::Vector vecE = minkowski::Vector(1, 1, 0);

    world_line.AddPoint(pointA, vecA);
    world_line.AddPoint(pointB, vecB);
    world_line.AddPoint(pointC, vecC);
    world_line.AddPoint(pointD, vecD);
    world_line.AddPoint(pointE, vecE);

    EXPECT_EQ(world_line.GetPosition(0), pointA);
    EXPECT_EQ(world_line.GetPosition(3), pointD);
    EXPECT_THROW(world_line.GetPosition(-1), std::runtime_error);
    EXPECT_NO_THROW(world_line.GetPosition(0));
    EXPECT_NO_THROW(world_line.GetPosition(world_line.size() - 1));
    EXPECT_THROW(world_line.GetPosition(world_line.size()), std::runtime_error);
}

TEST(WorldLineTest, GetVelocity) {
    minkowski::WorldLine world_line;
    minkowski::Point pointA = minkowski::Point(0, 1, 2);
    minkowski::Vector vecA = minkowski::Vector(3, 4, 5);
    minkowski::Point pointB = minkowski::Point(1, 1, 0);
    minkowski::Vector vecB = minkowski::Vector(1, 1, 0);
    minkowski::Point pointC = minkowski::Point(2, 2, 0);
    minkowski::Vector vecC = minkowski::Vector(1.5, 1.5, 0);
    minkowski::Point pointD = minkowski::Point(3.5, 3.5, 0);
    minkowski::Vector vecD = minkowski::Vector(2, 2, 0);
    minkowski::Point pointE = minkowski::Point(5.5, 5.5, 0);
    minkowski::Vector vecE = minkowski::Vector(2.5, 2.5, 0);

    world_line.AddPoint(pointA, vecA);
    world_line.AddPoint(pointB, vecB);
    world_line.AddPoint(pointC, vecC);
    world_line.AddPoint(pointD, vecD);
    world_line.AddPoint(pointE, vecE);

    EXPECT_EQ(world_line.GetVelocity(0), vecA);
    EXPECT_EQ(world_line.GetVelocity(3), vecD);
    EXPECT_THROW(world_line.GetVelocity(-1), std::runtime_error);
    EXPECT_NO_THROW(world_line.GetVelocity(0));
    EXPECT_NO_THROW(world_line.GetVelocity(world_line.size() - 1));
    EXPECT_THROW(world_line.GetVelocity(world_line.size()), std::runtime_error);
}

TEST(WorldLineTest, GetLightConeIntersection) {
    minkowski::WorldLine world_line;
    minkowski::Point pointA = minkowski::Point(0, 0, 0);
    minkowski::Vector vecA = minkowski::Vector(1, 0.5, 0);
    minkowski::Point pointB = minkowski::Point(1, 0.5, 0);
    minkowski::Vector vecB = minkowski::Vector(1, 0.5, 0);
    minkowski::Point pointC = minkowski::Point(2, 1, 0);
    minkowski::Vector vecC = minkowski::Vector(1, 0.5, 0);
    minkowski::Point pointD = minkowski::Point(3, 1.5, 0);
    minkowski::Vector vecD = minkowski::Vector(1, 0.5, 0);
    minkowski::Point pointE = minkowski::Point(4, 2, 0);
    minkowski::Vector vecE = minkowski::Vector(1, 0.5, 0);

    world_line.AddPoint(pointA, vecA);
    world_line.AddPoint(pointB, vecB);
    world_line.AddPoint(pointC, vecC);
    world_line.AddPoint(pointD, vecD);
    world_line.AddPoint(pointE, vecE);

    minkowski::Point cone_pos;
    minkowski::Point inter_pos;
    minkowski::Vector inter_vel;

    cone_pos = minkowski::Point(4, 2, 2);
    world_line.GetLightConeIntersection(cone_pos, inter_pos, inter_vel);
    EXPECT_NEAR((inter_pos - cone_pos)*(inter_pos - cone_pos), 0, 1e-5);

    cone_pos = minkowski::Point(4, 0, 2);
    world_line.GetLightConeIntersection(cone_pos, inter_pos, inter_vel);
    EXPECT_NEAR((inter_pos - cone_pos)*(inter_pos - cone_pos), 0, 1e-5);

    cone_pos = minkowski::Point(4, 20, -22);
    world_line.GetLightConeIntersection(cone_pos, inter_pos, inter_vel);
    EXPECT_NEAR((inter_pos - cone_pos)*(inter_pos - cone_pos), 0, 1e-5);

    cone_pos = minkowski::Point(-1, 2, -2);
    EXPECT_THROW(world_line.GetLightConeIntersection(cone_pos, inter_pos, inter_vel), std::runtime_error);
}

TEST(WorldLineTest, resample) {
    minkowski::WorldLine world_line;
    minkowski::Point pointA = minkowski::Point(0, 1, 2);
    minkowski::Vector vecA = minkowski::Vector(3, 4, 5);
    minkowski::Point pointB = minkowski::Point(1, 1, 0);
    minkowski::Vector vecB = minkowski::Vector(1, 1, 0);
    minkowski::Point pointC = minkowski::Point(2, 2, 0);
    minkowski::Vector vecC = minkowski::Vector(1, 1, 0);
    minkowski::Point pointD = minkowski::Point(3, 3, 0);
    minkowski::Vector vecD = minkowski::Vector(1, 1, 0);
    minkowski::Point pointE = minkowski::Point(4, 4, 0);
    minkowski::Vector vecE = minkowski::Vector(1, 1, 0);

    world_line.AddPoint(pointA, vecA);
    world_line.AddPoint(pointB, vecB);
    world_line.AddPoint(pointC, vecC);
    world_line.AddPoint(pointD, vecD);
    world_line.AddPoint(pointE, vecE);

    std::vector<float> full({1,2,0,4,5,3,1,0,1,1,0,1,2,0,2,1,0,1,3,0,3,1,0,1,4,0,4,1,0,1});
    std::vector<float> part({1,2,0,4,5,3,2,0,2,1,0,1,4,0,4,1,0,1});
    EXPECT_EQ(world_line.Resample(0.5, 100), full);
    EXPECT_EQ(world_line.Resample(1.0, 100), full);
    EXPECT_NE(world_line.Resample(2.0, 100), full);
    EXPECT_EQ(world_line.Resample(2.0, 100), part);


    minkowski::WorldLine world_line2;
    world_line2.AddPoint(pointA, vecA);
    world_line2.AddPoint(pointB, vecB);
    world_line2.AddPoint(pointC, vecC);
    world_line2.AddPoint(pointD, vecD);

    full = std::vector<float>({1,2,0,4,5,3,1,0,1,1,0,1,2,0,2,1,0,1,3,0,3,1,0,1});
    part = std::vector<float>({1,2,0,4,5,3,2,0,2,1,0,1});
    EXPECT_EQ(world_line2.Resample(0.5, 100), full);
    EXPECT_EQ(world_line2.Resample(1.0, 100), full);
    EXPECT_NE(world_line.Resample(2.0, 100), full);
    EXPECT_EQ(world_line2.Resample(2.0, 100), part);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
