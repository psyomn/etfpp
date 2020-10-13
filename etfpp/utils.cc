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
#include "utils.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include <iostream> // TODO REMOVE

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

  std::string BytesIntoString(const std::vector<uint8_t>& bytes)
  {
    std::stringstream ss;
    for (const auto& b: bytes) ss << b;
    return ss.str();
  }

  std::uint64_t ReverseBytes(const std::uint64_t value, const std::size_t num)
  {
    if (num > 8) throw std::runtime_error("can't do more than 8 bytes");
    const std::uint8_t bits = 8 * num;
    std::uint64_t ret = 0;

    for (std::size_t i = 0; i < bits; i += 8) {
      const std::uint8_t byte = (value >> i) & 0xff;
      ret = (ret << 8) | byte;
    }

    return ret;
  }

  std::uint64_t DoubleToBits(const double value)
  {
    union cvrt { double origin; std::uint64_t convert; };
    union cvrt v = {0};
    v.origin = value;
    return v.convert;
  }

  void ThrowIfNonNumeric(const std::string& str)
  {
    const std::string JustNumbers = "1234567890";
    auto ok = str.find_first_not_of(JustNumbers, std::string::npos);
    if (ok != std::string::npos) throw std::runtime_error("illegal character in passed bigint: " + str);
  }

  std::vector<std::uint8_t> StringIntToByteInt(const std::string& str)
  {
    std::vector<std::uint8_t> ret;
    for (const auto& c : str) ret.push_back(std::uint8_t(c - 0x30));
    return ret;
  }

  void TrimLeftChar(std::string& str, const char c)
  {
    str.erase(std::remove(str.begin(), str.end(), c), str.end());
  }
}
