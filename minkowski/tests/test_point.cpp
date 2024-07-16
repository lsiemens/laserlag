#include <gtest/gtest.h>

#include <glm/glm.hpp>

#include "minkowski.hpp"

namespace {

TEST(PointTest, point_difference) {
    minkowski::Point origin = minkowski::Point(0, 1, 2);
    minkowski::Point point = minkowski::Point(3, 2, 1);

    EXPECT_EQ((point - origin), minkowski::Vector(3, 1, -1));
    EXPECT_EQ((point - origin)*(point - origin), -7);
}

TEST(PointTest, point_vector_sum) {
    minkowski::Point origin = minkowski::Point(0, 1, 2);
    minkowski::Point point = minkowski::Point(3, 2, 1);
    minkowski::Vector diffrence = minkowski::Vector(0.1, 0.2, 0.3);

    EXPECT_EQ(origin + diffrence, minkowski::Point(0.1, 1.2, 2.3));
    EXPECT_EQ(origin + (point - origin), point);
}

TEST(PointTest, point_to_float) {
    minkowski::Point point = minkowski::Point(0, 1, 2);

    glm::vec3 std_vector_point(1, 2, 0);
    EXPECT_EQ(point.ToGLM(), std_vector_point);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
