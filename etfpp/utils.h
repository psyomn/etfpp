#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace etfpp {
  void BytesIntoVec(std::vector<std::uint8_t>& vec, const std::uint64_t value, const std::size_t num);
  std::string BytesIntoString(const std::vector<uint8_t>& bytes);
}
