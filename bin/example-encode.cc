#include "etfpp/etf.h"
#include "etfpp/term.h"
#include "etfpp/term_entry.h"

#include <iostream>

int main(void) {
  etfpp::Encoder encoder(std::cout);
  etfpp::TermEntry entry;
  (void) encoder.Encode(entry);
  return 0;
}
