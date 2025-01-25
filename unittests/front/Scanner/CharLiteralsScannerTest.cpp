#include "gtest/gtest.h"
#include "scanner.h"
#include <iostream>
#include <utility>

namespace Gnocchi
{
  using namespace std;

  class CharLiteralsScannerTest : public testing::Test, public testing::WithParamInterface<char>
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

    void testIdentifyCharLiteral(char c)
    {
      stringstream stream;
      stream << '\'' << c << '\'';
      obj->switch_streams(&stream, nullptr);
      Parser::symbol_type token = obj->get_next_token();
      ASSERT_EQ(Parser::symbol_kind_type::S_CHAR_LITERAL, token.kind());
      ASSERT_EQ(c, token.value.as<char>());
    }
  };

  TEST_P(CharLiteralsScannerTest, testIdentifyCharLiteral)
  {
    char c = GetParam();
    this->testIdentifyCharLiteral(c);
  }

  INSTANTIATE_TEST_SUITE_P(testIdentifyCharConstants, CharLiteralsScannerTest, testing::Range('!', '~'));

}