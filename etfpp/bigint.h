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

#include <cstdint>
#include <string>
#include <vector>

namespace etfpp
{
  /**
   * This is a pretty poor implementation but should do the trick for
   * now. If this library ever becomes remotely useful this could be a
   * good point for optimization (though it may not be worth it).
   *
   * This does not support sustractions below zero either. Again, this
   * is specialized for this project, and may or may not come back to
   * patch it to something better in the future.
   */
  class BigInt
  {
  public:
    explicit BigInt(std::string stringifiedInt);
    inline bool GetSign() const { return mSign == Sign::positive; }
    std::string Get() const noexcept;

  private:
    enum class Sign { positive, negative };
    std::string mValue;
    Sign mSign;
  };
}
