#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/term_entry.h"

TEST(encoder, encode_small_atom)
{
  etfpp::SmallAtom atom("smol");
  auto actual = atom.Bytes();
  const std::vector<std::uint8_t> expected = {
    0x73,
    0x04,
    's', 'm', 'o', 'l',
  };

  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
