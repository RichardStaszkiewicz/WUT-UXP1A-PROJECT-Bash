#include <gtest/gtest.h>
#include "interface.hpp"
#include <iostream>

TEST(sanity_test, sanity_tests)
{
    EXPECT_EQ(true, true);
}

TEST(setter_test, default_constructor)
{
    Interface i;
    i.set_current_dir("./");
    EXPECT_EQ(i.get_current_dir(), "./");
}

TEST(setter_test, stream_constructor)
{
    Interface i(std::cin, std::cout);
    i.set_current_dir("./");
    EXPECT_EQ(i.get_current_dir(), "./");
}

TEST(setter_test, dir_constructor)
{
    Interface i("./");
    EXPECT_EQ(i.get_current_dir(), "./");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
