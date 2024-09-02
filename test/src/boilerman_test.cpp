#include "lib.hpp"
#include <gtest/gtest.h>

#define IS_TESTING true

TEST(LibTests, TestNameIsRight_Zero)
{
  auto lib = library {};
  ASSERT_EQ(lib._name, "boilerman");
}

TEST(LibTests, TestNameIsRight_One)
{
  auto lib = library {};
  ASSERT_NE(lib._name, "not boilerman");
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
