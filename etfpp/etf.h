#pragma once

#include "term_entry.h"

#include <ostream>
#include <vector>
#include <cstdint>

namespace etfpp {
  enum EtfTags {
    EtfVersion    = 0x83,

    AtomCacheRef  = 0x52,
    SmallInteger  = 0x61,
    Integer       = 0x62,
    Float         = 0x63,
    Atom          = 0x64,
    Reference     = 0x65,
    Port          = 0x66,
    Pid           = 0x67,
    SmallTuple    = 0x68,
    LargeTuple    = 0x69,
    Map           = 0x74,
    Nil           = 0x6a,
    String        = 0x6b,
    List          = 0x6c,
    Binary        = 0x6d,
    SmallBig      = 0x6e,
    LargeBig      = 0x6f,
    NewReference  = 0x72,
    SmallAtom     = 0x73,
    Fun           = 0x75,
    NewFun        = 0x70,
    Export        = 0x71,
    BitBinary     = 0x4d,
    NewFloat      = 0x46,
    AtomUtf8      = 0x76,
    SmallAtomUtf8 = 0x77,
  };

  class Encoder {
  public:
    enum Status { Success = 0, Error };
    explicit Encoder(std::ostream& stream) : mStream(stream),
                                             mData({}) {};
    Encoder(const Encoder& other) = delete;
    Encoder(Encoder&& other) = delete;
    Encoder& operator=(Encoder&& other) = delete;
    ~Encoder() {};

    std::vector<std::uint8_t> Encode(TermEntry& entry);
  private:
    std::ostream& mStream;
    std::vector<std::uint8_t> mData;
  };
}
