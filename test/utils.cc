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
