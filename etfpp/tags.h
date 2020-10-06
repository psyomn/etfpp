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

namespace etfpp {
  namespace tag {
    static const std::uint8_t Version       = 0x83;
    static const std::uint8_t AtomCacheRef  = 0x52;
    static const std::uint8_t SmallInteger  = 0x61;
    static const std::uint8_t Integer       = 0x62;
    static const std::uint8_t Float         = 0x63;
    static const std::uint8_t Atom          = 0x64;
    static const std::uint8_t Reference     = 0x65;
    static const std::uint8_t Port          = 0x66;
    static const std::uint8_t Pid           = 0x67;
    static const std::uint8_t SmallTuple    = 0x68;
    static const std::uint8_t LargeTuple    = 0x69;
    static const std::uint8_t Map           = 0x74;
    static const std::uint8_t Nil           = 0x6a;
    static const std::uint8_t String        = 0x6b;
    static const std::uint8_t List          = 0x6c;
    static const std::uint8_t Binary        = 0x6d;
    static const std::uint8_t SmallBig      = 0x6e;
    static const std::uint8_t LargeBig      = 0x6f;
    static const std::uint8_t NewReference  = 0x72;
    static const std::uint8_t SmallAtom     = 0x73;
    static const std::uint8_t Fun           = 0x75;
    static const std::uint8_t NewFun        = 0x70;
    static const std::uint8_t Export        = 0x71;
    static const std::uint8_t BitBinary     = 0x4d;
    static const std::uint8_t NewFloat      = 0x46;
    static const std::uint8_t AtomUtf8      = 0x76;
    static const std::uint8_t SmallAtomUtf8 = 0x77;
  }
}
