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

#include "etfpp/small_atom_utf8.h"

TEST(encoder, small_atom_utf8)
{
  std::vector<std::uint8_t> name = {
    0xce, 0x94, 0xce, 0xb9, 0xce,
    0xbf, 0xce, 0xb3, 0xce, 0xad,
    0xce, 0xbd, 0xce, 0xb7, 0xcf,
    0x82,
  };

  etfpp::SmallAtomUtf8 atom(name);
  const auto actual = atom.Bytes();

  const std::vector<std::uint8_t> expected = {
    0x77,
    0x10,
    0xce, 0x94, 0xce, 0xb9, 0xce,
    0xbf, 0xce, 0xb3, 0xce, 0xad,
    0xce, 0xbd, 0xce, 0xb7, 0xcf,
    0x82,
  };

  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
