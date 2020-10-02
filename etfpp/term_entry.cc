#include "etf.h"
#include "term_entry.h"
#include "utils.h"

#include <iostream>

namespace etfpp
{
  // TermEntryList

  void TermEntryList::Add(std::unique_ptr<TermEntry>&& entry)
  {
    mEntries.push_back(entry);
  }

  std::vector<std::uint8_t> TermEntryList::Bytes() const
  {
    std::vector<std::uint8_t> ret;
    const std::size_t size = mEntries.size();
    ret.push_back(EtfTags::List);
    BytesIntoVec(ret, std::uint64_t(size), 4);

    for (const auto& e: mEntries) {
      const std::vector<std::uint8_t> bytes = e->Bytes();
      ret.insert(ret.end(), bytes.begin(), bytes.end());
    }

    // TODO: if improper list, this must not be nil.
    ret.push_back(EtfTags::Nil);
    return ret;
  }

  // // TermTuple

  // void TermEntryTuple::Add(std::unique_ptr<TermEntry>&& entry)
  // {
  //   mEntries.push_back((entry));
  // }

  // std::vector<std::uint8_t> TermEntryTuple::Bytes() const
  // {
  //   std::vector<std::uint8_t> ret;

  //   const std::size_t size = mEntries.size();
  //   if (size < 255) {
  //     ret.push_back(EtfTags::SmallTuple);
  //     ret.push_back(size & 0xff);
  //   } else {
  //     ret.push_back(EtfTags::LargeTuple);
  //     BytesIntoVec(ret, std::uint64_t(size), 4);
  //   }

  //   for (const auto& e : mEntries) {
  //     const std::vector<std::uint8_t> bytes = e.Bytes();
  //     ret.insert(ret.end(), bytes.begin(), bytes.end());
  //   }

  //   return ret;
  // }
}
