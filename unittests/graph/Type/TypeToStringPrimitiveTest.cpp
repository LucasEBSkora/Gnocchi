#include "gtest/gtest.h"

#include "ENTypes.h"
#include "ENExprs.h"

namespace EN
{

  class TypeToStringArrayTest : public testing::Test
  {

  private:
    std::shared_ptr<Expr> makeLiteral(int value)
    {
      return std::make_shared<LiteralExpr>(value);
    }

  public:
    void testOneDArrayToString()
    {
      const std::weak_ptr<Type> charType = PrimitiveType::getPrimitiveType(PrimitiveType::CHAR);
      const ArrayType array(charType, {std::make_shared<LiteralExpr>(10)});
      std::string str = array.toString();
      ASSERT_EQ(str, "char[10]");
    }

    void test3DArrayToString()
    {
      const std::weak_ptr<Type> charType = PrimitiveType::getPrimitiveType(PrimitiveType::CHAR);
      const ArrayType array(charType, {makeLiteral(1), makeLiteral(2), makeLiteral(3)});
      std::string str = array.toString();
      ASSERT_EQ(str, "char[1][2][3]");
    }
  };

  TEST_F(TypeToStringArrayTest, testOneDArrayToString)
  {
    this->testOneDArrayToString();
  }

}