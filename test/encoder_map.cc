#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/map.h"
#include "etfpp/integer.h"

#include <memory>

TEST(encoder, map)
{
  etfpp::Map map;
  std::unique_ptr<etfpp::Integer>
    one = std::make_unique<etfpp::Integer>(1),
    two = std::make_unique<etfpp::Integer>(2);

  map.Add(std::move(one), std::move(two));

  auto actual = map.Bytes();
  const std::vector<std::uint8_t> expected = {
    0x74,
    0x00, 0x00, 0x00, 0x01,
    0x62, 0x00, 0x00, 0x00, 0x01,
    0x62, 0x00, 0x00, 0x00, 0x02,
  };

  ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}
