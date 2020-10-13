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

#include "etfpp/utils.h"

#include <cstdint>

TEST(utils, bytes_into_vec_1_byte)
{
  const std::uint64_t example = 0xAABBCCDDEEFF11;
  const std::vector<std::uint8_t> expected = { 0x11 };
  std::vector<std::uint8_t> actual;
  etfpp::BytesIntoVec(actual, example, 1);
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, bytes_into_vec_2_byte)
{
  const std::uint64_t example = 0xAABBCCDDEEFF11;
  const std::vector<std::uint8_t> expected = { 0xFF, 0x11 };
  std::vector<std::uint8_t> actual;
  etfpp::BytesIntoVec(actual, example, 2);
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, bytes_into_vec_3_bytes)
{
  const std::uint64_t example = 0xAABBCCDDEEFF11;
  const std::vector<std::uint8_t> expected = { 0xEE, 0xFF, 0x11};
  std::vector<std::uint8_t> actual;
  etfpp::BytesIntoVec(actual, example, 3);
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, bytes_into_vec_4_bytes)
{
  const std::uint64_t example = 0xAABBCCDDEEFF11;
  const std::vector<std::uint8_t> expected = { 0xDD, 0xEE, 0xFF, 0x11 };
  std::vector<uint8_t> actual;
  etfpp::BytesIntoVec(actual, example, 4);
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, bytes_into_vec_5_bytes)
{
  const std::uint64_t example = 0xAABBCCDDEEFF11;
  const std::vector<std::uint8_t> expected = {
    0xCC, 0xDD, 0xEE, 0xFF, 0x11
  };

  std::vector<uint8_t> actual;
  etfpp::BytesIntoVec(actual, example, 5);
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, bytes_into_vec_6_bytes)
{
  const std::uint64_t example = 0xAABBCCDDEEFF11;
  const std::vector<std::uint8_t> expected = {
    0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11
  };

  std::vector<uint8_t> actual;
  etfpp::BytesIntoVec(actual, example, 6);
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, bytes_into_vec_7_bytes)
{
  const std::uint64_t example = 0xAABBCCDDEEFF11;
  const std::vector<std::uint8_t> expected = {
    0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11
  };

  std::vector<std::uint8_t> actual;
  etfpp::BytesIntoVec(actual, example, 7);

  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, bytes_into_vec_8_bytes)
{
  const std::uint64_t example = 0xAABBCCDDEEFF1122;
  const std::vector<std::uint8_t> expected = {
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x11, 0x22
  };

  std::vector<std::uint8_t> actual;
  etfpp::BytesIntoVec(actual, example, 8);

  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, double_to_bits)
{
  const double d = 123.0;
  std::uint64_t bits = etfpp::DoubleToBits(d);
  EXPECT_NE(std::uint64_t(d), bits);
  EXPECT_EQ(bits, 0x405ec00000000000);
}

TEST(utils, reverse_bits_test)
{
  struct TestCase {
    std::uint64_t value;
    std::uint64_t numBytes;
    std::uint64_t expected;
  };

  std::vector<TestCase> testCases = {
    {0x11223344AABBCCDD, 1, 0xDD},
    {0x11223344AABBCCDD, 2, 0xDDCC},
    {0x11223344AABBCCDD, 3, 0xDDCCBB},
    {0x11223344AABBCCDD, 4, 0xDDCCBBAA},
    {0x11223344AABBCCDD, 5, 0xDDCCBBAA44},
    {0x11223344AABBCCDD, 6, 0xDDCCBBAA4433},
    {0x11223344AABBCCDD, 7, 0xDDCCBBAA443322},
    {0x11223344AABBCCDD, 8, 0xDDCCBBAA44332211},
  };

  for (auto const& tc : testCases) {
    const std::uint64_t ret = etfpp::ReverseBytes(tc.value, tc.numBytes);
    EXPECT_EQ(ret, tc.expected);
  }
}

TEST(utils, string_int_to_byte_int)
{
  const std::string input = "1234";
  std::vector<std::uint8_t> actual = etfpp::StringIntToByteInt(input);
  const std::vector<std::uint8_t> expected = { 1, 2, 3, 4 };
  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(utils, trim_left_char)
{
  struct TestCase {
    std::string input;
    std::string expected;
  };

  std::vector<TestCase> tcs = {
    {"01", "1"},
    {"001", "1"},
    {"0001", "1"},
    {"00001", "1"},
    {"000001", "1"},

    {"100", "100"},
    {"1000", "1000"},
    {"1000000", "1000000"},
  };

  for (auto& e : tcs) {
    etfpp::TrimLeftChar(e.input, '0');
    EXPECT_EQ(e.input, e.expected);
  }
}
