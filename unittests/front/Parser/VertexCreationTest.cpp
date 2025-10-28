#include "ENExpr.h"
#include "ENGraphCommon.h"
#include "ENVertex.h"
#include "LiteralExpr.h"
#include "NotificationParameter.h"
#include "PrimitiveType.h"
#include "interpreter.h"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>

namespace Gnocchi {

class VertexCreationTest : public testing::Test {
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

  void testCreateMinimalVertex() {
    input << "declare vertex;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    ASSERT_NE(nullptr, g.getVertices().front());
  }

  void testCreatePublicVertex() {
    input << "public vertex;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    shared_ptr<EN::Vertex> v = g.getVertices().front();
    ASSERT_EQ(EN::Visibility::PUBLIC, v->visibility);
  }

  void testCreateNamedVertex() {
    input << "declare named_vertex is vertex;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    shared_ptr<EN::Vertex> v = g.getVertices().front();
    ASSERT_EQ("named_vertex", v->id);
  }

  void testCreateTypedVertex() {
    input << "declare vertex bool;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    shared_ptr<EN::Vertex> v = g.getVertices().front();
    shared_ptr<EN::Type> type = v->type.lock();
    ASSERT_NE(nullptr, type);
    ASSERT_EQ(*EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::BOOL).lock(), *type);
  }

  void testCreateOneNotificationParameter() {
    input << "declare vertex (p1 is int32);";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    shared_ptr<EN::Vertex> v = g.getVertices().front();
    ASSERT_EQ(1, v->notificationParameters.size());
    const EN::NotificationParameter &param = v->notificationParameters.front();
    ASSERT_EQ("p1", param.name);
    ASSERT_EQ(*EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::INT32).lock(), *param.type.lock());
    ASSERT_FALSE(param.defaultValue.has_value());
  }

  void testCreateDefaultNotificationParameter() {
    input << "declare vertex (p1 is int32 default 5);";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    shared_ptr<EN::Vertex> v = g.getVertices().front();
    ASSERT_EQ(1, v->notificationParameters.size());
    const EN::NotificationParameter &param = v->notificationParameters.front();
    ASSERT_EQ("p1", param.name);
    ASSERT_EQ(*EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::INT32).lock(), *param.type.lock());
    ASSERT_TRUE(param.defaultValue.has_value());
    shared_ptr<EN::LiteralExpr> expr = dynamic_pointer_cast<EN::LiteralExpr>(param.defaultValue.value());
    ASSERT_NE(nullptr, expr);
    ASSERT_EQ(EN::LiteralExpr::UINT, expr->getLiteralType());
    ASSERT_EQ(5, expr->getUint());
  }

  void testCreateMultipleNotificationParameters() {
    input << "declare vertex (p1 is int32, p2 is bool, p3 is int8 default 9);";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    shared_ptr<EN::Vertex> v = g.getVertices().front();
    ASSERT_EQ(3, v->notificationParameters.size());
  }

  void testCreateVertexWithState() {
    input << "declare vertex (p1 is bool), state !p1;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    shared_ptr<EN::Vertex> v = g.getVertices().front();
    shared_ptr<EN::Expr> expr = v->stateExpr;
    ASSERT_NE(nullptr, expr);
  }
};

#define VERTEX_CREATION_TEST(METHOD)                                                                                   \
  TEST_F(VertexCreationTest, METHOD) { this->METHOD(); }

VERTEX_CREATION_TEST(testCreateMinimalVertex)
VERTEX_CREATION_TEST(testCreatePublicVertex)
VERTEX_CREATION_TEST(testCreateNamedVertex)
VERTEX_CREATION_TEST(testCreateTypedVertex)
VERTEX_CREATION_TEST(testCreateOneNotificationParameter)
VERTEX_CREATION_TEST(testCreateDefaultNotificationParameter)
VERTEX_CREATION_TEST(testCreateMultipleNotificationParameters)
VERTEX_CREATION_TEST(testCreateVertexWithState)

} // namespace Gnocchi