#include "term.h"

#include <stdexcept>

namespace etfpp
{
  std::vector<std::uint8_t> Term::Bytes() const {
    std::vector<std::uint8_t> ret;

    if (mType == std::nullopt)
      throw std::runtime_error("can't encode unset type");

    // TODO: find better name than EtfTags
    switch (mType.value()) {
    case EtfTags::Version: break;
    case EtfTags::AtomCacheRef: break;
    case EtfTags::SmallInteger: break;
    case EtfTags::Integer: break;
    case EtfTags::Float: break;
    case EtfTags::Atom: break;
    case EtfTags::Reference: break;
    case EtfTags::Port: break;
    case EtfTags::Pid: break;

    case EtfTags::SmallTuple:
    case EtfTags::LargeTuple:
      EncodeTuple();
      break;

    case EtfTags::Map: break;
    case EtfTags::Nil: break;
    case EtfTags::String: break;
    case EtfTags::List: break;
    case EtfTags::Binary: break;
    case EtfTags::SmallBig: break;
    case EtfTags::LargeBig: break;
    case EtfTags::NewReference: break;
    case EtfTags::SmallAtom: break;
    case EtfTags::Fun: break;
    case EtfTags::NewFun: break;
    case EtfTags::Export: break;
    case EtfTags::BitBinary: break;
    case EtfTags::NewFloat: break;
    case EtfTags::AtomUtf8: break;
    case EtfTags::SmallAtomUtf8: break;
    default:
      throw std::runtime_error("can't encode unknown type");
    }

    return ret;
  }

  std::vector<std::uint8_t> Term::EncodeTuple() const {
    std::vector<std::uint8_t> ret;
    return ret;
  }
}
