#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/term_entry.h"

TEST(encoder, bitbinary_simple)
{
  const std::vector<std::uint8_t> bytes = {
    0xaa, 0xbb, 0xcc, 0xdd,
    0xee, 0xff, 0x11, 0x22,
    0x33, 0x44, 0x55, 0x66,
  };
  const std::uint8_t bits = 0x07;

  const etfpp::BitBinary bitbinary(bytes, bits);
  const auto actual = bitbinary.Bytes();
  std::vector<std::uint8_t> expected = {
    0x4d,
    0x00, 0x00, 0x00, 0x0c,
    0x07,
    0xaa, 0xbb, 0xcc, 0xdd,
    0xee, 0xff, 0x11, 0x22,
    0x33, 0x44, 0x55, 0x66,
  };

  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}