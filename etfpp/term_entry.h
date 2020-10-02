#pragma once

#include <cstdint>
#include <vector>
#include <cstddef>
#include <memory>

namespace etfpp
{
  class TermEntry {
  public:
    virtual std::vector<std::uint8_t> Bytes() const { return { 0xBA, 0xDD }; };
  };

  class TermEntryInteger : public TermEntry
  {
  public:
    explicit TermEntryInteger(std::uint64_t entry) : TermEntry(),
                                                     mEntry(entry) {}
    std::vector<std::uint8_t> Bytes() const override;
  private:
    std::uint64_t mEntry;
  };

  class TermEntryList : public TermEntry
  {
  public:
    TermEntryList() : TermEntry(),
                      mEntries({}) {}

    void Add(std::unique_ptr<TermEntry>&& entry);
    std::vector<std::uint8_t> Bytes() const override;
  private:
    std::vector<std::unique_ptr<TermEntry>> mEntries;
  };

  // class TermEntryTuple : public TermEntry
  // {
  // public:
  //   TermEntryTuple() : TermEntry(),
  //                      mEntries({}) {}

  //   void Add(std::unique_ptr<TermEntry>&& entry);
  //   std::vector<std::uint8_t> Bytes() const override;
  // private:
  //   std::vector<std::unique_ptr<TermEntry>> mEntries;
  // };
}
