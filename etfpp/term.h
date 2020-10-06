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

#include "tags.h"
#include "term_entry.h"

#include <vector>
#include <optional>
#include <cstdint>

namespace etfpp
{
  // TODO: this was a simple experiment which I think I might throw
  //   away in the end.
  class Term
  {
  public:
    using u8 = std::uint8_t;

    Term() :
      mType(std::nullopt),
      mTerms({}) {}

    ~Term() {}

    std::vector<u8> Bytes() const;
    inline void Type(std::uint8_t type) { mType = type; }

  private:
    std::optional<std::uint8_t> mType;
    std::vector<Term> mTerms;
    std::uint64_t mInteger;
    double mFloat;

    std::vector<u8> EncodeList() const;
    std::vector<u8> EncodeTuple() const;
  };
}
