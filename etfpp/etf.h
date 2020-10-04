#pragma once

#include "term_entry.h"

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
