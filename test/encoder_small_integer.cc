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
#include "etfpp/small_integer.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(encoder, small_integer_number)
{
  etfpp::SmallInteger tesi(0x24);
  auto actual = tesi.Bytes();
  std::vector<std::uint8_t> expected = { 0x61, 0x24 };
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, small_integer_max)
{
  etfpp::SmallInteger tesi(0xff);
  auto actual = tesi.Bytes();
  std::vector<std::uint8_t> expected = { 0x61, 0xff };
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, small_integer_nothingness)
{
  etfpp::SmallInteger tesi(0);
  auto actual = tesi.Bytes();
  std::vector<std::uint8_t> expected = { 0x61, 0x00 };
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
