#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace etfpp {
  void BytesIntoVec(std::vector<std::uint8_t>& vec, const std::uint64_t value, const std::size_t num);
}
