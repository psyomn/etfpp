/*
   Copyright 2020 Simon (psyomn) Symeonidis

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/etf.h"
#include "etfpp/term_entry.h"
#include "etfpp/list.h"
#include "etfpp/term.h"
#include "etfpp/tuple.h"

#include <sstream>

TEST(encoder, encode_empty_tuple)
{
  std::stringstream ss;
  etfpp::Tuple tuple;

  std::vector<std::uint8_t> actual = tuple.Bytes();
  const std::vector<std::uint8_t> expected = { 0x68, 0x00 };

  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_list_tuple)
{
  std::stringstream ss;
  etfpp::List list;
  std::unique_ptr<etfpp::Byteable> tuple(new etfpp::Tuple());

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
  etfpp::List list;
  std::unique_ptr<etfpp::Byteable> tuple(new etfpp::Tuple());

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
