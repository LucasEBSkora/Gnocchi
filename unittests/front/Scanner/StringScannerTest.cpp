#include "scanner.h"
#include "gtest/gtest.h"
#include <iostream>
#include <utility>

namespace Gnocchi {
using namespace std;

class StringScannerTest : public testing::Test {
public:
  Scanner *obj{nullptr};
  LocationProvider provider{"mock.gno"};

  void SetUp() override { obj = new Scanner(provider); }

  void TearDown() override {
    provider.reset();
    delete obj;
  }

  void testIdentifyStringLiteral(const string &s, string expected = "") const {
    if (expected.empty())
      expected = s;
    stringstream stream;
    stream << '"' << s << '"';
    obj->switch_streams(&stream, nullptr);
    Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(Parser::symbol_kind_type::S_STRING_LITERAL, token.kind());
    ASSERT_EQ(expected, token.value.as<string>());
  }
};

TEST_F(StringScannerTest, testIdentifyEmptyString) {
  this->testIdentifyStringLiteral("");
}

TEST_F(StringScannerTest, testIdentifyStringAllPrintableCharacters) {
  string allChars;
  for (char c = '!'; c <= '~'; c++) {
    if (c != '\\')
      allChars += c;
  }
  this->testIdentifyStringLiteral(allChars);
}

TEST_F(StringScannerTest, testIdentifyWhitespaceAndEscapeSequences) {
  string str = R"( \'\"\\\a\b\f\n\r\t\v\0)";
  string expected = " \'\"\\\a\b\f\n\r\t\vx";
  expected[expected.length() - 1] = '\0';
  this->testIdentifyStringLiteral(str, expected);
}
} // namespace Gnocchi