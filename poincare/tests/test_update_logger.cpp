#include <sstream>
#include <iostream>
#include <gtest/gtest.h>


#include "update_logger.hpp"

namespace {

TEST(UpdateLoggerTest, initalize) {
    // move std::cout to a string stream
    std::stringstream buffer;
    std::streambuf* cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    poincare::UpdateLogger* logger = poincare::UpdateLogger::GetInstance();

    EXPECT_EQ(buffer.str(), "");

    logger->log << "test\n";
    EXPECT_EQ(buffer.str(), "");

    logger->Flush();
    EXPECT_EQ(buffer.str(), "test\n\033[A");

    logger->log << "test2\n";
    logger->Flush();
    EXPECT_EQ(buffer.str(), "test\n\033[Atest2\n\033[A");

    logger->log << "test3\n";
    logger->log << "test4\n";
    logger->Flush();
    EXPECT_EQ(buffer.str(), "test\n\033[Atest2\n\033[Atest3\ntest4\n\033[A\033[A");

    // return std::cout to its propper buffer
    std::cout.rdbuf(cout_buffer);
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
