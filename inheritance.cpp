#include "inheritance.h"
#include <iostream>
#include <memory>
#include <gtest/gtest.h>

int Base::Foo()
{
  return 0;
}

int Derived::Foo()
{
  return 42;
}

class TestInheritance : public ::testing::Test
{
public:
  TestInheritance()
    : base(std::make_unique<Derived>())
    , derived(std::make_unique<Derived>())
  {
  }

  virtual ~TestInheritance() = default;

protected:
  virtual void SetUp() override {}
  virtual void TearDown() override {}

  std::unique_ptr<Base> base = nullptr;
  std::unique_ptr<Derived> derived = nullptr;
};

TEST_F(TestInheritance, FirstTest)
{
  EXPECT_EQ(42, base->Foo());
  EXPECT_EQ(42, derived->Foo());
}

