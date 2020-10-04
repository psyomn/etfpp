#include "etfpp/etf.h"
#include "etfpp/term_entry.h"

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

int main(void) {
  int counter = 0;

  auto MakeNameFn = [](int num) -> std::string {
    std::stringstream ss;
    ss << "file-" << num << ".etf";
    return ss.str();
  };

  {
    std::ofstream file;
    file.open(MakeNameFn(counter++), std::ios_base::binary);

    etfpp::List list;
    std::unique_ptr<etfpp::Byteable> tuple(new etfpp::Tuple());

    list.Add(std::move(tuple));
    std::stringstream ss;
    etfpp::Encoder encoder(ss);
    const std::vector<std::uint8_t> bytes = encoder.Encode(list);
    for (const auto& b : bytes) {
      file << b;
    }

    file.close();
  }

  return 0;
}
