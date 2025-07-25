#include "ENGraphCommon.h"
#include "parser.hpp"
#include "scanner.h"
#include "gtest/gtest.h"

namespace Gnocchi {

using namespace std;
using VisibilityTokenParam =
    tuple<Parser::symbol_kind_type, EN::Visibility, const char *, const char *>;

class VisibilityScannerTest
    : public testing::Test,
      public testing::WithParamInterface<VisibilityTokenParam> {
public:
  Scanner *obj;
  LocationProvider provider{"mock.gno"};

  virtual void SetUp() override { obj = new Scanner(provider); }

  virtual void TearDown() override {
    provider.reset();
    delete obj;
  }

  void testIdentifyVisibility(Parser::symbol_kind_type type,
                              EN::Visibility visibility, const char *text) {
    stringstream stream;
    stream << text;
    obj->switch_streams(&stream, nullptr);
    Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(type, token.kind());
    ASSERT_EQ(visibility, token.value.as<EN::Visibility>());
  }
};

TEST_P(VisibilityScannerTest, testIdentifyVisibility) {
  VisibilityTokenParam p = GetParam();
  this->testIdentifyVisibility(get<0>(p), get<1>(p), get<2>(p));
}

const vector<VisibilityTokenParam> visibilityTokenParams{
    {Parser::symbol_kind_type::S_PUBLIC, EN::Visibility::PUBLIC, "public",
     "testIdentifyPublic"},
    {Parser::symbol_kind_type::S_PRIVATE, EN::Visibility::PRIVATE, "private",
     "testIdentifyPrivate"},
    {Parser::symbol_kind_type::S_DECLARE, EN::Visibility::DEFAULT, "declare",
     "testIdentifyDeclare"},
};

INSTANTIATE_TEST_SUITE_P(
    testIdentifyVisibilityTokens, VisibilityScannerTest,
    testing::ValuesIn(visibilityTokenParams),
    [](const testing::TestParamInfo<VisibilityTokenParam> &info) {
      return get<3>(info.param);
    });
} // namespace Gnocchi