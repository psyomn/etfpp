#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/etf.h"
#include "etfpp/term_entry.h"
#include "etfpp/term.h"

#include <sstream>

TEST(encoder, encode_empty_tuple)
{
  std::stringstream ss;
  etfpp::TermEntryTuple tuple;

  std::vector<std::uint8_t> actual = tuple.Bytes();
  const std::vector<std::uint8_t> expected = { 0x68, 0x00 };

  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_list_tuple)
{
  std::stringstream ss;
  etfpp::TermEntryList list;
  std::unique_ptr<etfpp::Byteable> tuple(new etfpp::TermEntryTuple());

  list.Add(std::move(tuple));
  const auto actual = list.Bytes();
  const std::vector<std::uint8_t> expected = {
    0x6c, 0x00, 0x00, 0x00, 0x01, 0x68, 0x00, 0x6a
  };
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_empty_list_tuple_etf)
{
  std::stringstream ss;
  etfpp::Encoder encoder(ss);
  etfpp::TermEntryList list;
  std::unique_ptr<etfpp::Byteable> tuple(new etfpp::TermEntryTuple());

  list.Add(std::move(tuple));
  std::vector<std::uint8_t> actual = encoder.Encode(list);

  // In erlang terms: [{}]
  const std::vector<std::uint8_t> expected = {
    0x83,
    0x6c, 0x00, 0x00, 0x00, 0x01,
    0x68, 0x00,
    0x6a
  };

  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}
