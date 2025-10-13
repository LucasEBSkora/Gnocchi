#include "gtest/gtest.h"

#include "ENOperators.h"
#include "ENScope.h"
#include "UnaryExpr.h"
#include "VertexAccessExpr.h"
namespace EN {
using namespace std;

using TestParam =
    tuple<Operator, UnaryExpr::Direction, const char *, const char *>;

class UnaryExprToStringTest : public testing::Test,
                              public testing::WithParamInterface<TestParam> {
public:
  Scope scope;
  shared_ptr<Expr> a = make_shared<VertexAccessExpr>("a", scope);

  void testUnaryToString(Operator var, UnaryExpr::Direction dir,
                         const char *expected) {
    const unique_ptr<Expr> expr = make_unique<UnaryExpr>(var, a, dir);

    ASSERT_EQ(expected, expr->toString());
  }
};

TEST_P(UnaryExprToStringTest, testUnaryToString) {
  TestParam p = GetParam();
  this->testUnaryToString(std::get<0>(p), std::get<1>(p), std::get<2>(p));
}

const vector<TestParam> testTuples{
    {Operator::MINUS, UnaryExpr::Direction::LEFT, "-a",
     "testUnaryMinusToString"},
    {Operator::LOGIC_NOT, UnaryExpr::Direction::LEFT, "!a",
     "testLogicNotToString"},
    {Operator::BINARY_NOT, UnaryExpr::Direction::LEFT, "~a",
     "testBinaryNotToString"},
    {Operator::INC, UnaryExpr::Direction::LEFT, "++a", "testIncLeftToString"},
    {Operator::INC, UnaryExpr::Direction::RIGHT, "a++", "testIncRightToString"},
    {Operator::DEC, UnaryExpr::Direction::LEFT, "--a", "testDecLeftToString"},
    {Operator::DEC, UnaryExpr::Direction::RIGHT, "a--", "testDecRightToString"},
    {Operator::UNARY_LEFT_HOLON_OP, UnaryExpr::Direction::LEFT, "*>a",
     "testHolonOpLeftToString"},
    {Operator::UNARY_RIGHT_HOLON_OP, UnaryExpr::Direction::RIGHT, "a<*",
     "testHolonOpRightToString"},
};

INSTANTIATE_TEST_SUITE_P(UnaryToStringTest, UnaryExprToStringTest,
                         testing::ValuesIn(testTuples),
                         [](const testing::TestParamInfo<TestParam> &info) {
                           return std::get<3>(info.param);
                         });
} // namespace EN