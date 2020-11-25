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

#include <array>
#include <cstddef>
#include <stdexcept>

namespace etfpp
{
  // TODO: should constructor throw on non numeric string?
  BigInt::BigInt(std::string stringifiedInt) :
    mValue(stringifiedInt), mSign(Sign::positive) {}

  std::string BigInt::Get() const noexcept
  {
    return mValue;
  }

  std::vector<std::uint8_t> BigInt::ToLittleEndianVector() const
  {
    std::vector<std::uint8_t> ret;
    return ret;
  }

  bool operator== (const BigInt& bi1, const BigInt& bi2)
  {
    const std::string s1 = bi1.Get();
    const std::string s2 = bi2.Get();
    return s1 == s2;
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
