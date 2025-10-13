#include "scanner.h"
#include "gtest/gtest.h"
#include <iostream>

namespace Gnocchi {
using namespace std;

class ScannerTest : public testing::Test {
public:
  Scanner *obj;
  LocationProvider provider{"mock.gno"};

  virtual void SetUp() override { obj = new Scanner(provider); }

  virtual void TearDown() override {
    provider.reset();
    delete obj;
  }

  template <typename T>
  void testIdentifyLiteral(const char *text, Parser::symbol_kind_type type,
                           T value) {
    stringstream stream;
    stream << text;
    obj->switch_streams(&stream, nullptr);
    Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(type, token.kind());
    ASSERT_EQ(value, token.value.as<T>());
  }
};

TEST_F(ScannerTest, testIdentifyTrue) {
  this->testIdentifyLiteral<bool>(
      "true", Parser::symbol_kind_type::S_BOOL_LITERAL, true);
}

TEST_F(ScannerTest, testIdentifyFalse) {
  this->testIdentifyLiteral<bool>(
      "false", Parser::symbol_kind_type::S_BOOL_LITERAL, false);
}

TEST_F(ScannerTest, testIdentifyUnsignedIntegerZero) {
  this->testIdentifyLiteral<unsigned long long>(
      "0", Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 0);
}

TEST_F(ScannerTest, testIdentifyUnsignedIntegerArbitrary) {
  this->testIdentifyLiteral<unsigned long long>(
      "1234567890", Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL,
      1234567890);
}

TEST_F(ScannerTest, testIdentifyUnsignedIntegerMax) {
  this->testIdentifyLiteral<unsigned long long>(
      "18446744073709551615",
      Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL,
      18446744073709551615ULL);
}

TEST_F(ScannerTest, testIdentifyUnsignedIntegerWithE) {
  this->testIdentifyLiteral<unsigned long long>(
      "3e0", Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 3);
}

TEST_F(ScannerTest, testIdentifyUnsignedIntegerWithHighPowerOfTen) {
  this->testIdentifyLiteral<unsigned long long>(
      "3e9", Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 3000000000);
}

TEST_F(ScannerTest, testIdentifyUnsignedIntegerBinary) {
  this->testIdentifyLiteral<unsigned long long>(
      "0b101", Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 5);
}

TEST_F(ScannerTest, testIdentifyUnsignedIntegerOctal) {
  this->testIdentifyLiteral<unsigned long long>(
      "0o1234567", Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL,
      342391);
}

TEST_F(ScannerTest, testIdentifyUnsignedIntegerHex) {
  this->testIdentifyLiteral<unsigned long long>(
      "0x123456789ABCDEF0",
      Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL,
      1311768467463790320ull);
}

TEST_F(ScannerTest, testIdentifySignedIntegerPlusZero) {
  this->testIdentifyLiteral<long long>(
      "+0", Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, 0);
}

TEST_F(ScannerTest, testIdentifySignedIntegerMinusZero) {
  this->testIdentifyLiteral<long long>(
      "-0", Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, 0);
}

TEST_F(ScannerTest, testIdentifySignedIntegerArbitraryPositive) {
  this->testIdentifyLiteral<long long>(
      "+1234567890", Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL,
      1234567890);
}

TEST_F(ScannerTest, testIdentifySignedIntegerArbitraryNegative) {
  this->testIdentifyLiteral<long long>(
      "-9876543210", Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL,
      -9876543210);
}

TEST_F(ScannerTest, testIdentifySignedIntegerMin) {
  this->testIdentifyLiteral<long long>(
      "-9223372036854775808",
      Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL,
      -9223372036854775807LL - 1);
}

TEST_F(ScannerTest, testIdentifySignedIntegerMax) {
  this->testIdentifyLiteral<long long>(
      "+9223372036854775807",
      Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL,
      9223372036854775807LL);
}

TEST_F(ScannerTest, testIdentifySignedIntegerWithE) {
  this->testIdentifyLiteral<long long>(
      "-15e0", Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, -15);
}

TEST_F(ScannerTest, testIdentifySignedIntegerWithHighPowerOfTen) {
  this->testIdentifyLiteral<long long>(
      "+3e5", Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, 300000);
}

TEST_F(ScannerTest, testIdentifyDoublePlusZero) {
  this->testIdentifyLiteral<double>(
      "+0.0", Parser::symbol_kind_type::S_DOUBLE_LITERAL, +0.0);
}

TEST_F(ScannerTest, testIdentifyDoubleMinusZero) {
  this->testIdentifyLiteral<double>(
      "-0.0", Parser::symbol_kind_type::S_DOUBLE_LITERAL, -0.0);
}

TEST_F(ScannerTest, testIdentifyDoubleZero) {
  this->testIdentifyLiteral<double>(
      "0.0", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 0.0);
}

TEST_F(ScannerTest, testIdentifyDoublePositive) {
  this->testIdentifyLiteral<double>(
      "3.15", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 3.15);
}

TEST_F(ScannerTest, testIdentifyDoublePositiveWithSign) {
  this->testIdentifyLiteral<double>(
      "+23.15", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 23.15);
}

TEST_F(ScannerTest, testIdentifyDoubleNegative) {
  this->testIdentifyLiteral<double>(
      "-222.36", Parser::symbol_kind_type::S_DOUBLE_LITERAL, -222.36);
}

TEST_F(ScannerTest, testIdentifyDoubleWithE) {
  this->testIdentifyLiteral<double>(
      "15.0e0", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 15.0);
}

TEST_F(ScannerTest, testIdentifyPositiveDoubleWithE) {
  this->testIdentifyLiteral<double>(
      "+3.14e-2", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 0.0314);
}

TEST_F(ScannerTest, testIdentifyNegativeDoubleWithE) {
  this->testIdentifyLiteral<double>(
      "+123.0e10", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 123e10);
}

TEST_F(ScannerTest, testIdentifyFloatPlusZero) {
  this->testIdentifyLiteral<float>(
      "+0.0f", Parser::symbol_kind_type::S_FLOAT_LITERAL, +0.0f);
}

TEST_F(ScannerTest, testIdentifyFloatMinusZero) {
  this->testIdentifyLiteral<float>(
      "-0.0f", Parser::symbol_kind_type::S_FLOAT_LITERAL, -0.0f);
}

TEST_F(ScannerTest, testIdentifyFloatZero) {
  this->testIdentifyLiteral<float>(
      "0.0f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 0.0f);
}

TEST_F(ScannerTest, testIdentifyFloatPositive) {
  this->testIdentifyLiteral<float>(
      "3.15f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 3.15f);
}

TEST_F(ScannerTest, testIdentifyFloatPositiveWithSign) {
  this->testIdentifyLiteral<float>(
      "+23.15f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 23.15f);
}

TEST_F(ScannerTest, testIdentifyFloatNegative) {
  this->testIdentifyLiteral<float>(
      "-222.36f", Parser::symbol_kind_type::S_FLOAT_LITERAL, -222.36f);
}

TEST_F(ScannerTest, testIdentifyFloatWithE) {
  this->testIdentifyLiteral<float>(
      "15.0e0f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 15.0f);
}

TEST_F(ScannerTest, testIdentifyPositiveFloatWithE) {
  this->testIdentifyLiteral<float>(
      "+3.14e-2f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 0.0314f);
}

TEST_F(ScannerTest, testIdentifyNegativeFloatWithE) {
  this->testIdentifyLiteral<float>(
      "+123.0e10f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 123e10f);
}

} // namespace Gnocchi