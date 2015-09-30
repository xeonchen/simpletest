#include <gtest/gtest.h>

TEST(SimpleTest, FirstTest)
{
  // ASSERT_* can be replaced by EXPECT_*.
  // ASSERT_* yields fatal failure and EXPECT_* yields nonfatal failure.

  ASSERT_TRUE(true);
  ASSERT_FALSE(false);

  ASSERT_EQ(42, 42);
  ASSERT_NE(false, true);
  ASSERT_LT(1, 2);
  ASSERT_LE(1, 1);
  EXPECT_LE(1, 2);
  ASSERT_GT(1, 0);
  ASSERT_GE(1, 0);
  ASSERT_GE(0, 0);

  ASSERT_STREQ("foo", "foo");
  ASSERT_STRNE("foo", "Foo");
  ASSERT_STRCASEEQ("foo", "FOO");
  ASSERT_STRCASENE("foo", "bar");
  ASSERT_STRCASENE("", nullptr);
}
