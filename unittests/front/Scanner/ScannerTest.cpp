#include "scanner.h"
#include "gtest/gtest.h"
#include <iostream>

namespace Gnocchi {

class ScannerTest : public testing::Test {
public:
  Scanner *obj;
  LocationProvider provider{"mock.gno"};

  virtual void SetUp() override { obj = new Scanner(provider); }

  virtual void TearDown() override {
    provider.reset();
    delete obj;
  }

  void testCreateScanner() { ASSERT_NE(nullptr, obj); }

  void testSwitchStream() {
    stringstream stream;
    stream << "";
    obj->switch_streams(&stream, nullptr);
    ASSERT_EQ(0, obj->get_next_token().kind());

    stream << "+ *";
    ASSERT_EQ(Parser::symbol_kind_type::S_PLUS, obj->get_next_token().kind());

    stringstream stream2;
    stream2 << "";
    obj->switch_streams(&stream2, nullptr);
    ASSERT_EQ(0, obj->get_next_token().kind());
  }
};

TEST_F(ScannerTest, testCreateScanner) { this->testCreateScanner(); }

TEST_F(ScannerTest, testSwitchStream) { this->testSwitchStream(); }

} // namespace Gnocchi