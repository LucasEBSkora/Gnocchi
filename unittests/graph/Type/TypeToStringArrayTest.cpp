#include "gtest/gtest.h"

#include "ENExprs.h"
#include "ENTypes.h"

namespace EN {
using namespace std;

class TypeToStringArrayTest : public testing::Test {

private:
  shared_ptr<Expr> makeLiteral(int value) {
    return make_shared<LiteralExpr>(value);
  }

public:
  void testOneDArrayToString() {
    const weak_ptr<Type> charType =
        PrimitiveType::getPrimitiveType(PrimitiveType::CHAR);
    const ArrayType array(charType, {make_shared<LiteralExpr>(10)});
    string str = array.toString();
    ASSERT_EQ(str, "char[10]");
  }

  void test3DArrayToString() {
    const weak_ptr<Type> charType =
        PrimitiveType::getPrimitiveType(PrimitiveType::CHAR);
    const ArrayType array(charType,
                          {makeLiteral(1), makeLiteral(2), makeLiteral(3)});
    string str = array.toString();
    ASSERT_EQ(str, "char[1][2][3]");
  }
};

TEST_F(TypeToStringArrayTest, testOneDArrayToString) {
  this->testOneDArrayToString();
}

} // namespace EN