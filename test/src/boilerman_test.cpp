#include "lib.hpp"
#include <gtest/gtest.h>

#include <filesystem>

#define IS_TESTING true

TEST(LibTests, FileExistsTest)
{
  ASSERT_TRUE(std::filesystem::exists("resources/meow.txt"));
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
