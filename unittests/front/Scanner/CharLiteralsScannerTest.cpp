#include "gtest/gtest.h"
#include "scanner.h"
#include <iostream>
#include <utility>

using charLiteralTestParam = std::tuple<const char*, char, const char *>;

namespace Gnocchi
{

  class CharLiteralsScannerTest : public testing::Test, public testing::WithParamInterface<charLiteralTestParam>
  {
  public:
    Scanner *obj;
    LocationProvider provider{"mock.gno"};

    virtual void SetUp() override
    {
      obj = new Scanner(provider);
    }

    virtual void TearDown() override
    {
      provider.reset();
      delete obj;
    }

    void testIdentifyCharLiteral(const char* token, char expected)
    {
      std::stringstream stream;
      stream << '\'' << token << '\'';
      obj->switch_streams(&stream, nullptr);
      ASSERT_EQ(type, obj->get_next_token().kind());
    }
  };

  TEST_P(CharLiteralsScannerTest, testIdentifySimpleTokenType)
  {
    charLiteralTestParam p = GetParam();
    this->testIdentifySimpleTokenType(std::get<0>(p), std::get<1>(p));
  }

  const std::vector<charLiteralTestParam> simpleTokenPairs{
      {Parser::symbol_kind_type::S_EDGE, "edge", "testIdentifyEdge"},
      {Parser::symbol_kind_type::S_ATOM, "atom", "testIdentifyAtom"},
      {Parser::symbol_kind_type::S_THIS, "this", "testIdentifyThis"},
      {Parser::symbol_kind_type::S_HEAD, "head", "testIdentifyHead"},
      {Parser::symbol_kind_type::S_PUBLIC, "public", "testIdentifyPublic"},
      {Parser::symbol_kind_type::S_PRIVATE, "private", "testIdentifyPrivate"},
      {Parser::symbol_kind_type::S_IS, "is", "testIdentifyIs"},
      {Parser::symbol_kind_type::S_VERTEX, "vertex", "testIdentifyVertex"},
      {Parser::symbol_kind_type::S_BOUND, "bound", "testIdentifyBound"},
      {Parser::symbol_kind_type::S_DEFAULT, "default", "testIdentifyDefault"},
      {Parser::symbol_kind_type::S_WHEN, "when", "testIdentifyWhen"},
      {Parser::symbol_kind_type::S_WITH, "with", "testIdentifyWith"},
      {Parser::symbol_kind_type::S_ENABLES, "enables", "testIdentifyEnables"},
      {Parser::symbol_kind_type::S_DISABLES, "disables", "testIdentifyDisables"},
      {Parser::symbol_kind_type::S_NOTIFY, "notify", "testIdentifyNotify"},
      {Parser::symbol_kind_type::S_READ, "read", "testIdentifyRead"},
      {Parser::symbol_kind_type::S_LISTEN, "listen", "testIdentifyListen"},
      {Parser::symbol_kind_type::S_INITIALISE, "initialise", "testIdentifyInitialise"},
      {Parser::symbol_kind_type::S_HOLON, "holon", "testIdentifyHolon"},
      {Parser::symbol_kind_type::S_INT, "int", "testIdentifyInt"},
      {Parser::symbol_kind_type::S_INT8, "int8", "testIdentifyInt8"},
      {Parser::symbol_kind_type::S_INT16, "int16", "testIdentifyInt16"},
      {Parser::symbol_kind_type::S_INT24, "int24", "testIdentifyInt24"},
      {Parser::symbol_kind_type::S_INT32, "int32", "testIdentifyInt32"},
      {Parser::symbol_kind_type::S_UINT, "uint", "testIdentifyUint"},
      {Parser::symbol_kind_type::S_UINT8, "uint8", "testIdentifyUint8"},
      {Parser::symbol_kind_type::S_UINT16, "uint16", "testIdentifyUint16"},
      {Parser::symbol_kind_type::S_UINT24, "uint24", "testIdentifyUint24"},
      {Parser::symbol_kind_type::S_UINT32, "uint32", "testIdentifyUint32"},
      {Parser::symbol_kind_type::S_FLOAT, "float", "testIdentifyFloat"},
      {Parser::symbol_kind_type::S_DOUBLE, "double", "testIdentifyDouble"},
      {Parser::symbol_kind_type::S_NUMBER, "number", "testIdentifyNumber"},
      {Parser::symbol_kind_type::S_BOOL, "bool", "testIdentifyBool"},
      {Parser::symbol_kind_type::S_CHAR, "char", "testIdentifyChar"},
      {Parser::symbol_kind_type::S_REF, "ref", "testIdentifyRef"},
      {Parser::symbol_kind_type::S_TO, "to", "testIdentifyTo"},
      {Parser::symbol_kind_type::S_TYPE, "type", "testIdentifyType"},
      {Parser::symbol_kind_type::S_SAME, "same", "testIdentifySame"},
      {Parser::symbol_kind_type::S_AS, "as", "testIdentifyAs"},
      {Parser::symbol_kind_type::S_SEMICOLON, ";", "testIdentifySemicolon"},
      {Parser::symbol_kind_type::S_COMMA, ",", "testIdentifyComma"},
      {Parser::symbol_kind_type::S_COLON, ":", "testIdentifyColon"},
      {Parser::symbol_kind_type::S_LPAR, "(", "testIdentifyLpar"},
      {Parser::symbol_kind_type::S_RPAR, ")", "testIdentifyRpar"},
      {Parser::symbol_kind_type::S_LSBRACKET, "[", "testIdentifyLsbracket"},
      {Parser::symbol_kind_type::S_RSBRACKET, "]", "testIdentifyRsbracket"},
      {Parser::symbol_kind_type::S_LCBRACKET, "{", "testIdentifyLcbracket"},
      {Parser::symbol_kind_type::S_RCBRACKET, "}", "testIdentifyRcbracket"},
      {Parser::symbol_kind_type::S_NOTIFY_OP, "->", "testIdentifyNotifyOp"},
      {Parser::symbol_kind_type::S_ELLIPSIS, "...", "testIdentifyEllipsis"},
      {Parser::symbol_kind_type::S_HOLON_OP, "<>", "testIdentifyHolon_op"},
      {Parser::symbol_kind_type::S_ASSIGN, ":=", "testIdentifyAssign"},
      {Parser::symbol_kind_type::S_ASSIGN_PLUS, "+=", "testIdentifyAssignPlus"},
      {Parser::symbol_kind_type::S_ASSIGN_MINUS, "-=", "testIdentifyAssignMinus"},
      {Parser::symbol_kind_type::S_ASSIGN_MUL, "*=", "testIdentifyAssignMul"},
      {Parser::symbol_kind_type::S_ASSIGN_DIV, "/=", "testIdentifyAssignDiv"},
      {Parser::symbol_kind_type::S_ASSIGN_MOD, "%=", "testIdentifyAssignMod"},
      {Parser::symbol_kind_type::S_ASSIGN_AND, "&=", "testIdentifyAssignAnd"},
      {Parser::symbol_kind_type::S_ASSIGN_OR, "|=", "testIdentifyAssignOr"},
      {Parser::symbol_kind_type::S_ASSIGN_XOR, "^=", "testIdentifyAssignXor"},
      {Parser::symbol_kind_type::S_LOGIC_OR, "||", "testIdentifyLogicOr"},
      {Parser::symbol_kind_type::S_LOGIC_XOR, "^^", "testIdentifyLogicXor"},
      {Parser::symbol_kind_type::S_LOGIC_AND, "&&", "testIdentifyLogicAnd"},
      {Parser::symbol_kind_type::S_BINARY_OR, "|", "testIdentifyBinaryOr"},
      {Parser::symbol_kind_type::S_BINARY_XOR, "^", "testIdentifyBinaryXor"},
      {Parser::symbol_kind_type::S_BINARY_AND, "&", "testIdentifyBinaryAnd"},
      {Parser::symbol_kind_type::S_EQ, "==", "testIdentifyEq"},
      {Parser::symbol_kind_type::S_NE, "!=", "testIdentifyNe"},
      {Parser::symbol_kind_type::S_LT, "<", "testIdentifyLt"},
      {Parser::symbol_kind_type::S_LE, "<=", "testIdentifyLe"},
      {Parser::symbol_kind_type::S_GT, ">", "testIdentifyGt"},
      {Parser::symbol_kind_type::S_GE, ">=", "testIdentifyGe"},
      {Parser::symbol_kind_type::S_SHIFT_LEFT, "<<", "testIdentifyShiftLeft"},
      {Parser::symbol_kind_type::S_SHIFT_RIGHT, ">>", "testIdentifyShiftRight"},
      {Parser::symbol_kind_type::S_PLUS, "+", "testIdentifyPlus"},
      {Parser::symbol_kind_type::S_MINUS, "-", "testIdentifyMinus"},
      {Parser::symbol_kind_type::S_MUL, "*", "testIdentifyMul"},
      {Parser::symbol_kind_type::S_DIV, "/", "testIdentifyDiv"},
      {Parser::symbol_kind_type::S_MOD, "%", "testIdentifyMod"},
      {Parser::symbol_kind_type::S_LOGIC_NOT, "!", "testIdentifyLogicNot"},
      {Parser::symbol_kind_type::S_BINARY_NOT, "~", "testIdentifyBinaryNot"},
      {Parser::symbol_kind_type::S_INC, "++", "testIdentifyInc"},
      {Parser::symbol_kind_type::S_DEC, "--", "testIdentifyDec"},
      {Parser::symbol_kind_type::S_DOT, ".", "testIdentifyDot"},
      {Parser::symbol_kind_type::S_APOSTROPHE, "'", "testIdentifyApostrophe"},
  };

  INSTANTIATE_TEST_SUITE_P(testIdentifyPunctiationOperatorsKeywords, CharLiteralsScannerTest,
                           testing::ValuesIn(simpleTokenPairs), [](const testing::TestParamInfo<charLiteralTestParam> &info)
                           { return std::get<2>(info.param); });
}