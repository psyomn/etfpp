#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/tags.h"
#include "etfpp/term_entry.h"
#include "etfpp/etf.h"

TEST(encoder, encode_positive_integer)
{
  etfpp::TermEntryInteger tei(1);
  auto actual = tei.Bytes();
  auto expected = std::vector<uint8_t>({
      0x62, 0x00, 0x00, 0x00, 0x01
  });
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_max_32_bit_signed_integer)
{
  etfpp::TermEntryInteger tei(~std::int32_t(0));
  auto actual = tei.Bytes();
  auto expected = std::vector<uint8_t>({
      0x62, 0xff, 0xff, 0xff, 0xff
  });
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_nothingness)
{
  etfpp::TermEntryInteger tei(std::uint32_t(0));
  auto actual = tei.Bytes();
  auto expected = std::vector<uint8_t>({
      0x62, 0x00, 0x00, 0x00, 0x00
  });
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_negative_integer)
{
  etfpp::TermEntryInteger tei(-1);
  auto actual = tei.Bytes();
  auto expected = std::vector<uint8_t>({
      0x62, 0xff, 0xff, 0xff, 0xff
  });
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
