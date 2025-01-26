#include "gtest/gtest.h"

#include "ENExprs.h"

namespace EN
{
    using namespace std;

    using TestParam = tuple<Operator, const char *, const char *>;

    class BinaryExprToStringTest : public testing::Test, public testing::WithParamInterface<TestParam>
    {
    public:
        shared_ptr<Expr> a = make_shared<VertexAccessExpr>("a");
        shared_ptr<Expr> b = make_shared<VertexAccessExpr>("b");

        void testBinaryToString(Operator var, const char *expected)
        {
            const unique_ptr<Expr> expr = make_unique<BinaryExpr>(a, var, b);

            ASSERT_EQ(expected, expr->toString());
        }
    };

    TEST_P(BinaryExprToStringTest, testBinaryToString)
    {
        TestParam p = GetParam();
        this->testBinaryToString(std::get<0>(p), std::get<1>(p));
    }

    const vector<TestParam> testTuples{
        {Operator::HOLON_OP, "a <> b", "testHolonOpToString"},
        {Operator::ASSIGN, "a := b", "testAssignToString"},
        {Operator::ASSIGN_PLUS, "a += b", "testAssignPlusToString"},
        {Operator::ASSIGN_MINUS, "a -= b", "testAssignMinusToString"},
        {Operator::ASSIGN_MUL, "a *= b", "testAssignMulToString"},
        {Operator::ASSIGN_DIV, "a /= b", "testAssignDivToString"},
        {Operator::ASSIGN_MOD, "a %= b", "testAssignModToString"},
        {Operator::ASSIGN_AND, "a &= b", "testAssignAndToString"},
        {Operator::ASSIGN_OR, "a |= b", "testAssignOrToString"},
        {Operator::ASSIGN_XOR, "a ^= b", "testAssignXorToString"},
        {Operator::LOGIC_OR, "a || b", "testLogicOrToString"},
        {Operator::LOGIC_XOR, "a ^^ b", "testLogicXorToString"},
        {Operator::LOGIC_AND, "a && b", "testLogicAndToString"},
        {Operator::BINARY_OR, "a | b", "testBinaryOrToString"},
        {Operator::BINARY_XOR, "a ^ b", "testBinaryXorToString"},
        {Operator::BINARY_AND, "a & b", "testBinaryAndToString"},
        {Operator::EQ, "a == b", "testEqualityToString"},
        {Operator::NE, "a != b", "testInequalityToString"},
        {Operator::LT, "a < b", "testLessThanToString"},
        {Operator::LE, "a <= b", "testLessEqualToString"},
        {Operator::GT, "a > b", "testGreaterToString"},
        {Operator::GE, "a >= b", "testGreaterEqualToString"},
        {Operator::SHIFT_LEFT, "a << b", "testShiftLeftToString"},
        {Operator::SHIFT_RIGHT, "a >> b", "testShiftRightToString"},
        {Operator::PLUS, "a + b", "testPlusToString"},
        {Operator::MINUS, "a - b", "testMinusToString"},
        {Operator::MUL, "a * b", "testMulToString"},
        {Operator::DIV, "a / b", "testDivToString"},
        {Operator::MOD, "a % b", "testModToString"},
    };

    INSTANTIATE_TEST_SUITE_P(BinaryToStringTest, BinaryExprToStringTest,
                             testing::ValuesIn(testTuples), [](const testing::TestParamInfo<TestParam> &info)
                             { return std::get<2>(info.param); });
}