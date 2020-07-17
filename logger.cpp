#include <map>
#include <string>
#include <tuple>
#include "gtest/gtest.h"
#include "logger.h"

TEST(Logger, NumArgs)
{
  ASSERT_EQ(0, NARG());
  ASSERT_EQ(1, NARG(0));
  ASSERT_EQ(2, NARG(0, 1));
  ASSERT_EQ(3, NARG(0, 1, 2));
  ASSERT_EQ(4, NARG(0, 1, 2, 3));
  ASSERT_EQ(5, NARG(0, 1, 2, 3, 4));
  ASSERT_EQ(6, NARG(0, 1, 2, 3, 4, 5));
  ASSERT_EQ(7, NARG(0, 1, 2, 3, 4, 5, 6));
  ASSERT_EQ(8, NARG(0, 1, 2, 3, 4, 5, 6, 7));
}

TEST(Logger, ForEach)
{
  int sum = 0;
  auto f = [&sum] (int n) { return sum += n; };

  FOR_EACH(f, 1, 2, 3, 4, 5, 6, 7, 8);
  EXPECT_EQ(36, sum);
}

class TestLogger : public ::testing::Test
{
public:
  TestLogger() = default;
  virtual ~TestLogger() = default;

  static std::map<std::string, std::tuple<std::string, uint32_t, int>> logValues;

protected:
  virtual void SetUp() override
  {
    logValues.clear();
  }

  virtual void TearDown() override
  {
    logValues.clear();
  }
};

std::map<std::string, std::tuple<std::string, uint32_t, int>> TestLogger::logValues;

#define L(...) FOR_EACH(LOG, __VA_ARGS__)
#define LOG(x) TestLogger::logValues[#x] = std::make_tuple(__FILE__, __LINE__, x);

TEST_F(TestLogger, ForEachLogger)
{
  ASSERT_EQ(0u, TestLogger::logValues.size());

  int a = 42, b = -1, c = 496, d = 3;
  L(a, b, c, d); auto ln = __LINE__;

  ASSERT_EQ(4u, TestLogger::logValues.size());
  EXPECT_EQ(std::tie(__FILE__, ln, a), TestLogger::logValues["a"]);
  EXPECT_EQ(std::tie(__FILE__, ln, b), TestLogger::logValues["b"]);
  EXPECT_EQ(std::tie(__FILE__, ln, c), TestLogger::logValues["c"]);
  EXPECT_EQ(std::tie(__FILE__, ln, d), TestLogger::logValues["d"]);
}

template <typename... Args>
void AddLogger(const char* file, int line, const char* name, int value, Args&&... args)
{
  AddLogger(file, line, name, value);
  AddLogger(file, line, std::forward<Args>(args)...);
}

template <>
void AddLogger<>(const char* file, int line, const char* name, int value)
{
  TestLogger::logValues[name] = std::make_tuple(file, line, value);
}

#define L2(...) AddLogger(__FILE__, __LINE__, EXTEND(__VA_ARGS__))

TEST_F(TestLogger, ExpandLogger)
{
  ASSERT_EQ(0u, TestLogger::logValues.size());

  int a = 42, b = -1, c = 496, d = 3;
  L2(a, b, c, d); auto ln = __LINE__;

  ASSERT_EQ(4u, TestLogger::logValues.size());
  EXPECT_EQ(std::tie(__FILE__, ln, a), TestLogger::logValues["a"]);
  EXPECT_EQ(std::tie(__FILE__, ln, b), TestLogger::logValues["b"]);
  EXPECT_EQ(std::tie(__FILE__, ln, c), TestLogger::logValues["c"]);
  EXPECT_EQ(std::tie(__FILE__, ln, d), TestLogger::logValues["d"]);
}
