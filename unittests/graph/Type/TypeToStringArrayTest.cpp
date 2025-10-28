#include "gtest/gtest.h"

#include "ArrayType.h"
#include "LiteralExpr.h"
#include "PrimitiveType.h"
namespace EN {
using namespace std;

class TypeToStringArrayTest : public testing::Test {

private:
  shared_ptr<Expr> makeLiteral(int value) { return make_shared<LiteralExpr>(value); }

public:
  void testOneDArrayToString() {
    const weak_ptr<Type> charType = PrimitiveType::getPrimitiveType(PrimitiveType::CHAR);
    const ArrayType array(charType, {make_shared<LiteralExpr>(10)});
    string str = array.toString();
    ASSERT_EQ(str, "char[10]");
  }

  void test3DArrayToString() {
    const weak_ptr<Type> charType = PrimitiveType::getPrimitiveType(PrimitiveType::CHAR);
    const ArrayType array(charType, {makeLiteral(1), makeLiteral(2), makeLiteral(3)});
    string str = array.toString();
    ASSERT_EQ(str, "char[1][2][3]");
  }
};

#define TYPE_TO_STRING_ARRAY_TEST(METHOD)                                                                              \
  TEST_F(TypeToStringArrayTest, METHOD) { this->METHOD(); }

TYPE_TO_STRING_ARRAY_TEST(testOneDArrayToString)
TYPE_TO_STRING_ARRAY_TEST(test3DArrayToString)

} // namespace EN