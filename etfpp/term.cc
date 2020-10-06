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
#include "term.h"

#include <stdexcept>

namespace etfpp
{
  std::vector<std::uint8_t> Term::Bytes() const {
    std::vector<std::uint8_t> ret;

    if (mType == std::nullopt)
      throw std::runtime_error("can't encode unset type");

    // TODO: find better name than tag
    switch (mType.value()) {
    case tag::Version: break;
    case tag::AtomCacheRef: break;
    case tag::SmallInteger: break;
    case tag::Integer: break;
    case tag::Float: break;
    case tag::Atom: break;
    case tag::Reference: break;
    case tag::Port: break;
    case tag::Pid: break;

    case tag::SmallTuple:
    case tag::LargeTuple:
      EncodeTuple();
      break;

    case tag::Map: break;
    case tag::Nil: break;
    case tag::String: break;
    case tag::List: break;
    case tag::Binary: break;
    case tag::SmallBig: break;
    case tag::LargeBig: break;
    case tag::NewReference: break;
    case tag::SmallAtom: break;
    case tag::Fun: break;
    case tag::NewFun: break;
    case tag::Export: break;
    case tag::BitBinary: break;
    case tag::NewFloat: break;
    case tag::AtomUtf8: break;
    case tag::SmallAtomUtf8: break;
    default:
      throw std::runtime_error("can't encode unknown type");
    }

    return ret;
  }

  std::vector<std::uint8_t> Term::EncodeTuple() const {
    std::vector<std::uint8_t> ret;
    return ret;
  }
}
