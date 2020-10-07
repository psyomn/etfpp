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
#include "etfpp/float.h"
#include "etfpp/utils.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cmath>
#include <limits>
#include <sstream>

TEST(encoder, encode_zero_float)
{
  using namespace std::string_literals;

  etfpp::Float flt(0.0);
  auto actual = flt.Bytes();

  const std::string expected = "c0.00000000000000000000e+00\0\0\0\0\0"s;
  const std::string str = etfpp::BytesIntoString(actual);

  ASSERT_EQ(str, expected);
}

TEST(encoder, encode_simple_float)
{
  using namespace std::string_literals;

  etfpp::Float flt(123.123123321);
  auto actual = flt.Bytes();

  const std::string expected = "c1.23123123320999994235e+02\0\0\0\0\0"s;
  const std::string str = etfpp::BytesIntoString(actual);

  ASSERT_EQ(str, expected);
}

TEST(encoder, encode_bigger_float)
{
  using namespace std::string_literals;

  etfpp::Float flt(1000000000000.123123123);
  auto actual = flt.Bytes();

  const std::string expected = "c1.00000000000012316895e+12\0\0\0\0\0"s;
  const std::string str = etfpp::BytesIntoString(actual);

  ASSERT_EQ(str, expected);
}

TEST(encoder, float_rejects_nan)
{
  double x = std::nan("");
  etfpp::Float flt(x);

  // TODO: maybe there is something in gtest/gmock for these checks
  try {
    flt.Bytes();
    FAIL() << "should reject nan floats";
  } catch(const std::exception&) { /* ok */ }
}

TEST(encoder, float_rejects_inf)
{
  double inf = std::numeric_limits<double>::infinity();
  etfpp::Float flt(inf);

  try {
    flt.Bytes();
    FAIL() << "should reject inf values";
  } catch(const std::exception&) { /* ok */ }
}
