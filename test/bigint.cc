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


TEST(bigint_operator, test_eq)
{
  const etfpp::BigInt bi1("123123123123123123123123123123123123123123123123123");
  const etfpp::BigInt bi2("123123123123123123123123123123123123123123123123123");
  const etfpp::BigInt bi3("123");
  EXPECT_THAT(bi1 == bi2, true);
  EXPECT_THAT(bi1 == bi3, false);
}

TEST(bigint_operator, test_neq)
{
  const etfpp::BigInt bi1("123123123123123123123123123123123123123123123123123");
  const etfpp::BigInt bi2("123123123123123123123123123123123123123123123123123");
  const etfpp::BigInt bi3("123");
  EXPECT_THAT(bi1 != bi2, false);
  EXPECT_THAT(bi1 != bi3, true);
}

TEST(bigint_operator, test_lt)
{
  const etfpp::BigInt bi1("123123123123123123123123123123123123123123123123123");
  const etfpp::BigInt bi2("123123123123123123123123123123123123123123123123123");
  const etfpp::BigInt bi3("123");
  const etfpp::BigInt bi4("123123123123123123123123123123123123123123123123124");
  const etfpp::BigInt bi5("123123123123123123123123123444444123123123123123123");
  const etfpp::BigInt zero("0");
  const etfpp::BigInt one("1");

  EXPECT_THAT(bi1 < bi1, false);

  EXPECT_THAT(bi1 < bi2, false);
  EXPECT_THAT(bi1 < bi3, false);
  EXPECT_THAT(bi3 < bi1, true);
  EXPECT_THAT(bi1 < bi4, true);

  EXPECT_THAT(bi1 < bi5, true);
  EXPECT_THAT(bi5 < bi1, false);

  EXPECT_THAT(zero < one, true);
  EXPECT_THAT(one < zero, false);

  EXPECT_THAT(etfpp::BigInt("99") <
              etfpp::BigInt("100"), true);
}

TEST(bigint_operator, test_gt)
{
  const etfpp::BigInt bi1("123123123123123123123123123123123123123123123123123");
  const etfpp::BigInt bi2("123123123123123123123123123123123123123123123123123");
  const etfpp::BigInt bi3("123");
  const etfpp::BigInt bi4("123123123123123123123123123123123123123123123123124");
  const etfpp::BigInt bi5("123123123123123123123123123444444123123123123123123");
  const etfpp::BigInt zero("0");
  const etfpp::BigInt one("1");

  EXPECT_THAT(bi1 > bi2, false);
  EXPECT_THAT(bi2 > bi1, false);
  EXPECT_THAT(bi1 > bi3, true);
  EXPECT_THAT(bi3 > bi1, false);
  EXPECT_THAT(bi1 > bi4, false);
  EXPECT_THAT(bi4 > bi1, true);
  EXPECT_THAT(bi5 > bi1, true);
  EXPECT_THAT(bi1 > bi5, false);

  EXPECT_THAT(zero > one, false);
  EXPECT_THAT(one > zero, true);

  EXPECT_THAT(etfpp::BigInt("99") >
              etfpp::BigInt("100"), false);
}

TEST(bigint_operator, test_geq)
{
  const etfpp::BigInt bi1("100");
  const etfpp::BigInt bi2("100");
  const etfpp::BigInt bi3("101");
  EXPECT_THAT(bi1 >= bi3, false);
  EXPECT_THAT(bi1 >= bi2, true);
  EXPECT_THAT(bi3 >= bi1, true);
}

TEST(bigint_operator, test_leq)
{
  const etfpp::BigInt bi1("100");
  const etfpp::BigInt bi2("100");
  const etfpp::BigInt bi3("99");
  EXPECT_THAT(bi1 <= bi3, false);
  EXPECT_THAT(bi1 <= bi2, true);
  EXPECT_THAT(bi3 <= bi1, true);
}

TEST(bigint, to_little_endian_vector)
{
  {
    const std::string input = "18446744073709551616"; // 2 ^ 64 + 1
    const std::vector<std::uint8_t> expected = {
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x01,
    };

    const etfpp::BigInt bi(input);
    const auto lev = bi.ToLittleEndianVector();

    EXPECT_THAT(lev, ::testing::ContainerEq(expected));
  }

  {
    const std::string input = "36893488147419103232"; // 2 x (2 ^ 64) + 1
    const std::vector<std::uint8_t> expected = {
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x02,
    };

    const etfpp::BigInt bi(input);
    const auto lev = bi.ToLittleEndianVector();

    EXPECT_THAT(lev, ::testing::ContainerEq(expected));
  }

  {
    const std::string input = "184467440737095516160"; // (2 ^ 64 + 1) * 10
    const std::vector<std::uint8_t> expected = {
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x0a,
    };

    const etfpp::BigInt bi(input);
    const auto lev = bi.ToLittleEndianVector();

    EXPECT_THAT(lev, ::testing::ContainerEq(expected));
  }

  {
    const std::string input = "4722366482869645213694";
    const std::vector<std::uint8_t> expected = {
      0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff,
      0xfe,
    };

    const etfpp::BigInt bi(input);
    const auto lev = bi.ToLittleEndianVector();
    EXPECT_THAT(lev, ::testing::ContainerEq(expected));
  }
}

// TODO: test bigint("000000000000000000")
// TODO: test bigint("")
// TODO: test bigint("abc")
// TODO: test bigint("123abc123")
