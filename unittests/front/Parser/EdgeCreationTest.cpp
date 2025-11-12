#include "VertexAccessExpr.h"
#include "interpreter.h"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>

namespace Gnocchi {

class EdgeCreationTest : public testing::Test {
public:
  Interpreter *obj;
  std::stringstream input;

  virtual void SetUp() override {
    obj = new Interpreter("mock.gno");
    obj->switchInputStream(&input);
  }

  virtual void TearDown() override {
    delete obj;
    input.clear();
    input.str("");
  }

  void testCreateMinimalEdge() {
    input << "declare a is vertex;\n"
             "declare b is vertex;\n"
             "edge a -> b;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(2, g.getVertices().size());
    ASSERT_EQ(1, g.getEdges().size());
    shared_ptr<EN::Edge> edge = g.getEdges().front();
    shared_ptr<EN::VertexAccessExpr> source = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->source);
    ASSERT_NE(nullptr, source);
    ASSERT_EQ(obj->getGraph().getVertex("a"), source->getVertex().lock());
    shared_ptr<EN::VertexAccessExpr> destination = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->destination);
    ASSERT_NE(nullptr, destination);
    ASSERT_EQ(obj->getGraph().getVertex("b"), destination->getVertex().lock());
  }

  void testCreateVertexWithClause() {
    input << "declare a is vertex;\n"
             "declare b is vertex (p is int32);\n"
             "edge a -> b with 10;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getEdges().size());
    shared_ptr<EN::Edge> edge = g.getEdges().front();

    ASSERT_NE(nullptr, edge->with);
    shared_ptr<EN::LiteralExpr> expr = dynamic_pointer_cast<EN::LiteralExpr>(edge->with);
    ASSERT_NE(nullptr, expr);
    ASSERT_EQ(EN::LiteralExpr::UINT, expr->getLiteralType());
    ASSERT_EQ(10, expr->getUint());
  }

  void testCreateVertexWhenClause() {
    input << "declare a is vertex;\n"
             "declare b is vertex;\n"
             "edge a -> b when true;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(2, g.getVertices().size());
    ASSERT_EQ(1, g.getEdges().size());
    ASSERT_NE(nullptr, g.getVertices().front());
    shared_ptr<EN::Edge> edge = g.getEdges().front();

    ASSERT_NE(nullptr, edge->when);
    shared_ptr<EN::LiteralExpr> expr = dynamic_pointer_cast<EN::LiteralExpr>(edge->when);
    ASSERT_NE(nullptr, expr);
    ASSERT_EQ(EN::LiteralExpr::BOOL, expr->getLiteralType());
    ASSERT_EQ(true, expr->getBool());
  }

  void testCreateMultipleVerticesLeft() {
    input << "declare a is vertex;\n"
             "declare b is vertex;\n"
             "declare c is vertex;\n"
             "edge [a, b] -> c;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(3, g.getVertices().size());
    ASSERT_EQ(2, g.getEdges().size());
    ASSERT_NE(nullptr, g.getVertices().front());

    shared_ptr<EN::Edge> edge = g.getEdges().front();
    shared_ptr<EN::VertexAccessExpr> source = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->source);
    ASSERT_NE(nullptr, source);
    ASSERT_EQ(obj->getGraph().getVertex("a"), source->getVertex().lock());
    shared_ptr<EN::VertexAccessExpr> destination = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->destination);
    ASSERT_NE(nullptr, destination);
    ASSERT_EQ(obj->getGraph().getVertex("c"), destination->getVertex().lock());

    edge = g.getEdges().back();
    source = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->source);
    ASSERT_NE(nullptr, source);
    ASSERT_EQ(obj->getGraph().getVertex("b"), source->getVertex().lock());
    destination = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->destination);
    ASSERT_NE(nullptr, destination);
    ASSERT_EQ(obj->getGraph().getVertex("c"), destination->getVertex().lock());
  }

  void testCreateMultipleVerticesRight() {
    input << "declare a is vertex;\n"
             "declare b is vertex;\n"
             "declare c is vertex;\n"
             "edge a -> [b, c];";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(3, g.getVertices().size());
    ASSERT_EQ(2, g.getEdges().size());
    ASSERT_NE(nullptr, g.getVertices().front());

    shared_ptr<EN::Edge> edge = g.getEdges().front();
    shared_ptr<EN::VertexAccessExpr> source = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->source);
    ASSERT_NE(nullptr, source);
    ASSERT_EQ(obj->getGraph().getVertex("a"), source->getVertex().lock());
    shared_ptr<EN::VertexAccessExpr> destination = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->destination);
    ASSERT_NE(nullptr, destination);
    ASSERT_EQ(obj->getGraph().getVertex("b"), destination->getVertex().lock());

    edge = g.getEdges().back();
    source = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->source);
    ASSERT_NE(nullptr, source);
    ASSERT_EQ(obj->getGraph().getVertex("a"), source->getVertex().lock());
    destination = dynamic_pointer_cast<EN::VertexAccessExpr>(edge->destination);
    ASSERT_NE(nullptr, destination);
    ASSERT_EQ(obj->getGraph().getVertex("c"), destination->getVertex().lock());
  }

  void testCreateMultipleVertices() {
    input << "declare a is vertex;\n"
             "declare b is vertex;\n"
             "declare c is vertex;\n"
             "declare d is vertex;\n"
             "edge [a, b] -> [c, d];";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(4, g.getVertices().size());
    ASSERT_EQ(4, g.getEdges().size());
  }
};

#define EDGE_CREATION_TEST(METHOD)                                                                                     \
  TEST_F(EdgeCreationTest, METHOD) { this->METHOD(); }

EDGE_CREATION_TEST(testCreateMinimalEdge)
EDGE_CREATION_TEST(testCreateVertexWithClause)
EDGE_CREATION_TEST(testCreateVertexWhenClause)
EDGE_CREATION_TEST(testCreateMultipleVerticesLeft)
EDGE_CREATION_TEST(testCreateMultipleVerticesRight)
EDGE_CREATION_TEST(testCreateMultipleVertices)
} // namespace Gnocchi