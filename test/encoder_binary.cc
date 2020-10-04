#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/term_entry.h"

TEST(encoder, simple_binary)
{
  std::vector<std::uint8_t> data;
  const std::string example = "hello world this is a binary";

  std::copy(example.begin(), example.end(),
            std::back_inserter(data));

  etfpp::Binary binary(data);
  auto actual = binary.Bytes();
  const std::vector<std::uint8_t> expected = {
    0x6d,
    0x00, 0x00, 0x00, 0x1c,
    'h', 'e', 'l', 'l', 'o', ' ',
    'w', 'o', 'r', 'l', 'd', ' ',
    't', 'h', 'i', 's', ' ',
    'i', 's', ' ',
    'a', ' ',
    'b', 'i', 'n', 'a', 'r', 'y',
  };

  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
