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
#include "tags.h"
#include "tuple.h"
#include "utils.h"

namespace etfpp
{
  void Tuple::Add(std::unique_ptr<Byteable>&& entry)
  {
    mEntries.push_back(std::move(entry));
  }

  std::vector<std::uint8_t> Tuple::Bytes(void) const
  {
    std::vector<std::uint8_t> ret;

    const std::size_t size = mEntries.size();
    if (size < 255) {
      ret.push_back(tag::SmallTuple);
      ret.push_back(size & 0xff);
    } else {
      ret.push_back(tag::LargeTuple);
      BytesIntoVec(ret, std::uint64_t(size), 4);
    }

    for (const auto& e : mEntries) {
      const std::vector<std::uint8_t> bytes = e->Bytes();
      ret.insert(ret.end(), bytes.begin(), bytes.end());
    }

    return ret;
  }
}
