#pragma once

#include "term_entry.h"

#include <vector>

namespace etfpp
{
  class Term
  {
  public:
    explicit Term() {}
    ~Term() {}
    Term(const Term& other) = delete;
    Term(Term&& other) = delete;
    Term& operator=(Term&& other) = delete;

  private:
  };
}
