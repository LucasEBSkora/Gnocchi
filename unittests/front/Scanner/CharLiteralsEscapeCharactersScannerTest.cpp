#include "scanner.h"
#include "gtest/gtest.h"
#include <iostream>
#include <utility>

namespace Gnocchi {
using namespace std;

using charLiteralTestParam = tuple<const char *, char, const char *>;

class charLiteralsEscapeCharacterScannerTest
    : public testing::Test,
      public testing::WithParamInterface<charLiteralTestParam> {
public:
  Scanner *obj{nullptr};
  LocationProvider provider{"mock.gno"};

  void SetUp() override { obj = new Scanner(provider); }

  void TearDown() override {
    provider.reset();
    delete obj;
  }

  void testIdentifyCharLiteral(const char *text, char expected) {
    stringstream stream;
    stream << '\'' << text << '\'';
    obj->switch_streams(&stream, nullptr);
    Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(Parser::symbol_kind_type::S_CHAR_LITERAL, token.kind());
    ASSERT_EQ(expected, token.value.as<char>());
  }
};

TEST_P(charLiteralsEscapeCharacterScannerTest, testIdentifyCharLiteral) {
  charLiteralTestParam p = GetParam();
  this->testIdentifyCharLiteral(get<0>(p), get<1>(p));
}

const vector<charLiteralTestParam> simpleTokenPairs{
    {"\\'", '\'', "testIdentifyApostrophe"},
    {"\\\"", '\"', "testIdentifyQuotationEscape"},
    {"\\\\", '\\', "testIdentifyBackslash"},
    {"\\a", '\a', "testIdentifyAlert"},
    {"\\b", '\b', "testIdentifyBackspace"},
    {"\\f", '\f', "testIdentifyPageBreak"},
    {"\\n", '\n', "testIdentifyNewLine"},
    {"\\r", '\r', "testIdentifyCarriageReturn"},
    {"\\t", '\t', "testIdentifyTab"},
    {"\\v", '\v', "testIdentifyVerticalTab"},
    {"\\0", '\0', "testIdentifyEOF"},
};

INSTANTIATE_TEST_SUITE_P(
    testIdentifyCharConstants, charLiteralsEscapeCharacterScannerTest,
    testing::ValuesIn(simpleTokenPairs),
    [](const testing::TestParamInfo<charLiteralTestParam> &info) {
      return get<2>(info.param);
    });

} // namespace Gnocchi