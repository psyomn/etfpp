#include "etf.h"

namespace etfpp {
  std::vector<std::uint8_t> Encoder::Encode(TermEntry& entry) {
    mData.push_back(EtfVersion);

    return mData;
  }
}
