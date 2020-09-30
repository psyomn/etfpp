#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/etf.h"
#include "etfpp/term.h"
#include "etfpp/term_entry.h"

#include <sstream>

TEST(encoder, encode_empty_tuple)
{
  std::stringstream ss;
  etfpp::Encoder encoder(ss);
  etfpp::TermEntryList entry;
  etfpp::TermEntryTuple tuple;

  entry.Add(std::move(tuple));
  std::vector<std::uint8_t> actual = encoder.Encode(entry);

  // In erlang terms: [{}]
  const std::vector<std::uint8_t> expected = {
    0x83,
    0x6c, 0x00, 0x00, 0x00, 0x01,
    0x68, 0x00,
    0x6a
  };

  EXPECT_THAT(expected, ::testing::ContainerEq(actual));
}
