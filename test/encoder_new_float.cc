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

#include "etfpp/new_float.h"

TEST(encoder, simple_new_float)
{
  etfpp::NewFloat flt(123.123);
  const std::vector<std::uint8_t> expected = {
    0x46,
    0x40, 0x5E, 0xC7, 0xDF,
    0x3B, 0x64, 0x5A, 0x1D,
  };
  auto actual = flt.Bytes();
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
