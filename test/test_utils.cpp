#include <gtest/gtest.h>
#include "utils/utils.hpp"

TEST(UtilsTest, VectorFind)
{
    std::vector<int> int_vec{1,2,3,4};
    EXPECT_EQ(utils::find(int_vec, 1), 0);
    EXPECT_EQ(utils::find(int_vec, 2), 1);
    EXPECT_EQ(utils::find(int_vec, 3), 2);
    EXPECT_EQ(utils::find(int_vec, 4), 3);
    EXPECT_EQ(utils::find(int_vec, 5), -1);

    std::vector<double> float_vec{1.1,2.1,3.1,4.1};
    EXPECT_EQ(utils::find(float_vec, 1.1), 0);
    EXPECT_EQ(utils::find(float_vec, 0.1), -1);

    std::vector<std::string> str_vec{"1.1","2.1","3.1","4.1"};
    EXPECT_EQ(utils::find(str_vec, std::string("1.1")), 0);
    EXPECT_EQ(utils::find(str_vec, std::string("0.1")), -1);
}

TEST(UtilsTest, VectorFindIf)
{
    std::vector<int> int_vec{1,2,3,4};
    EXPECT_EQ(utils::find_if(int_vec, [](int n) { return n % 2 == 0; }), 1);
    EXPECT_EQ(utils::find_if(int_vec, [](int n) { return n % 3 == 0; }), 2);
    EXPECT_EQ(utils::find_if(int_vec, [](int n) { return n % 5 == 0; }), -1);

}