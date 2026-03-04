#include <gtest/gtest.h>

#include "a.hpp"

TEST(test, first) {
    int a = 5, b = 6;
    EXPECT_EQ(a::solve(a, b), 11);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
