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


  class List : public Byteable
  {
  public:
    void Add(std::unique_ptr<Byteable>&& entry);
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::vector<std::unique_ptr<Byteable>> mEntries;
  };


  class Tuple : public Byteable
  {
  public:
    void Add(std::unique_ptr<Byteable>&& entry);
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::vector<std::unique_ptr<Byteable>> mEntries;
  };


  class SmallInteger : public Byteable
  {
  public:
    explicit SmallInteger(std::uint8_t value) : mEntry(value) {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::uint8_t mEntry;
  };


  class Integer : public Byteable
  {
  public:
    explicit Integer(std::int32_t value) : mEntry(value) {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::int32_t mEntry;
  };
}
