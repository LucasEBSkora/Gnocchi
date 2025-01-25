#include "gtest/gtest.h"
#include "ENScope.h"
#include "VertexBuilder.h"
#include "SemanticException.h"

namespace EN
{
    using namespace std;

    class ScopeTest : public testing::Test
    {
    public:
        Scope *obj;

        virtual void SetUp() override
        {
            obj = new Scope();
        }

        virtual void TearDown() override
        {
            delete obj;
        }

        void testAddVertexUnnamed()
        {
            VertexBuilder builder;
            shared_ptr<Vertex> v = builder.setVisibility(Visibility::PUBLIC).build();
            obj->addVertex(v);
            ASSERT_FALSE(obj->hasVertex(""));
            ASSERT_EQ(1, obj->getVertices().size());
            ASSERT_EQ(Visibility::PUBLIC, obj->getVertices()[0]->visibility);
        }

        void testAddVertexNamed()
        {
            VertexBuilder builder;
            shared_ptr<Vertex> v = builder.setId("vertex0").build();
            obj->addVertex(v);
            ASSERT_TRUE(obj->hasVertex("vertex0"));
            ASSERT_EQ(1, obj->getVertices().size());
            ASSERT_EQ("vertex0", obj->getVertices()[0]->id);
            ASSERT_EQ(v, obj->getVertex("vertex0"));
        }

        void testAddEdge()
        {
            obj->addEdge(make_shared<Edge>(shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>()));
            ASSERT_EQ(1, obj->getEdges().size());
        }

        void testGetVertices()
        {
            VertexBuilder builder;

            obj->addVertex(builder.setId("10").build());
            obj->addVertex(builder.setId("20").build());
            ASSERT_EQ(2, obj->getVertices().size());
        }

        void testHasVertex()
        {
            ASSERT_FALSE(obj->hasVertex("10"));
            VertexBuilder builder;
            obj->addVertex(builder.setId("10").build());
            ASSERT_TRUE(obj->hasVertex("10"));
            ASSERT_FALSE(obj->hasVertex("20"));
        }

        void testGetVertexWorks()
        {
            VertexBuilder builder;
            obj->addVertex(builder.setId("1").build());
            ASSERT_TRUE(obj->getVertex("1"));
        }

        void testGetVertexFails()
        {
            ASSERT_THROW(obj->getVertex("1"), SemanticException);
        }

        void testGetEdges()
        {
            obj->addEdge(make_shared<Edge>(shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>()));
            obj->addEdge(make_shared<Edge>(shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>()));
            obj->addEdge(make_shared<Edge>(shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>()));
            ASSERT_EQ(3, obj->getEdges().size());
        }
    };

#define SCOPE_TEST(METHOD)    \
    TEST_F(ScopeTest, METHOD) \
    {                         \
        this->METHOD();       \
    }

    SCOPE_TEST(testAddVertexUnnamed)
    SCOPE_TEST(testAddVertexNamed)
    SCOPE_TEST(testAddEdge)
    SCOPE_TEST(testGetVertices)
    SCOPE_TEST(testHasVertex)
    SCOPE_TEST(testGetVertexWorks)
    SCOPE_TEST(testGetVertexFails)
    SCOPE_TEST(testGetEdges)

}