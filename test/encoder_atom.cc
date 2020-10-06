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

TEST(encoder, simple_legacy_atom)
{
  etfpp::Atom atom("apple");
  const std::vector<std::uint8_t> expected = {
    0x64,
    0x00, 0x05,
    'a', 'p', 'p', 'l', 'e'
  };
  auto actual = atom.Bytes();
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(encoder, simple_legacy_atom_latin_1)
{
  // it should look like ÿapple
  etfpp::Atom atom("\xFF""apple");
  const std::vector<std::uint8_t> expected = {
    0x64,
    0x00, 0x06,
    0xff, 'a', 'p', 'p', 'l', 'e'
  };
  auto actual = atom.Bytes();
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
