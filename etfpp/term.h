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
