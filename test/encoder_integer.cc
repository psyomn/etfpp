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

#include "etfpp/tags.h"
#include "etfpp/term_entry.h"
#include "etfpp/etf.h"

TEST(encoder, encode_positive_integer)
{
  etfpp::Integer tei(1);
  auto actual = tei.Bytes();
  auto expected = std::vector<uint8_t>({
      0x62, 0x00, 0x00, 0x00, 0x01
  });
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_max_32_bit_signed_integer)
{
  etfpp::Integer tei(~std::int32_t(0));
  auto actual = tei.Bytes();
  auto expected = std::vector<uint8_t>({
      0x62, 0xff, 0xff, 0xff, 0xff
  });
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_nothingness)
{
  etfpp::Integer tei(std::uint32_t(0));
  auto actual = tei.Bytes();
  auto expected = std::vector<uint8_t>({
      0x62, 0x00, 0x00, 0x00, 0x00
  });
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, encode_negative_integer)
{
  etfpp::Integer tei(-1);
  auto actual = tei.Bytes();
  auto expected = std::vector<uint8_t>({
      0x62, 0xff, 0xff, 0xff, 0xff
  });
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
