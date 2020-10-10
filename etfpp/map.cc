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
#include "byteable.h"
#include "map.h"
#include "tags.h"
#include "utils.h"

#include <utility>
#include <vector>

namespace etfpp
{
  void Map::Add(unique_byteable&& key, unique_byteable&& value) {
    std::pair<unique_byteable, unique_byteable> pair =
      std::make_pair(std::move(key), std::move(value));
    mKeyValues.push_back(std::move(pair));
  }

  std::vector<std::uint8_t> Map::Bytes(void) const {
    std::vector<std::uint8_t> ret = { tag::Map };
    const std::size_t size = mKeyValues.size();
    BytesIntoVec(ret, size, 4);

    for (const auto& kv : mKeyValues) {
      const auto keyBytes = kv.first->Bytes();
      ret.insert(ret.end(), keyBytes.begin(), keyBytes.end());

      const auto valueBytes = kv.second->Bytes();
      ret.insert(ret.end(), valueBytes.begin(), valueBytes.end());
    }

    return ret;
  }
}
