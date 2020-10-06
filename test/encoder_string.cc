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
