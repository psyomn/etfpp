#pragma once

#include <cstdint>
#include <vector>
#include <cstddef>

namespace etfpp
{
  class TermEntry {};

  class TermEntryInteger : public TermEntry
  {
  public:
    TermEntryInteger(std::uint64_t entry) : mEntry(entry) {};
  private:
    std::uint64_t mEntry;
  };

  class TermEntryList : public TermEntry
  {
  public:
    explicit TermEntryList() : mEntries({}) {}
    TermEntryList(const TermEntryList& other) = delete;
    TermEntryList(TermEntryList&& other) = delete;
    TermEntryList& operator=(TermEntryList& other) = delete;

    void Add(TermEntry&& entry);
  private:
    std::vector<TermEntry> mEntries;
  };

  class TermEntryTuple : public TermEntry
  {
  public:
    void Add(TermEntry&& entry);
    std::vector<std::uint8_t> Bytes() const;
  private:
    std::vector<TermEntry> mEntries;
  };
}
