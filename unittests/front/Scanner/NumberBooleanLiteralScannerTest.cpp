#include "scanner.h"
#include "gtest/gtest.h"

namespace Gnocchi {
using namespace std;

class LiteralScannerTest : public testing::Test {
public:
  Scanner *obj;
  LocationProvider provider{"mock.gno"};

  virtual void SetUp() override { obj = new Scanner(provider); }

  virtual void TearDown() override {
    provider.reset();
    delete obj;
  }

  template <typename T> void testIdentifyLiteral(const char *text, Parser::symbol_kind_type type, T value) {
    stringstream stream;
    stream << text;
    obj->switch_streams(&stream, nullptr);
    Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(type, token.kind());
    ASSERT_EQ(value, token.value.as<T>());
  }
};

#define LITERAL_SCANNER_TEST(NAME, TYPE, INPUT, SYMBOL, VALUE)                                                         \
  TEST_F(LiteralScannerTest, NAME) { this->testIdentifyLiteral<TYPE>(INPUT, SYMBOL, VALUE); }

LITERAL_SCANNER_TEST(testIdentifyTrue, bool, "true", Parser::symbol_kind_type::S_BOOL_LITERAL, true)
LITERAL_SCANNER_TEST(testIdentifyFalse, bool, "false", Parser::symbol_kind_type::S_BOOL_LITERAL, false)
LITERAL_SCANNER_TEST(testIdentifyUnsignedIntegerZero, unsigned long long, "0",
                     Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 0)
LITERAL_SCANNER_TEST(testIdentifyUnsignedIntegerArbitrary, unsigned long long, "1234567890",
                     Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 1234567890)
LITERAL_SCANNER_TEST(testIdentifyUnsignedIntegerMax, unsigned long long, "18446744073709551615",
                     Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 18446744073709551615ULL)
LITERAL_SCANNER_TEST(testIdentifyUnsignedIntegerWithE, unsigned long long, "3e0",
                     Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 3)
LITERAL_SCANNER_TEST(testIdentifyUnsignedIntegerWithHighPowerOfTen, unsigned long long, "3e9",
                     Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 3000000000)
LITERAL_SCANNER_TEST(testIdentifyUnsignedIntegerBinary, unsigned long long, "0b101",
                     Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 5)
LITERAL_SCANNER_TEST(testIdentifyUnsignedIntegerOctal, unsigned long long, "0o1234567",
                     Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 342391)
LITERAL_SCANNER_TEST(testIdentifyUnsignedIntegerHex, unsigned long long, "0x123456789ABCDEF0",
                     Parser::symbol_kind_type::S_UNSIGNED_INTEGER_LITERAL, 1311768467463790320ull)
LITERAL_SCANNER_TEST(testIdentifySignedIntegerPlusZero, long long, "+0",
                     Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, 0)
LITERAL_SCANNER_TEST(testIdentifySignedIntegerMinusZero, long long, "-0",
                     Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, 0)
LITERAL_SCANNER_TEST(testIdentifySignedIntegerArbitraryPositive, long long, "+1234567890",
                     Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, 1234567890)
LITERAL_SCANNER_TEST(testIdentifySignedIntegerArbitraryNegative, long long, "-9876543210",
                     Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, -9876543210)
LITERAL_SCANNER_TEST(testIdentifySignedIntegerMin, long long, "-9223372036854775808",
                     Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, -9223372036854775807LL - 1)
LITERAL_SCANNER_TEST(testIdentifySignedIntegerMax, long long, "+9223372036854775807",
                     Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, 9223372036854775807LL)
LITERAL_SCANNER_TEST(testIdentifySignedIntegerWithE, long long, "-15e0",
                     Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, -15)
LITERAL_SCANNER_TEST(testIdentifySignedIntegerWithHighPowerOfTen, long long, "+3e5",
                     Parser::symbol_kind_type::S_SIGNED_INTEGER_LITERAL, 300000)
LITERAL_SCANNER_TEST(testIdentifyDoublePlusZero, double, "+0.0", Parser::symbol_kind_type::S_DOUBLE_LITERAL, +0.0)
LITERAL_SCANNER_TEST(testIdentifyDoubleMinusZero, double, "-0.0", Parser::symbol_kind_type::S_DOUBLE_LITERAL, -0.0)
LITERAL_SCANNER_TEST(testIdentifyDoubleZero, double, "0.0", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 0.0)
LITERAL_SCANNER_TEST(testIdentifyDoublePositive, double, "3.15", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 3.15)
LITERAL_SCANNER_TEST(testIdentifyDoublePositiveWithSign, double, "+23.15", Parser::symbol_kind_type::S_DOUBLE_LITERAL,
                     23.15)
LITERAL_SCANNER_TEST(testIdentifyDoubleNegative, double, "-222.36", Parser::symbol_kind_type::S_DOUBLE_LITERAL, -222.36)
LITERAL_SCANNER_TEST(testIdentifyDoubleWithE, double, "15.0e0", Parser::symbol_kind_type::S_DOUBLE_LITERAL, 15.0)
LITERAL_SCANNER_TEST(testIdentifyPositiveDoubleWithE, double, "+3.14e-2", Parser::symbol_kind_type::S_DOUBLE_LITERAL,
                     0.0314)
LITERAL_SCANNER_TEST(testIdentifyNegativeDoubleWithE, double, "+123.0e10", Parser::symbol_kind_type::S_DOUBLE_LITERAL,
                     123e10)
LITERAL_SCANNER_TEST(testIdentifyFloatPlusZero, float, "+0.0f", Parser::symbol_kind_type::S_FLOAT_LITERAL, +0.0f)
LITERAL_SCANNER_TEST(testIdentifyFloatMinusZero, float, "-0.0f", Parser::symbol_kind_type::S_FLOAT_LITERAL, -0.0f)
LITERAL_SCANNER_TEST(testIdentifyFloatZero, float, "0.0f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 0.0f)
LITERAL_SCANNER_TEST(testIdentifyFloatPositive, float, "3.15f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 3.15f)
LITERAL_SCANNER_TEST(testIdentifyFloatPositiveWithSign, float, "+23.15f", Parser::symbol_kind_type::S_FLOAT_LITERAL,
                     23.15f)
LITERAL_SCANNER_TEST(testIdentifyFloatNegative, float, "-222.36f", Parser::symbol_kind_type::S_FLOAT_LITERAL, -222.36f)
LITERAL_SCANNER_TEST(testIdentifyFloatWithE, float, "15.0e0f", Parser::symbol_kind_type::S_FLOAT_LITERAL, 15.0f)
LITERAL_SCANNER_TEST(testIdentifyPositiveFloatWithE, float, "+3.14e-2f", Parser::symbol_kind_type::S_FLOAT_LITERAL,
                     0.0314f)
LITERAL_SCANNER_TEST(testIdentifyNegativeFloatWithE, float, "+123.0e10f", Parser::symbol_kind_type::S_FLOAT_LITERAL,
                     123e10f)
} // namespace Gnocchi