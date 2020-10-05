#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/term_entry.h"

TEST(encoder, simple_legacy_atom)
{
  etfpp::Atom atom("apple");
  const std::vector<std::uint8_t> expected = {
    0x64,
    0x00, 0x05,
    'a', 'p', 'p', 'l', 'e'
  };
  auto actual = atom.Bytes();
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, simple_legacy_atom_latin_1)
{
  // it should look like ÿapple
  etfpp::Atom atom("\xFF""apple");
  const std::vector<std::uint8_t> expected = {
    0x64,
    0x00, 0x06,
    0xff, 'a', 'p', 'p', 'l', 'e'
  };
  auto actual = atom.Bytes();
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
