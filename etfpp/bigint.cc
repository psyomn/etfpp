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
#include "bigint.h"
#include "utils.h"

#include <cstddef>
#include <stdexcept>

namespace etfpp
{

  // TODO: should constructor throw on non numeric string?
  BigInt::BigInt(std::string stringifiedInt) :
    mValue(stringifiedInt) {}

  void BigInt::Add(const std::string& num)
  {
    ThrowIfNonNumeric(num);

    std::string smaller = num.size() < mValue.size() ? num : mValue;
    std::string bigger = num.size() >= mValue.size() ? num : mValue;

    std::size_t bigCursor = bigger.size() - 1;
    std::size_t smallCursor = smaller.size() - 1;

    std::uint8_t carry = 0;

    while (true) {
      std::uint8_t current =
        (bigger[bigCursor] - 0x30) + (smaller[smallCursor] - 0x30)
        + carry;

      carry = 0;

      if (current >= 10) {
        carry = 1;
        current -= 10;
      }

      bigger[bigCursor] = static_cast<char>(current + 0x30);

      if (smallCursor == 0)
        break;

      --smallCursor;
      --bigCursor;
    }

    if (bigCursor == 0)  goto finish;

    --bigCursor;
    while (carry != 0) {
      std::uint8_t current = bigger[bigCursor] - 0x30 + carry;
      carry = 0;

      if (current >= 10) {
        carry = 1;
        current -= 10;
      }

      bigger[bigCursor] = static_cast<char>(current + 0x30);

      if (bigCursor == 0)
        break;

      --bigCursor;
    }

  finish:
    if (carry) bigger = "1" + bigger;
    mValue = bigger;
  }

  std::string BigInt::Get() const
  {
    return mValue;
  }

  std::vector<std::uint8_t> BigInt::ToLittleEndianVector() const
  {
    std::vector<std::uint8_t> ret = { 0x00 };
    BigInt bi("0");

    while (bi.Get() != Get()) {
      bi.Add("1");

      std::size_t cursor = 0;
      std::uint8_t carry = 0;

      // for (const auto& c : ret)
      //   std::cout << std::hex << int(c) << " ";
      // std::cout << std::endl;

      // 01 00 00 00 00
      do {
        if (cursor > ret.size() - 1)
          ret.push_back(0);

        if (ret[cursor] == 0xff) {
          ret[cursor] = 0;
          carry = 1;
        } else {
          ret[cursor]++;
          carry = 0;
        }

        ++cursor;
      } while (carry);
    }

    return ret;
  }
}
