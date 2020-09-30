#include "etf.h"
#include "term_entry.h"

namespace etfpp
{
  void TermEntryList::Add(TermEntry&& entry)
  {
    mEntries.push_back(entry);
  }

  void TermEntryTuple::Add(TermEntry&& entry)
  {
    mEntries.push_back(entry);
  }

  std::vector<std::uint8_t> TermEntryTuple::Bytes() const
  {
    std::vector<std::uint8_t> ret;

    const std::size_t size = mEntries.size();
    if (size < 255) {
      ret.push_back(EtfTags::SmallTuple);
      ret.push_back(size & 0xff);
    } else {
      ret.push_back(EtfTags::LargeTuple);
    }

    return ret;
  }
}
