#include <gtest/gtest.h>
#include "utils/utils.hpp"

TEST(UtilsTest, VectorFind)
{
    std::vector<int> int_vec{1,2,3,4};
    EXPECT_EQ(utils::find(int_vec, 1), 0);
    EXPECT_EQ(utils::find(int_vec, 1), -1);
}