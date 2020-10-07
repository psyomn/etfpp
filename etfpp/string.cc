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
#include "string.h"
#include "tags.h"
#include "utils.h"

#include <stdexcept>

namespace etfpp
{
  std::vector<std::uint8_t> String::Bytes(void) const
  {
    std::vector<std::uint8_t> ret = { tag::String };

    // TODO: constructor probably should throw instead
    if (mEntry.size() > mMaxSize)
      throw std::runtime_error("can not encode strings larger than 65535 bytes");

    const std::size_t size = mEntry.size();
    BytesIntoVec(ret, size, 2);

    std::copy(mEntry.begin(), mEntry.end(),
              std::back_inserter(ret));

    return ret;
  }
}
