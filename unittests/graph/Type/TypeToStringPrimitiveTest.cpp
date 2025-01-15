#include "gtest/gtest.h"

#include "ENTypes.h"

namespace EN
{

  class TypeToStringArrayTest : public testing::Test
  {
  public:
    void testOneDArrayToString()
    {
      const std::weak_ptr<Type> charType = PrimitiveType::getPrimitiveType(PrimitiveType::CHAR);
      const ArrayType array(charType, {10});
      std::string str = array.toString();
      ASSERT_EQ(str, "char[10]");
    }
  };

  TEST_F(TypeToStringArrayTest, testOneDArrayToString)
  {
    this->testOneDArrayToString();
  }

}