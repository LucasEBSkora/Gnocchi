#include "ENGraphCommon.h"
#include "ENVertex.h"
#include "parser.hpp"
#include "scanner.h"
#include "gtest/gtest.h"

namespace Gnocchi {

using namespace std;
using OperationTokenParam = tuple<Parser::symbol_kind_type, EN::AllowedOperations, const char *, const char *>;

class OperationScannerTest : public testing::Test, public testing::WithParamInterface<OperationTokenParam> {
public:
  Scanner *obj;
  LocationProvider provider{"mock.gno"};

  virtual void SetUp() override { obj = new Scanner(provider); }

  virtual void TearDown() override {
    provider.reset();
    delete obj;
  }

  void testIdentifyOperation(Parser::symbol_kind_type type, EN::AllowedOperations operations, const char *text) {
    stringstream stream;
    stream << text;
    obj->switch_streams(&stream, nullptr);
    Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(type, token.kind());
    ASSERT_EQ(operations, token.value.as<EN::AllowedOperations>());
  }
};

TEST_P(OperationScannerTest, testIdentifyOperation) {
  OperationTokenParam p = GetParam();
  this->testIdentifyOperation(get<0>(p), get<1>(p), get<2>(p));
}

const vector<OperationTokenParam> visibilityTokenParams{
    {Parser::symbol_kind_type::S_READ, EN::AllowedOperations::READ, "read", "testIdentifyRead"},
    {Parser::symbol_kind_type::S_NOTIFY, EN::AllowedOperations::NOTIFY, "notify", "testIdentifyNotify"},
    {Parser::symbol_kind_type::S_LISTEN, EN::AllowedOperations::LISTEN, "listen", "testIdentifyListen"},
};

INSTANTIATE_TEST_SUITE_P(testIdentifyOperationTokens, OperationScannerTest, testing::ValuesIn(visibilityTokenParams),
                         [](const testing::TestParamInfo<OperationTokenParam> &info) { return get<3>(info.param); });
} // namespace Gnocchi