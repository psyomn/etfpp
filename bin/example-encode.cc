/*
   Copyright 2020 Simon (psyomn) Symeonidis

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */
#include "etfpp/etf.h"
#include "etfpp/term_entry.h"

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

int main(void) {
  int counter = 0;

  // TODO: refine API and make the ofstream param in encoder actually
  //   useful.

  // TODO: in the future, planning to do a builder pattern to work on
  //   this.

  auto MakeNameFn = [](int num) -> std::string {
    std::stringstream ss;
    ss << "file-" << num << ".etf";
    return ss.str();
  };

  { // [{}]
    std::ofstream file;
    file.open(MakeNameFn(counter++), std::ios_base::binary);

    etfpp::List list;
    std::unique_ptr<etfpp::Byteable> tuple(new etfpp::Tuple());

    list.Add(std::move(tuple));
    std::stringstream ss;
    etfpp::Encoder encoder(ss);
    const std::vector<std::uint8_t> bytes = encoder.Encode(list);

    for (const auto& b : bytes) file << b;
    file.close();
  }

  { // [123.123]
    std::ofstream file;
    file.open(MakeNameFn(counter++), std::ios_base::binary);

    etfpp::List list;
    std::unique_ptr<etfpp::Byteable> flt(new etfpp::Float(123.123));
    list.Add(std::move(flt));

    std::stringstream ss;
    etfpp::Encoder encoder(ss);
    const std::vector<std::uint8_t> bytes = encoder.Encode(list);

    for (const auto& b : bytes) file << b;
    file.close();
  }

  { // [<<"hello world">>]
    std::ofstream file;
    file.open(MakeNameFn(counter++), std::ios_base::binary);

    std::vector<std::uint8_t> data;
    const std::string example = "hello world this is a binary";

    std::copy(example.begin(), example.end(),
              std::back_inserter(data));

    etfpp::List list;
    std::unique_ptr<etfpp::Byteable> bin(new etfpp::Binary(data));
    list.Add(std::move(bin));

    std::stringstream ss;
    etfpp::Encoder encoder(ss);
    const std::vector<std::uint8_t> bytes = encoder.Encode(list);

    for (const auto& b : bytes) file << b;
    file.close();
  }

  { // [{1,2,3, 123.123, <<"hello">>}]
    using std::unique_ptr;

    std::ofstream file;
    file.open(MakeNameFn(counter++), std::ios_base::binary);

    etfpp::List list;
    unique_ptr<etfpp::Tuple> tuple(new etfpp::Tuple());

    unique_ptr<etfpp::Integer> one = std::make_unique<etfpp::Integer>(1);
    unique_ptr<etfpp::Integer> two = std::make_unique<etfpp::Integer>(2);
    unique_ptr<etfpp::Integer> three = std::make_unique<etfpp::Integer>(3);

    const std::vector<std::uint8_t> vec = {'h', 'e', 'l', 'l', 'o'};
    unique_ptr<etfpp::Binary> bin = std::make_unique<etfpp::Binary>(vec);

    unique_ptr<etfpp::Byteable> flt(new etfpp::Float(123.123));

    tuple->Add(std::move(one));
    tuple->Add(std::move(two));
    tuple->Add(std::move(three));
    tuple->Add(std::move(bin));

    unique_ptr<etfpp::Byteable> tupbyte(tuple.release());
    list.Add(std::move(tupbyte));

    std::stringstream ss;
    etfpp::Encoder encoder(ss);
    const std::vector<std::uint8_t> bytes = encoder.Encode(list);

    for (const auto& b : bytes) file << b;
    file.close();
  }

  { // [one, two, three, ÿapple]
    using std::unique_ptr;

    std::ofstream file;
    file.open(MakeNameFn(counter++), std::ios_base::binary);

    etfpp::List list;

    unique_ptr<etfpp::Atom>
      one = std::make_unique<etfpp::Atom>("one"),
      two = std::make_unique<etfpp::Atom>("two"),
      three = std::make_unique<etfpp::Atom>("three"),
      four = std::make_unique<etfpp::Atom>("\xFF""apple");

    list.Add(std::move(one));
    list.Add(std::move(two));
    list.Add(std::move(three));
    list.Add(std::move(four));

    std::stringstream ss;
    etfpp::Encoder encoder(ss);
    const std::vector<std::uint8_t> bytes = encoder.Encode(list);

    for (const auto& b : bytes) file << b;
    file.close();
  }

  { // bitbinary example
    using std::unique_ptr;

    std::ofstream file;
    file.open(MakeNameFn(counter++), std::ios_base::binary);

    const std::vector<std::uint8_t> data = { 0xaa, 0xbb, 0xcc, 0xdd };
    const std::uint8_t bits = 0x07;

    etfpp::List list;
    unique_ptr<etfpp::BitBinary> bitbinary =
      std::make_unique<etfpp::BitBinary>(data, bits);

    list.Add(std::move(bitbinary));

    std::stringstream ss;
    etfpp::Encoder encoder(ss);
    std::vector<std::uint8_t> bytes = encoder.Encode(list);

    for (const auto& b : bytes) file << b;
    file.close();
  }

  {
    using std::unique_ptr;

    std::ofstream file;
    file.open(MakeNameFn(counter++), std::ios_base::binary);

    const std::vector<std::uint8_t> name = {
      0xe1, 0xbc, 0x80, 0xce, 0xbc, 0xce,
      0xbc, 0xce, 0xbf, 0xcf, 0x85, 0xce,
      0xb4, 0xce, 0xb9, 0xe1, 0xbd, 0xb2,
      0xcf, 0x82,
    };

    unique_ptr<etfpp::AtomUtf8> atom =
      std::make_unique<etfpp::AtomUtf8>(name);

    etfpp::List list;
    list.Add(std::move(atom));

    std::stringstream ss;
    etfpp::Encoder encoder(ss);
    std::vector<std::uint8_t> bytes = encoder.Encode(list);

    for (const auto& b : bytes) file << b;
    file.close();
  }

  return 0;
}
