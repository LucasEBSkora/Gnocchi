#include "ENOperators.h"
#include "scanner.h"
#include "gtest/gtest.h"

namespace Gnocchi {

using namespace std;
using OperatorTokenParam = tuple<Gnocchi::Parser::symbol_kind_type,
                                 EN::Operator, const char *, const char *>;

class OperatorScannerTest
    : public testing::Test,
      public testing::WithParamInterface<OperatorTokenParam> {
public:
  Scanner *obj;
  LocationProvider provider{"mock.gno"};

  virtual void SetUp() override { obj = new Scanner(provider); }

  virtual void TearDown() override {
    provider.reset();
    delete obj;
  }

  void testIdentifyOperator(Parser::symbol_kind_type type, EN::Operator op,
                            const char *text) {
    stringstream stream;
    stream << text;
    obj->switch_streams(&stream, nullptr);
    Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(type, token.kind());
    ASSERT_EQ(op, token.value.as<EN::Operator>());
  }
};

TEST_P(OperatorScannerTest, testIdentifyOperator) {
  OperatorTokenParam p = GetParam();
  this->testIdentifyOperator(get<0>(p), get<1>(p), get<2>(p));
}

const vector<OperatorTokenParam> operatorTokenParams{
    {Parser::symbol_kind_type::S_HOLON_BINARY_OP, EN::Operator::BINARY_HOLON_OP,
     "<*>", "testIdentifyBinaryHolonOp"},
    {Parser::symbol_kind_type::S_HOLON_UNARY_LEFT_OP,
     EN::Operator::UNARY_LEFT_HOLON_OP, "*>", "testIdentifyUnaryLeftHolonOp"},
    {Parser::symbol_kind_type::S_HOLON_UNARY_RIGHT_OP,
     EN::Operator::UNARY_RIGHT_HOLON_OP, "<*", "testIdentifyUnaryRightHolonOp"},
    {Parser::symbol_kind_type::S_ASSIGN, EN::Operator::ASSIGN,
     ":=", "testIdentifyAssign"},
    {Parser::symbol_kind_type::S_ASSIGN_PLUS, EN::Operator::ASSIGN_PLUS,
     "+=", "testIdentifyAssignPlus"},
    {Parser::symbol_kind_type::S_ASSIGN_MINUS, EN::Operator::ASSIGN_MINUS,
     "-=", "testIdentifyAssignMinus"},
    {Parser::symbol_kind_type::S_ASSIGN_MUL, EN::Operator::ASSIGN_MUL,
     "*=", "testIdentifyAssignMul"},
    {Parser::symbol_kind_type::S_ASSIGN_DIV, EN::Operator::ASSIGN_DIV,
     "/=", "testIdentifyAssignDiv"},
    {Parser::symbol_kind_type::S_ASSIGN_MOD, EN::Operator::ASSIGN_MOD,
     "%=", "testIdentifyAssignMod"},
    {Parser::symbol_kind_type::S_ASSIGN_AND, EN::Operator::ASSIGN_AND,
     "&=", "testIdentifyAssignAnd"},
    {Parser::symbol_kind_type::S_ASSIGN_OR, EN::Operator::ASSIGN_OR,
     "|=", "testIdentifyAssignOr"},
    {Parser::symbol_kind_type::S_ASSIGN_XOR, EN::Operator::ASSIGN_XOR,
     "^=", "testIdentifyAssignXor"},
    {Parser::symbol_kind_type::S_LOGIC_OR, EN::Operator::LOGIC_OR, "||",
     "testIdentifyLogicOr"},
    {Parser::symbol_kind_type::S_LOGIC_XOR, EN::Operator::LOGIC_XOR, "^^",
     "testIdentifyLogicXor"},
    {Parser::symbol_kind_type::S_LOGIC_AND, EN::Operator::LOGIC_AND, "&&",
     "testIdentifyLogicAnd"},
    {Parser::symbol_kind_type::S_BINARY_OR, EN::Operator::BINARY_OR, "|",
     "testIdentifyBinaryOr"},
    {Parser::symbol_kind_type::S_BINARY_XOR, EN::Operator::BINARY_XOR, "^",
     "testIdentifyBinaryXor"},
    {Parser::symbol_kind_type::S_BINARY_AND, EN::Operator::BINARY_AND, "&",
     "testIdentifyBinaryAnd"},
    {Parser::symbol_kind_type::S_EQ, EN::Operator::EQ, "==", "testIdentifyEq"},
    {Parser::symbol_kind_type::S_NE, EN::Operator::NE, "!=", "testIdentifyNe"},
    {Parser::symbol_kind_type::S_LT, EN::Operator::LT, "<", "testIdentifyLt"},
    {Parser::symbol_kind_type::S_LE, EN::Operator::LE, "<=", "testIdentifyLe"},
    {Parser::symbol_kind_type::S_GT, EN::Operator::GT, ">", "testIdentifyGt"},
    {Parser::symbol_kind_type::S_GE, EN::Operator::GE, ">=", "testIdentifyGe"},
    {Parser::symbol_kind_type::S_SHIFT_LEFT, EN::Operator::SHIFT_LEFT, "<<",
     "testIdentifyShiftLeft"},
    {Parser::symbol_kind_type::S_SHIFT_RIGHT, EN::Operator::SHIFT_RIGHT, ">>",
     "testIdentifyShiftRight"},
    {Parser::symbol_kind_type::S_PLUS, EN::Operator::PLUS, "+",
     "testIdentifyPlus"},
    {Parser::symbol_kind_type::S_MINUS, EN::Operator::MINUS, "-",
     "testIdentifyMinus"},
    {Parser::symbol_kind_type::S_MUL, EN::Operator::MUL, "*",
     "testIdentifyMul"},
    {Parser::symbol_kind_type::S_DIV, EN::Operator::DIV, "/",
     "testIdentifyDiv"},
    {Parser::symbol_kind_type::S_MOD, EN::Operator::MOD, "%",
     "testIdentifyMod"},
    {Parser::symbol_kind_type::S_LOGIC_NOT, EN::Operator::LOGIC_NOT, "!",
     "testIdentifyLogicNot"},
    {Parser::symbol_kind_type::S_BINARY_NOT, EN::Operator::BINARY_NOT, "~",
     "testIdentifyBinaryNot"},
    {Parser::symbol_kind_type::S_INC, EN::Operator::INC, "++",
     "testIdentifyInc"},
    {Parser::symbol_kind_type::S_DEC, EN::Operator::DEC, "--",
     "testIdentifyDec"},
};

INSTANTIATE_TEST_SUITE_P(
    testIdentifyPunctiationOperatorsKeywords, OperatorScannerTest,
    testing::ValuesIn(operatorTokenParams),
    [](const testing::TestParamInfo<OperatorTokenParam> &info) {
      return get<3>(info.param);
    });
} // namespace Gnocchi