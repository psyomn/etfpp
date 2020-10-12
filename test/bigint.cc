#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/bigint.h"

TEST(bigint, add_one_to_zero)
{
  const std::string
    expected = "1",
    add = "1",
    input = "0";

  etfpp::BigInt bi(input);
  bi.Add(add);

  ASSERT_EQ(bi.Get(), expected);
}

TEST(bigint, initialize_with_string_value)
{
  const std::string expected = "112312312312323123123123123123123123123123123";
  const etfpp::BigInt bi(expected);

  ASSERT_EQ(bi.Get(), expected);
}

TEST(bigint, one_and_one)
{
  const std::string one = "1";
  etfpp::BigInt bi(one);
  bi.Add(one);

  ASSERT_EQ(bi.Get(), "2");
}

TEST(bigint, simple_add)
{
  const std::string
    first = "123",
    toAdd = "1",
    expect = "124";

  etfpp::BigInt bi(first);
  bi.Add(toAdd);

  ASSERT_EQ(bi.Get(), expect);
}

TEST(bigint, simple_add_carry)
{
  const std::string
    first = "999",
    toAdd = "1",
    expect = "1000";

  etfpp::BigInt bi(first);
  bi.Add(toAdd);

  ASSERT_EQ(bi.Get(), expect);
}

TEST(bigint, add_value_edge)
{
  const std::string
    first = "999999999999999999999999999999999999999999",
    toAdd = "1",
    expect = "1000000000000000000000000000000000000000000";

  etfpp::BigInt bi(first);
  bi.Add(toAdd);

  ASSERT_EQ(bi.Get(), expect);
}

TEST(bigint, add_1_to_9)
{
  const std::string
    first = "9",
    toAdd = "1",
    expect = "10";

  etfpp::BigInt bi(first);
  bi.Add(toAdd);

  ASSERT_EQ(bi.Get(), expect);
}

TEST(bigint, add_upto_N)
{
  etfpp::BigInt bi("0");
  const std::size_t N = 1000;

  for (std::size_t i = 0; i < N; ++i) {
    std::cout << i << std::endl;
    bi.Add("1");
  }

  ASSERT_EQ(bi.Get(), "1000");
}

#include <iostream>
#include <thread>
#include <unistd.h>
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
