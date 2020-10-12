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
   */
  class BigInt
  {
  public:
    explicit BigInt(std::string stringifiedInt);

    void Add(const std::string& num);
    std::string Get() const;

    std::vector<std::uint8_t> ToLittleEndianVector() const;
  private:
    std::string mValue;
  };
}
