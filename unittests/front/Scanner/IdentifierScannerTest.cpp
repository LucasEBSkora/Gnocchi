#include "scanner.h"
#include "gtest/gtest.h"

namespace Gnocchi {

class IdentifierScannerTest : public testing::Test {
public:
  Scanner *obj;
  LocationProvider provider{"mock.gno"};

  virtual void SetUp() override { obj = new Scanner(provider); }

  virtual void TearDown() override {
    provider.reset();
    delete obj;
  }

  void testIdentifyIdentifier(const char *text) {
    stringstream stream;
    stream << text;
    obj->switch_streams(&stream, nullptr);
    Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(Parser::symbol_kind_type::S_IDENTIFIER, token.kind());
    ASSERT_EQ(text, token.value.as<string>());
  }
};

#define IDENTIFIER_SCANNER_TEST(NAME, INPUT)                                                                           \
  TEST_F(IdentifierScannerTest, NAME) { this->testIdentifyIdentifier(INPUT); }

IDENTIFIER_SCANNER_TEST(testIdentifierOnlyText, "abaosafpasfas")
IDENTIFIER_SCANNER_TEST(testIdentifierStartUnderscore, "_padkadada")
IDENTIFIER_SCANNER_TEST(testIdentifierWithNumbers, "_12312412412")
IDENTIFIER_SCANNER_TEST(testIdentifierComplete, "_1jiasjfaafsokw243___")
} // namespace Gnocchi
