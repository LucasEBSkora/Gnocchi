#include "gtest/gtest.h"
#include <list>
#include <memory>

#include "ENEdge.h"
#include "ENScope.h"
#include "VertexAccessExpr.h"
namespace EN {
using namespace std;

class createMultipleEdgesTest : public testing::Test {
  Scope *scope;
  shared_ptr<Expr> expr1;
  shared_ptr<Expr> expr2;
  shared_ptr<Expr> expr3;
  shared_ptr<Expr> expr4;

public:
  void SetUp() override {
    scope = new EN::Scope();
    expr1 = make_shared<VertexAccessExpr>("vertex1", *scope);
    expr2 = make_shared<VertexAccessExpr>("vertex2", *scope);
    expr3 = make_shared<VertexAccessExpr>("vertex3", *scope);
    expr4 = make_shared<VertexAccessExpr>("vertex4", *scope);
  }

  void TearDown() override { delete scope; }

  void createSingleEdgeTest() {
    list<shared_ptr<Edge>> edges = Edge::createMultipleEdges({expr1}, {expr2}, nullptr, nullptr);
    ASSERT_EQ(1, edges.size());
    ASSERT_EQ("vertex1", edges.front()->source->toString());
    ASSERT_EQ("vertex2", edges.front()->destination->toString());
  }

  void createMultipleEdgesLeftTest() {
    list<shared_ptr<Edge>> edges = Edge::createMultipleEdges({expr1, expr3}, {expr2}, nullptr, nullptr);
    ASSERT_EQ(2, edges.size());
    shared_ptr<Edge> first = edges.front();
    ASSERT_EQ("vertex1", first->source->toString());
    ASSERT_EQ("vertex2", first->destination->toString());
    shared_ptr<Edge> second = edges.back();
    ASSERT_EQ("vertex3", second->source->toString());
    ASSERT_EQ("vertex2", second->destination->toString());
  }

  void createMultipleEdgesRightTest() {
    list<shared_ptr<Edge>> edges = Edge::createMultipleEdges({expr1}, {expr2, expr4}, nullptr, nullptr);
    shared_ptr<Edge> first = edges.front();
    ASSERT_EQ(2, edges.size());
    ASSERT_EQ("vertex1", first->source->toString());
    ASSERT_EQ("vertex2", first->destination->toString());
    shared_ptr<Edge> second = edges.back();
    ASSERT_EQ("vertex1", second->source->toString());
    ASSERT_EQ("vertex4", second->destination->toString());
  }

  void createMultipleEdgesManyTest() {
    list<shared_ptr<Edge>> edges = Edge::createMultipleEdges({expr1, expr3}, {expr2, expr4}, nullptr, nullptr);
    ASSERT_EQ(4, edges.size());
    auto it = edges.begin();
    shared_ptr<Edge> first = *(it++);
    ASSERT_EQ("vertex1", first->source->toString());
    ASSERT_EQ("vertex2", first->destination->toString());
    shared_ptr<Edge> second = *(it++);
    ASSERT_EQ("vertex1", second->source->toString());
    ASSERT_EQ("vertex4", second->destination->toString());
    shared_ptr<Edge> third = *(it++);
    ASSERT_EQ("vertex3", third->source->toString());
    ASSERT_EQ("vertex2", third->destination->toString());
    shared_ptr<Edge> fourth = *(it++);
    ASSERT_EQ("vertex3", fourth->source->toString());
    ASSERT_EQ("vertex4", fourth->destination->toString());
  }
};

#define CREATE_MULTIPLE_EDGES_TEST(METHOD)                                                                             \
  TEST_F(createMultipleEdgesTest, METHOD) { this->METHOD(); }

CREATE_MULTIPLE_EDGES_TEST(createSingleEdgeTest)
CREATE_MULTIPLE_EDGES_TEST(createMultipleEdgesLeftTest)
CREATE_MULTIPLE_EDGES_TEST(createMultipleEdgesRightTest)
CREATE_MULTIPLE_EDGES_TEST(createMultipleEdgesManyTest)

} // namespace EN