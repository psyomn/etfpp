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

#include "etfpp/atom_utf8.h"

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
