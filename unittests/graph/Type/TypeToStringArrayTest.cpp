#include "gtest/gtest.h"

#include "ENTypes.h"

#include <iostream>

using TestParam = std::tuple<EN::PrimitiveType::Primitive, const char *, const char *>;

namespace EN
{

  class TypeToStringPrimitiveTest : public testing::Test, public testing::WithParamInterface<TestParam>
  {
  public:
    void testTypeToStringPrimitive(EN::PrimitiveType::Primitive type, const char *expected)
    {
      const std::weak_ptr<Type> typeInst = PrimitiveType::getPrimitiveType(type);
      ASSERT_EQ(expected, typeInst.lock()->toString());
    }
  };

  TEST_P(TypeToStringPrimitiveTest, testTypeToStringPrimitive)
  {
    TestParam p = GetParam();
    this->testTypeToStringPrimitive(std::get<0>(p), std::get<1>(p));
  }

  const std::vector<TestParam> testTuples{
      {PrimitiveType::INT8, "int8", "testINT8ToString"},
      {PrimitiveType::INT16, "int16", "testINT16ToString"},
      {PrimitiveType::INT24, "int24", "testINT24ToString"},
      {PrimitiveType::INT32, "int32", "testINT32ToString"},
      {PrimitiveType::INT, "int", "testINTToString"},
      {PrimitiveType::UIT8, "uit8", "testUIT8ToString"},
      {PrimitiveType::UINT16, "uint16", "testUINT16ToString"},
      {PrimitiveType::UINT24, "uint24", "testUINT24ToString"},
      {PrimitiveType::UINT32, "uint32", "testUINT32ToString"},
      {PrimitiveType::UINT, "uint", "testUINTToString"},
      {PrimitiveType::FLOAT, "float", "testFLOATToString"},
      {PrimitiveType::DOUBLE, "double", "testDOUBLEToString"},
      {PrimitiveType::NUMBER, "number", "testNUMBERToString"},
      {PrimitiveType::BOOL, "bool", "testBOOLToString"},
      {PrimitiveType::CHAR, "char", "testCHARToString"},
  };

  INSTANTIATE_TEST_SUITE_P(testPrimitiveTypeToString, TypeToStringPrimitiveTest,
                           testing::ValuesIn(testTuples), [](const testing::TestParamInfo<TestParam> &info)
                           { return std::get<2>(info.param); });

}