#include <gtest/gtest.h>

#include "vector.hpp"

namespace {

TEST(VectorTest, inner_product) {
    minkowski::Vector time_point = minkowski::Vector(2, 1, 1);
    minkowski::Vector null_point = minkowski::Vector(5, 3, 4);

    EXPECT_EQ(time_point*time_point, -2);
    EXPECT_EQ(null_point*null_point, 0);
    EXPECT_EQ(time_point*null_point, -3);
}

TEST(VectorTest, scalar_product) {
    minkowski::Vector vector = minkowski::Vector(2, 1, 1);

    EXPECT_EQ(0.1L*vector, minkowski::Vector(0.2L, 0.1L, 0.1L));
}

TEST(VectorTest, addition_subtraction) {
    minkowski::Vector vectorA = minkowski::Vector(2, 1, 1);
    minkowski::Vector vectorB = minkowski::Vector(5, 3, 4);

    EXPECT_EQ(vectorA + vectorB, minkowski::Vector(7, 4, 5));
    EXPECT_EQ(vectorA - vectorB, minkowski::Vector(-3, -2, -3));
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
