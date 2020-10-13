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
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace etfpp
{
  void BytesIntoVec(std::vector<std::uint8_t>& vec, const std::uint64_t value, const std::size_t num);
  std::string BytesIntoString(const std::vector<uint8_t>& bytes);
  __attribute__((pure)) std::uint64_t DoubleToBits(const double value);
  __attribute__((pure)) std::uint64_t ReverseBytes(const std::uint64_t value, const std::size_t num);
  std::vector<std::uint8_t> StringIntToByteInt(const std::string& str);
  void ThrowIfNonNumeric(const std::string& str);
  void TrimLeftChar(std::string& str, const char c);
}
