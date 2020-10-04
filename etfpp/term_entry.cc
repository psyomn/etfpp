#include "etf.h"
#include "tags.h"
#include "term_entry.h"
#include "utils.h"

#include <iostream>

namespace etfpp
{
  // List
  void List::Add(std::unique_ptr<Byteable>&& entry)
  {
    mEntries.push_back(std::move(entry));
  }

  std::vector<std::uint8_t> List::Bytes(void) const
  {
    std::vector<std::uint8_t> ret;
    const std::size_t size = mEntries.size();
    ret.push_back(tag::List);
    BytesIntoVec(ret, std::uint64_t(size), 4);

    for (const auto& e : mEntries) {
      const std::vector<std::uint8_t> bytes = e->Bytes();
      ret.insert(ret.end(), bytes.begin(), bytes.end());
    }

    // TODO: if improper list, this must not be nil.
    ret.push_back(tag::Nil);
    return ret;
  }
}

namespace etfpp
{
  // TermTuple
  void Tuple::Add(std::unique_ptr<Byteable>&& entry)
  {
    mEntries.push_back(std::move(entry));
  }

  std::vector<std::uint8_t> Tuple::Bytes(void) const
  {
    std::vector<std::uint8_t> ret;

    const std::size_t size = mEntries.size();
    if (size < 255) {
      ret.push_back(tag::SmallTuple);
      ret.push_back(size & 0xff);
    } else {
      ret.push_back(tag::LargeTuple);
      BytesIntoVec(ret, std::uint64_t(size), 4);
    }

    for (const auto& e : mEntries) {
      const std::vector<std::uint8_t> bytes = e->Bytes();
      ret.insert(ret.end(), bytes.begin(), bytes.end());
    }

    return ret;
  }
}


namespace etfpp
{
  std::vector<std::uint8_t> SmallInteger::Bytes(void) const
  {
    return std::vector<std::uint8_t>({ tag::SmallInteger, mEntry });
  }
}


namespace etfpp
{
  std::vector<std::uint8_t> Integer::Bytes(void) const
  {
    std::vector<std::uint8_t> ret = { tag::Integer };
    BytesIntoVec(ret, std::uint64_t(mEntry), 4);
    return ret;
  }
}
