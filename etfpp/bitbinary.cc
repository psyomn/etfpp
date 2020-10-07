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
#include "bitbinary.h"
#include "utils.h"
#include "tags.h"

namespace etfpp
{
  std::vector<std::uint8_t> BitBinary::Bytes(void) const
  {
    std::vector<std::uint8_t> ret = { tag::BitBinary };
    const std::size_t size = mData.size();
    BytesIntoVec(ret, size, 4);
    ret.push_back(mBits);
    ret.insert(ret.end(), mData.begin(), mData.end());
    return ret;
  }
}
