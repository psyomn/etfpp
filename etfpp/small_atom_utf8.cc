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
#include "small_atom_utf8.h"

#include "tags.h"
#include "utils.h"

namespace etfpp
{
  std::vector<std::uint8_t> SmallAtomUtf8::Bytes(void) const
  {
    std::vector<std::uint8_t> ret = { tag::SmallAtomUtf8 };
    const std::size_t size = mName.size();
    BytesIntoVec(ret, size, 1);
    ret.insert(ret.end(), mName.begin(), mName.end());
    return ret;
  }
}
