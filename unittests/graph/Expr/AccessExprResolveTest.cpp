#include "gtest/gtest.h"

#include "VertexAccessExpr.h"
#include "ENScope.h"
#include "ENVertex.h"
#include "VertexBuilder.h"
#include "SemanticException.h"

namespace EN
{
    using namespace std;

    class AccessExprResolveTest : public testing::Test
    {
    public:
        shared_ptr<Vertex> v;

        virtual void SetUp() override
        {
            v = VertexBuilder().setId("vertex1").build();
        }

        void resolveManuallyTest()
        {
            VertexAccessExpr access{"vertex1"};
            ASSERT_THROW(access.getVertex(), SemanticException);
            access.resolve(v);
            ASSERT_EQ(v->id, access.getVertex().lock()->id);
        }

        void resolveWithScope()
        {
            shared_ptr<Scope> scope = make_shared<Scope>();
            VertexAccessExpr access{"vertex1", scope};
            ASSERT_THROW(access.getVertex(), SemanticException);
            scope->addVertex(v);
            ASSERT_EQ(v->id, access.getVertex().lock()->id);
        }
    };

#define ACCESS_EXPR_RESOLVE_TEST(METHOD)  \
    TEST_F(AccessExprResolveTest, METHOD) \
    {                                     \
        this->METHOD();                   \
    }

    ACCESS_EXPR_RESOLVE_TEST(resolveManuallyTest)
    ACCESS_EXPR_RESOLVE_TEST(resolveWithScope)
}