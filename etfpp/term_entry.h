#pragma once

#include <cstdint>
#include <vector>
#include <cstddef>
#include <memory>

namespace etfpp
{
  class Byteable {
  public:
    virtual std::vector<std::uint8_t> Bytes(void) const = 0;
  };

  class TermEntryList : public Byteable
  {
  public:
    void Add(std::unique_ptr<Byteable>&& entry);
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::vector<std::unique_ptr<Byteable>> mEntries;
  };

  class TermEntryTuple : public Byteable
  {
  public:
    void Add(std::unique_ptr<Byteable>&& entry);
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::vector<std::unique_ptr<Byteable>> mEntries;
  };

  class TermEntryInteger : public Byteable
  {
  public:
    explicit TermEntryInteger(std::int32_t value) : mEntry(value) {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::int32_t mEntry;
  };
}
