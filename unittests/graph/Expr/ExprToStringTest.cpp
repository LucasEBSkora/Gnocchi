#include "gtest/gtest.h"

#include "ENExprs.h"

namespace EN
{
    using namespace std;

    class ExprToStringTest : public testing::Test
    {
    public:
        void vertexAccessTest()
        {
            VertexAccessExpr access{"this"};
            ASSERT_EQ("this", access.toString());
        }

        void notifyTest()
        {
            shared_ptr<VertexAccessExpr> access = make_shared<VertexAccessExpr>("this");
            NotifyExpr expr{{make_shared<LiteralExpr>(10), make_shared<LiteralExpr>("hello")}, access};
            ASSERT_EQ("( 10 \"hello\" ) -> this", expr.toString());
        }
    };

#define EXPR_TO_STRING_TEST(METHOD)  \
    TEST_F(ExprToStringTest, METHOD) \
    {                                \
        this->METHOD();              \
    }

    EXPR_TO_STRING_TEST(vertexAccessTest)
    EXPR_TO_STRING_TEST(notifyTest)
}