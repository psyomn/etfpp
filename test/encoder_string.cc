#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/term_entry.h"

TEST(encoder, string_simple)
{
  etfpp::String etfstr("hello");
  auto actual = etfstr.Bytes();
  const std::vector<std::uint8_t> expected = {
    0x6b,
    0x00, 0x05,
    'h', 'e', 'l', 'l', 'o'
  };

  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, string_cant_over_max)
{
  constexpr std::size_t vecsize = 0xffff + 10;
  const std::vector<uint8_t> temp(vecsize, 'a');

  std::string str;
  std::copy(temp.begin(), temp.end(),
            std::back_inserter(str));

  try {
    etfpp::String s(str);
    s.Bytes();
    FAIL() << "bigger strings that 65535 should not be encodable";
  } catch(std::exception&) { /* ok */ }
}
