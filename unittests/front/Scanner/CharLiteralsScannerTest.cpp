#include "gtest/gtest.h"
#include "scanner.h"
#include <iostream>
#include <utility>

using charLiteralTestParam = std::tuple<const char*, char, const char *>;

namespace Gnocchi
{

  class CharLiteralsScannerTest : public testing::Test, public testing::WithParamInterface<charLiteralTestParam>
  {
  public:
    Scanner *obj{nullptr};
    LocationProvider provider{"mock.gno"};

    void SetUp() override
    {
      obj = new Scanner(provider);
    }

    void TearDown() override
    {
      provider.reset();
      delete obj;
    }

    void testIdentifyCharLiteral(const char* text, char expected)
    {
      std::stringstream stream;
      stream << '\'' << text << '\'';
      obj->switch_streams(&stream, nullptr);
      Parser::symbol_type token = obj->get_next_token();
      ASSERT_EQ(Parser::symbol_kind_type::S_CHAR_LITERAL, token.kind());
      ASSERT_EQ(expected, token.value.as<char>());
    }
  };

  TEST_P(CharLiteralsScannerTest, testIdentifyCharLiteral)
  {
    charLiteralTestParam p = GetParam();
    this->testIdentifyCharLiteral(std::get<0>(p), std::get<1>(p));
  }

  const std::vector<charLiteralTestParam> simpleTokenPairs{
    {"\\0", '\0', "testIdentifyEOF"},
    {"\\t", '\t', "testIdentifyTab"},
    {"\\n", '\n', "testIdentifyNewLine"},
    {"\\r", '\r', "testIdentifyCarriageReturn"},
    {" ", ' ', "testIdentifyWhitespace"},
 };

  INSTANTIATE_TEST_SUITE_P(testIdentifyCharConstants, CharLiteralsScannerTest,
                           testing::ValuesIn(simpleTokenPairs), [](const testing::TestParamInfo<charLiteralTestParam> &info)
                           { return std::get<2>(info.param); });
}