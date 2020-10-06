#pragma once

#include <cstdint>
#include <vector>
#include <cstddef>
#include <memory>
#include <string>

namespace etfpp
{
  class Byteable {
  public:
    virtual std::vector<std::uint8_t> Bytes(void) const = 0;
  };


  class Atom : public Byteable
  {
  public:
    explicit Atom(std::string name) : mName(name) {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::string mName;
  };


  class SmallAtom : public Byteable
  {
  public:
    explicit SmallAtom(std::string name) : mName(name) {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::string mName;
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


  class Float : public Byteable
  {
  public:
    explicit Float(double value) : mEntry(value) {}
    ~Float() {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    double mEntry;
  };


  class String : public Byteable
  {
  public:
    explicit String(std::string value) : mEntry(value) {}
    ~String() {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    static const std::size_t mMaxSize = 0xffff;
    std::string mEntry;
  };


  class Binary : public Byteable
  {
  public:
    explicit Binary(std::vector<std::uint8_t> data) : mData(data) {}
    ~Binary() {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::vector<std::uint8_t> mData;
  };


  class BitBinary : public Byteable
  {
  public:
    BitBinary(std::vector<std::uint8_t> data,
              std::uint8_t bits) :
      mData(data), mBits(bits) {}
    ~BitBinary() {}
    std::vector<std::uint8_t> Bytes(void) const override;
  private:
    std::vector<std::uint8_t> mData;
    std::uint8_t mBits;
  };
}
