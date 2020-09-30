#include "utils.h"

#include <stdexcept>

namespace etfpp {
  void BytesIntoVec(std::vector<std::uint8_t>& vec, const std::uint64_t value, const std::size_t num)
  {
    switch (num) {
    case 8: vec.push_back((value & 0xFF00000000000000) >> 56); [[fallthrough]];
    case 7: vec.push_back((value & 0x00FF000000000000) >> 48); [[fallthrough]];
    case 6: vec.push_back((value & 0x0000FF0000000000) >> 40); [[fallthrough]];
    case 5: vec.push_back((value & 0x000000FF00000000) >> 32); [[fallthrough]];
    case 4: vec.push_back((value & 0x00000000FF000000) >> 24); [[fallthrough]];
    case 3: vec.push_back((value & 0x0000000000FF0000) >> 16); [[fallthrough]];
    case 2: vec.push_back((value & 0x000000000000FF00) >>  8); [[fallthrough]];
    case 1: vec.push_back(value & 0x00000000000000FF);         break;
    default:
      throw std::runtime_error("can only do up to 8 bytes");
    }
  }
}
