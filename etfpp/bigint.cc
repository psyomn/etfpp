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
}
