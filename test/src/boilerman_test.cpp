#include "lib.hpp"
#include <gtest/gtest.h>

TEST(LibTests, TestNameIsRight_Zero)
{
  auto const lib = library {};
  ASSERT_EQ(lib._name, "boilerman");
}

TEST(LibTests, TestNameIsRight_One)
{
  auto const lib = library {};
  ASSERT_NE(lib._name, "not boilerman");
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
