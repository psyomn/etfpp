#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "etfpp/term_entry.h"
#include "etfpp/utils.h"

#include <cmath>
#include <limits>
#include <sstream>

TEST(encoder, encode_zero_float)
{
  etfpp::Float flt(0.0);
  auto actual = flt.Bytes();

  const std::string expected = "c0.00000000000000000000e+00";
  const std::string str = etfpp::BytesIntoString(actual);

  ASSERT_EQ(str, expected);
}

TEST(encoder, encode_simple_float)
{
  etfpp::Float flt(123.123123321);
  auto actual = flt.Bytes();

  const std::string expected = "c1.23123123320999994235e+02";
  const std::string str = etfpp::BytesIntoString(actual);

  ASSERT_EQ(str, expected);
}

TEST(encoder, encode_bigger_float)
{
  etfpp::Float flt(1000000000000.123123123);
  auto actual = flt.Bytes();

  const std::string expected = "c1.00000000000012316895e+12";
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
