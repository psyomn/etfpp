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

#include "etfpp/bitbinary.h"

TEST(encoder, bitbinary_simple)
{
  const std::vector<std::uint8_t> bytes = {
    0xaa, 0xbb, 0xcc, 0xdd,
    0xee, 0xff, 0x11, 0x22,
    0x33, 0x44, 0x55, 0x66,
  };
  const std::uint8_t bits = 0x07;

  const etfpp::BitBinary bitbinary(bytes, bits);
  const auto actual = bitbinary.Bytes();
  std::vector<std::uint8_t> expected = {
    0x4d,
    0x00, 0x00, 0x00, 0x0c,
    0x07,
    0xaa, 0xbb, 0xcc, 0xdd,
    0xee, 0xff, 0x11, 0x22,
    0x33, 0x44, 0x55, 0x66,
  };

  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
