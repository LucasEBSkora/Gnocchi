#include "gtest/gtest.h"
#include "scanner.h"
#include <iostream>

namespace Gnocchi {

  class IdentifierScannerTest : public testing::Test {
  public:
    Scanner *obj;
    LocationProvider provider{"mock.gno"};

    virtual void SetUp() override {
      obj = new Scanner(provider);
    }

    virtual void TearDown() override {
      provider.reset();
      delete obj;
    }

    void testIdentifyIdentifier(const char *text) {
      std::stringstream stream;
      stream << text;
      obj->switch_streams(&stream, nullptr);
      Parser::symbol_type token = obj->get_next_token();
      ASSERT_EQ(Parser::symbol_kind_type::S_IDENTIFIER, token.kind());
      ASSERT_EQ(text, token.value.as<std::string>());
    }
  };

  TEST_F(IdentifierScannerTest, testIdentifierOnlyText) {
    this->testIdentifyIdentifier("abaosafpasfas");
  }

  TEST_F(IdentifierScannerTest, testIdentifierStartUnderscore) {
    this->testIdentifyIdentifier("_padkadada");
  }

  TEST_F(IdentifierScannerTest, testIdentifierWithNumbers) {
    this->testIdentifyIdentifier("_12312412412");
  }

  TEST_F(IdentifierScannerTest, testIdentifierComplete) {
    this->testIdentifyIdentifier("_1jiasjfaafsokw243___");
  }
}
