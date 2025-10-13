#include "gtest/gtest.h"

#include "ENExprs.h"

namespace EN {
using namespace std;

using TestParam = tuple<EN::LiteralVariant, const char *, const char *>;

class LiteralToStringTest : public testing::Test,
                            public testing::WithParamInterface<TestParam> {
public:
  void testLiteralToString(LiteralVariant var, const char *expected) {
    const unique_ptr<Expr> expr = make_unique<LiteralExpr>(var);

    ASSERT_EQ(expected, expr->toString());
  }
};

TEST_P(LiteralToStringTest, testLiteralToString) {
  TestParam p = GetParam();
  this->testLiteralToString(std::get<0>(p), std::get<1>(p));
}

const vector<TestParam> testTuples{
    {10ll, "10", "testIntToString"},
    {23.f, "23f", "testFloatToString"},
    {0.12, "0.12", "testDoubleToString"},
    {'a', "a", "testCharToString"},
    {"bipbop", "\"bipbop\"", "testStringLiteral"},
    {true, "true", "testTrueToString"},
    {false, "false", "testFalseToString"},
};

INSTANTIATE_TEST_SUITE_P(testLiteralToString, LiteralToStringTest,
                         testing::ValuesIn(testTuples),
                         [](const testing::TestParamInfo<TestParam> &info) {
                           return std::get<2>(info.param);
                         });
} // namespace EN