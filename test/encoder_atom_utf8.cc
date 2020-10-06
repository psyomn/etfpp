#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/term_entry.h"

TEST(encoder, atom_utf8_simple)
{
  const std::vector<std::uint8_t> name = {
    0xe1, 0xbc, 0x80, 0xce, 0xbc, 0xce,
    0xbc, 0xce, 0xbf, 0xcf, 0x85, 0xce,
    0xb4, 0xce, 0xb9, 0xe1, 0xbd, 0xb2,
    0xcf, 0x82,
  };

  etfpp::AtomUtf8 atom(name);
  const auto actual = atom.Bytes();
  const std::vector<std::uint8_t> expected = {
    0x76,
    0x00, 0x14,
    0xe1, 0xbc, 0x80, 0xce, 0xbc, 0xce,
    0xbc, 0xce, 0xbf, 0xcf, 0x85, 0xce,
    0xb4, 0xce, 0xb9, 0xe1, 0xbd, 0xb2,
    0xcf, 0x82,
  };

  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}