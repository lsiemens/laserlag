#include <gtest/gtest.h>

#include <glm/glm.hpp>

#include "minkowski.hpp"

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

TEST(VectorTest, vector_to_float) {
    minkowski::Vector vectorA = minkowski::Vector(2, 1, 3);

    glm::vec3 std_vector_a(1, 3, 2);
    EXPECT_EQ(vectorA.ToGLM(), std_vector_a);
}

TEST(VectorTest, boost) {
    minkowski::Vector time_like = minkowski::Vector(1, 0, 0);

    glm::vec3 time(0, 0, 1);
    glm::mat3 boost = time_like.Boost();
    EXPECT_EQ(boost*time, time_like.ToGLM());

    // nontrivial vector
    time_like = minkowski::Vector(1, 0.5, 0);
    time_like = (1/std::sqrt(-1*time_like*time_like))*time_like;

    boost = time_like.Boost();
    EXPECT_EQ(boost*time, time_like.ToGLM());

    glm::mat3 metric = glm::mat3{{1, 0, 0},
                                 {0, 1, 0},
                                 {0, 0,-1}};
    glm::mat3 new_metric = boost*metric*boost;
    EXPECT_FLOAT_EQ(new_metric[0][0], metric[0][0]);
    EXPECT_FLOAT_EQ(new_metric[1][1], metric[1][1]);
    EXPECT_FLOAT_EQ(new_metric[2][2], metric[2][2]);

    EXPECT_FLOAT_EQ(new_metric[0][1], metric[0][1]);
    EXPECT_FLOAT_EQ(new_metric[0][2], metric[0][2]);
    EXPECT_FLOAT_EQ(new_metric[1][2], metric[1][2]);

    EXPECT_FLOAT_EQ(new_metric[1][0], metric[1][0]);
    EXPECT_FLOAT_EQ(new_metric[2][0], metric[2][0]);
    EXPECT_FLOAT_EQ(new_metric[2][1], metric[2][1]);

    // manual example
    time_like = minkowski::Vector(3/2.0, 1/2.0, 1);
    glm::vec3 space_like = minkowski::Vector(-1/2.0, 3.0, 1/3.0).ToGLM();
    glm::vec3 result = minkowski::Vector(13/12.0, 187/60.0, 17/30.0).ToGLM();

    boost = time_like.Boost();

    glm::vec3 boosted_vector = boost*space_like;
    EXPECT_FLOAT_EQ(boosted_vector[0], result[0]);
    EXPECT_FLOAT_EQ(boosted_vector[1], result[1]);
    EXPECT_FLOAT_EQ(boosted_vector[2], result[2]);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
