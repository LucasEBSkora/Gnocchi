#include "PrimitiveType.h"
#include "parser.hpp"
#include "scanner.h"
#include "gtest/gtest.h"
#include <memory>

namespace Gnocchi {

using namespace std;
using namespace EN;
using PrimitiveTypeParam =
    tuple<Gnocchi::Parser::symbol_kind_type, PrimitiveType::Primitive,
          const char *, const char *>;

class PrimitiveTypeScannerTest
    : public testing::Test,
      public testing::WithParamInterface<PrimitiveTypeParam> {
public:
  Scanner *obj;
  LocationProvider provider{"mock.gno"};

  virtual void SetUp() override { obj = new Scanner(provider); }

  virtual void TearDown() override {
    provider.reset();
    delete obj;
  }

  void testIdentifyPrimitiveType(Parser::symbol_kind_type type,
                                 PrimitiveType::Primitive primitive,
                                 const char *text) {
    stringstream stream;
    stream << text;
    obj->switch_streams(&stream, nullptr);
    Gnocchi::Parser::symbol_type token = obj->get_next_token();
    ASSERT_EQ(type, token.kind());
    ASSERT_EQ(*PrimitiveType::getPrimitiveType(primitive).lock(),
              *token.value.as<weak_ptr<Type>>().lock());
  }
};

TEST_P(PrimitiveTypeScannerTest, testIdentifyPrimitiveType) {
  PrimitiveTypeParam p = GetParam();
  this->testIdentifyPrimitiveType(get<0>(p), get<1>(p), get<2>(p));
}

const vector<PrimitiveTypeParam> primitiveTypeParams{
    {Parser::symbol_kind_type::S_INT, PrimitiveType::Primitive::INT, "int",
     "testIdentifyInt"},
    {Parser::symbol_kind_type::S_INT8, PrimitiveType::Primitive::INT8, "int8",
     "testIdentifyInt8"},
    {Parser::symbol_kind_type::S_INT16, PrimitiveType::Primitive::INT16,
     "int16", "testIdentifyInt16"},
    {Parser::symbol_kind_type::S_INT24, PrimitiveType::Primitive::INT24,
     "int24", "testIdentifyInt24"},
    {Parser::symbol_kind_type::S_INT32, PrimitiveType::Primitive::INT32,
     "int32", "testIdentifyInt32"},
    {Parser::symbol_kind_type::S_UINT, PrimitiveType::Primitive::UINT, "uint",
     "testIdentifyUint"},
    {Parser::symbol_kind_type::S_UINT8, PrimitiveType::Primitive::UINT8,
     "uint8", "testIdentifyUint8"},
    {Parser::symbol_kind_type::S_UINT16, PrimitiveType::Primitive::UINT16,
     "uint16", "testIdentifyUint16"},
    {Parser::symbol_kind_type::S_UINT24, PrimitiveType::Primitive::UINT24,
     "uint24", "testIdentifyUint24"},
    {Parser::symbol_kind_type::S_UINT32, PrimitiveType::Primitive::UINT32,
     "uint32", "testIdentifyUint32"},
    {Parser::symbol_kind_type::S_FLOAT, PrimitiveType::Primitive::FLOAT,
     "float", "testIdentifyFloat"},
    {Parser::symbol_kind_type::S_DOUBLE, PrimitiveType::Primitive::DOUBLE,
     "double", "testIdentifyDouble"},
    {Parser::symbol_kind_type::S_NUMBER, PrimitiveType::Primitive::NUMBER,
     "number", "testIdentifyNumber"},
    {Parser::symbol_kind_type::S_BOOL, PrimitiveType::Primitive::BOOL, "bool",
     "testIdentifyBool"},
    {Parser::symbol_kind_type::S_CHAR, PrimitiveType::Primitive::CHAR, "char",
     "testIdentifyChar"},
};

INSTANTIATE_TEST_SUITE_P(
    testIdentifyPrimitiveTypes, PrimitiveTypeScannerTest,
    testing::ValuesIn(primitiveTypeParams),
    [](const testing::TestParamInfo<PrimitiveTypeParam> &info) {
      return get<3>(info.param);
    });
} // namespace Gnocchi