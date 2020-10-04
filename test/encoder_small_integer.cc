#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/term_entry.h"

TEST(encoder, small_integer_number)
{
  etfpp::SmallInteger tesi(0x24);
  auto actual = tesi.Bytes();
  std::vector<std::uint8_t> expected = { 0x61, 0x24 };
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, small_integer_max)
{
  etfpp::SmallInteger tesi(0xff);
  auto actual = tesi.Bytes();
  std::vector<std::uint8_t> expected = { 0x61, 0xff };
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, small_integer_nothingness)
{
  etfpp::SmallInteger tesi(0);
  auto actual = tesi.Bytes();
  std::vector<std::uint8_t> expected = { 0x61, 0x00 };
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
