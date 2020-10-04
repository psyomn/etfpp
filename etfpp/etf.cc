#include "etf.h"
#include "tags.h"

namespace etfpp {
  std::vector<std::uint8_t> Encoder::Encode(Byteable& entry) {
    std::vector<std::uint8_t> ret;
    ret.push_back(EtfTags::Version);
    const std::vector<std::uint8_t> bytes = entry.Bytes();
    ret.insert(ret.end(), bytes.begin(), bytes.end());

    mLastData = ret;

    return ret;
  }
}
