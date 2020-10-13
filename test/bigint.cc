#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/bigint.h"

TEST(bigint, init_sign)
{
  const etfpp::BigInt bi("1");
  ASSERT_EQ(bi.GetSign(), true);
}

TEST(bigint, initialize_with_string_value)
{
  const std::string expected = "112312312312323123123123123123123123123123123";
  const etfpp::BigInt bi(expected);

  ASSERT_EQ(bi.Get(), expected);
}

TEST(bigint_add, add_one_to_zero)
{
  const std::string
    expected = "1",
    add = "1",
    input = "0";

  etfpp::BigInt bi(input);
  bi.Add(add);

  ASSERT_EQ(bi.Get(), expected);
}

TEST(bigint_add, one_and_one)
{
  const std::string one = "1";
  etfpp::BigInt bi(one);
  bi.Add(one);

  ASSERT_EQ(bi.Get(), "2");
}

TEST(bigint_add, simple_add)
{
  const std::string
    first = "123",
    toAdd = "1",
    expect = "124";

  etfpp::BigInt bi(first);
  bi.Add(toAdd);

  ASSERT_EQ(bi.Get(), expect);
}

TEST(bigint_add, simple_add_carry)
{
  const std::string
    first = "999",
    toAdd = "1",
    expect = "1000";

  etfpp::BigInt bi(first);
  bi.Add(toAdd);

  ASSERT_EQ(bi.Get(), expect);
}

TEST(bigint_add, add_value_edge)
{
  const std::string
    first = "999999999999999999999999999999999999999999",
    toAdd = "1",
    expect = "1000000000000000000000000000000000000000000";

  etfpp::BigInt bi(first);
  bi.Add(toAdd);

  ASSERT_EQ(bi.Get(), expect);
}

TEST(bigint_add, add_1_to_9)
{
  const std::string
    first = "9",
    toAdd = "1",
    expect = "10";

  etfpp::BigInt bi(first);
  bi.Add(toAdd);

  ASSERT_EQ(bi.Get(), expect);
}

TEST(bigint_add, add_upto_N)
{
  etfpp::BigInt bi("0");
  const std::size_t N = 1000;

  for (std::size_t i = 0; i < N; ++i) bi.Add("1");

  ASSERT_EQ(bi.Get(), "1000");
}

TEST(bigint_add, add_111_to_222)
{
  etfpp::BigInt bi("111");
  bi.Add("222");
  ASSERT_EQ(bi.Get(), "333");
}

TEST(bigint_add, add_big_number)
{
  {
    etfpp::BigInt bi("");
    bi.Add("5000000000000000000000");
    ASSERT_EQ(bi.Get(), "10000000000000000005000000000000000000000");
  }

  {
    etfpp::BigInt bi("190000000000000000000000000000000000000000000");
    bi.Add("10000000000000000000000000000000000000000000");
    ASSERT_EQ(bi.Get(), "200000000000000000000000000000000000000000000");
  }
}

TEST(bigint_sub, simple_subs)
{
  struct TestCase {
    std::string init;
    std::string toSub;
    std::string expected;
  };

  const std::vector<TestCase> tcs = {
    {"5", "1", "4"},
    {"15", "1", "14"},
    {"115", "1", "114"},
  };

  for (const auto& tc : tcs) {
    etfpp::BigInt bi(tc.init);
    bi.Sub(tc.toSub);
    ASSERT_THAT(bi.Get(), tc.expected);
  }
}

TEST(bigint_sub, evoke_carry)
{
  struct TestCase {
    std::string init;
    std::string toSub;
    std::string expect;
  };

  const std::vector<TestCase> tcs = {
    {"10", "1", "9"},
    {"20", "1", "19"},
    {"30", "1", "29"},
    {"100", "1", "99"},
    {"1000", "1", "999"},
  };

  for (const auto& tc : tcs) {
    etfpp::BigInt bi(tc.init);
    bi.Sub(tc.toSub);
    ASSERT_THAT(bi.Get(), tc.expect);
  }
}

TEST(bigint_sub, remove_eq)
{
  etfpp::BigInt bi("123");
  bi.Sub("123");
  ASSERT_THAT(bi.Get(), "0");
}

TEST(bigint_sub, sub_many)
{
  etfpp::BigInt bi("1000");

  ASSERT_THAT(bi.Get(), "1000");

  bi.Sub("250");
  ASSERT_THAT(bi.Get(), "750");

  bi.Sub("250");
  ASSERT_THAT(bi.Get(), "500");

  bi.Sub("250");
  ASSERT_THAT(bi.Get(), "250");

  bi.Sub("250");
  ASSERT_THAT(bi.Get(), "0");
}

TEST(bigint, remove_bigger_value)
{
  {
    etfpp::BigInt bi("18446744073709551616");
    bi.Sub("18446744073709551615");
    ASSERT_THAT(bi.Get(), "1");
  }

  {
    etfpp::BigInt bi("18446744073709551616");
    bi.Sub("18446744073709551616");
    ASSERT_THAT(bi.Get(), "0");
  }

  {
    etfpp::BigInt bi("10000000000000000000000000000000000000000000000000000000000000000");
    bi.Sub("1");
    ASSERT_THAT(bi.Get(), "9999999999999999999999999999999999999999999999999999999999999999");
  }
}

TEST(bigint, to_little_endian_vector)
{
  const std::string input = "18446744073709551616"; // 2 ^ 64 + 1
  const std::vector<std::uint8_t> expected = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x01,
  };

  etfpp::BigInt bi(input);
  const auto lev = bi.ToLittleEndianVector();

  ASSERT_THAT(lev, ::testing::ContainerEq(expected));
}

// TODO: test bigint("")
// TODO: test bigint("abc")
// TODO: test bigint("123abc123")
