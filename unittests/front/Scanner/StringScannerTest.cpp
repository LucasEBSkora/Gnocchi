#include "gtest/gtest.h"
#include "scanner.h"
#include <iostream>
#include <utility>

namespace Gnocchi
{

  class StringScannerTest : public testing::Test  
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

    void testIdentifyStringLiteral(std::string s)
    {
      std::stringstream stream;
      stream << '"' << s << '"';
      obj->switch_streams(&stream, nullptr);
      Parser::symbol_type token = obj->get_next_token();
      ASSERT_EQ(Parser::symbol_kind_type::S_STRING_LITERAL, token.kind());
      ASSERT_EQ(s, token.value.as<std::string>());
    }
  };



  TEST_F(StringScannerTest, testIdentifyEmptyString)
  {
    this->testIdentifyStringLiteral("");
  }
}