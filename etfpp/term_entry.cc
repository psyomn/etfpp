#include "etf.h"
#include "tags.h"
#include "term_entry.h"
#include "utils.h"

#include <cmath>
#include <iostream>
#include <limits>

namespace etfpp
{
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

namespace etfpp
{
  std::vector<std::uint8_t> Float::Bytes(void) const
  {
    if (mEntry != mEntry)
      throw std::runtime_error("can't encode NaN");

    if (mEntry == std::numeric_limits<double>::infinity())
      throw std::runtime_error("can't encode Inf");

    std::vector<std::uint8_t> ret = { tag::Float };

    constexpr std::size_t buffsize = 32;
    char buffer[buffsize] = {0};

    if (snprintf(buffer, buffsize - 1, "%.20e", mEntry) < 0)
      throw std::runtime_error("could not format buffer");

    for (std::size_t i = 0; i < buffsize - 1; ++i)
      ret.push_back(std::uint8_t(buffer[i]));

    return ret;
  }
}

namespace etfpp
{
  std::vector<std::uint8_t> String::Bytes(void) const
  {
    std::vector<std::uint8_t> ret = { tag::String };

    // TODO: constructor probably should throw instead
    if (mEntry.size() > mMaxSize)
      throw std::runtime_error("can not encode strings larger than 65535 bytes");

    const std::size_t size = mEntry.size();
    BytesIntoVec(ret, size, 2);

    std::copy(mEntry.begin(), mEntry.end(),
              std::back_inserter(ret));

    return ret;
  }
}

namespace etfpp
{
  std::vector<std::uint8_t> Binary::Bytes(void) const
  {
    std::vector<std::uint8_t> ret = { tag::Binary };
    const std::size_t size = mData.size();
    BytesIntoVec(ret, size, 4);
    ret.insert(ret.end(), mData.begin(), mData.end());
    return ret;
  }
}

namespace etfpp
{
  std::vector<std::uint8_t> Atom::Bytes(void) const
  {
    // TODO check for max bounds here
    std::vector<std::uint8_t> ret = { tag::Atom };
    const std::size_t size = mName.size();
    BytesIntoVec(ret, size, 2);
    ret.insert(ret.end(), mName.begin(), mName.end());
    return ret;
  }
}

namespace etfpp
{
  std::vector<std::uint8_t> SmallAtom::Bytes(void) const
  {
    // TODO check for max bounds here
    std::vector<std::uint8_t> ret = { tag::SmallAtom };
    const std::size_t size = mName.size();
    BytesIntoVec(ret, size, 1);

    for (const auto& b : mName)
      ret.push_back(static_cast<std::uint8_t>(b));

    return ret;
  }
}

namespace etfpp
{
  std::vector<std::uint8_t> BitBinary::Bytes(void) const
  {
    std::vector<std::uint8_t> ret = { tag::BitBinary };
    const std::size_t size = mData.size();
    BytesIntoVec(ret, size, 4);
    ret.push_back(mBits);
    ret.insert(ret.end(), mData.begin(), mData.end());
    return ret;
  }
}
