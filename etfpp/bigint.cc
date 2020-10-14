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
    mValue(stringifiedInt), mSign(Sign::positive) {}

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

  void BigInt::Sub(const std::string& num)
  {
    ThrowIfNonNumeric(num);

    std::uint8_t carry = 0;
    std::size_t cursor = mValue.size() - 1;
    std::size_t subCursor = num.size() - 1;

    while (true) {
      int current =
        int(mValue[cursor] - 0x30) -
        int(num[subCursor] - 0x30) - carry;

      carry = 0;

      if (current < 0) {
        carry = 1;
        current += 10;
      }

      mValue[cursor] = static_cast<char>(current + 0x30);

      if (cursor == 0) break;
      if (subCursor == 0) break;
      --cursor;
      --subCursor;
    }

    while (carry && cursor) {
      --cursor;

      carry = 0;
      int current = int(mValue[cursor] - 0x30) - 1;

      if (current < 0) {
        carry = 1;
        current += 10;
      }

      mValue[cursor] = static_cast<char>(current + 0x30);
    }

    // This would make sense if we were handling negative numbers but
    // we're not.
    // while (carry && subCursor) {}

    TrimLeftChar(mValue, '0');

    if (mValue == "") mValue = "0";
  }

  std::string BigInt::Get() const
  {
    return mValue;
  }

  std::vector<std::uint8_t> BigInt::ToLittleEndianVector() const
  {
    std::vector<std::uint8_t> ret = { 0x00 };
    return ret;
  }

  bool operator== (const BigInt& bi1, const BigInt& bi2)
  {
    const std::string s1 = bi1.Get();
    const std::string s2 = bi2.Get();
    const std::size_t sz1 = s1.size();
    const std::size_t sz2 = s2.size();

    if (sz1 != sz2) return false;

    const std::size_t size = s1.size();
    for (std::size_t i = 0; i < size; ++i)
      if (s1[i] != s2[i]) return false;

    return true;
  }

  bool operator!= (const BigInt& bi1, const BigInt& bi2)
  {
    return !(bi1 == bi2);
  }

  bool operator<  (const BigInt& bi1, const BigInt& bi2)
  {
    const std::string s1 = bi1.Get();
    const std::string s2 = bi2.Get();
    const std::size_t sz1 = s1.size();
    const std::size_t sz2 = s2.size();

    if (sz1 < sz2) return true;
    if (sz1 > sz2) return false;

    for (std::size_t i = 0; i < sz1; ++i) {
      if (s1[i] > s2[i]) return false;
      if (s1[i] < s2[i]) return true;
    }

    return false;
  }

  bool operator>  (const BigInt& bi1, const BigInt& bi2)
  {
    const std::string s1 = bi1.Get();
    const std::string s2 = bi2.Get();
    const std::size_t sz1 = s1.size();
    const std::size_t sz2 = s2.size();

    if (sz1 > sz2) return true;
    if (sz1 < sz2) return false;

    for (std::size_t i = 0; i < sz1; ++i) {
      if (s1[i] > s2[i]) return true;
      if (s1[i] < s2[i]) return false;
    }

    return false;
  }

  bool operator<= (const BigInt& bi1, const BigInt& bi2)
  {
    return !(bi1 > bi2);
  }

  bool operator>= (const BigInt& bi1, const BigInt& bi2)
  {
    return !(bi1 < bi2);
  }
}
