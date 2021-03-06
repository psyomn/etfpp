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

#include "term_entry.h"
#include "byteable.h"

#include <ostream>
#include <vector>
#include <cstdint>

namespace etfpp {
  class Encoder {
  public:
    enum Status { Success = 0, Error };
    explicit Encoder(std::ostream& stream) : mStream(stream),
                                             mLastData({}) {};
    Encoder(const Encoder& other) = delete;
    Encoder(Encoder&& other) = delete;
    Encoder& operator=(Encoder&& other) = delete;
    ~Encoder() {};

    std::vector<std::uint8_t> Encode(Byteable& entry);
  private:
    std::ostream& mStream;
    std::vector<std::uint8_t> mLastData;
  };
}
