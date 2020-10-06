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
