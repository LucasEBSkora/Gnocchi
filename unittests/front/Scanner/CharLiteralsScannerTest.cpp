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
    {" ", ' ', "testIdentifyWhitespace"},
    {"\"", '"', "testIdentifyExclamation"},
    {"#", '#', "testIdentifyPoundSign"},
    {"$", '$', "testIdentifyDollarSign"},
    {"%", '%', "testIdentifyPercentSign"},
    {"&", '&', "testIdentifyAmpersand"},
    {"(", '(', "testIdentifyLeftParentheses"},
    {")", ')', "testIdentifyRightParentheses"},
    {"*", '*', "testIdentifyAsterisc"},
    {"+", '+', "testIdentifyPlusSign"},
    {",", ',', "testIdentifyComma"},
    {"-", '-', "testIdentifyMinus"},
    {".", '.', "testIdentifyDot"},
    {"/", '/', "testIdentifySlash"},
    {"\"", '"', "testIdentifyQuotation"},
    {":", ':', "testIdentifyColon"},
    {";", ';', "testIdentifySemicolon"},
    {"", '', "testIdentify"},
    // {"0", '0', "testIdentifyExclamation"},
    // {"1", '1', "testIdentifyExclamation"},
    // {"2", '2', "testIdentifyExclamation"},
    // {"3", '3', "testIdentifyExclamation"},
    // {"4", '4', "testIdentifyExclamation"},
    // {"5", '5', "testIdentifyExclamation"},
    // {"6", '6', "testIdentifyExclamation"},
    // {"7", '7', "testIdentifyExclamation"},
    // {"8", '8', "testIdentifyExclamation"},
    // {"9", '9', "testIdentifyExclamation"},

    // {";", ';', "testIdentifyExclamation"},
    // {";", ';', "testIdentifyExclamation"},
    // {";", ';', "testIdentifyExclamation"},
    // {";", ';', "testIdentifyExclamation"},
    // {";", ';', "testIdentifyExclamation"},
    // {";", ';', "testIdentifyExclamation"},
    // {";", ';', "testIdentifyExclamation"},
    // {";", ';', "testIdentifyExclamation"},
    // {";", ';', "testIdentifyExclamation"},
 };

  INSTANTIATE_TEST_SUITE_P(testIdentifyCharConstants, CharLiteralsScannerTest,
                           testing::ValuesIn(simpleTokenPairs), [](const testing::TestParamInfo<charLiteralTestParam> &info)
                           { return std::get<2>(info.param); });
}