#include "term.h"

#include <stdexcept>

namespace etfpp
{
  std::vector<std::uint8_t> Term::Bytes() const {
    std::vector<std::uint8_t> ret;

    if (mType == std::nullopt)
      throw std::runtime_error("can't encode unset type");

    // TODO: find better name than tag
    switch (mType.value()) {
    case tag::Version: break;
    case tag::AtomCacheRef: break;
    case tag::SmallInteger: break;
    case tag::Integer: break;
    case tag::Float: break;
    case tag::Atom: break;
    case tag::Reference: break;
    case tag::Port: break;
    case tag::Pid: break;

    case tag::SmallTuple:
    case tag::LargeTuple:
      EncodeTuple();
      break;

    case tag::Map: break;
    case tag::Nil: break;
    case tag::String: break;
    case tag::List: break;
    case tag::Binary: break;
    case tag::SmallBig: break;
    case tag::LargeBig: break;
    case tag::NewReference: break;
    case tag::SmallAtom: break;
    case tag::Fun: break;
    case tag::NewFun: break;
    case tag::Export: break;
    case tag::BitBinary: break;
    case tag::NewFloat: break;
    case tag::AtomUtf8: break;
    case tag::SmallAtomUtf8: break;
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
