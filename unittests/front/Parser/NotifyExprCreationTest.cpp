#include "ENVertex.h"
#include "NotifyExpr.h"
#include "VertexAccessExpr.h"
#include "interpreter.h"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>

namespace Gnocchi {

class NotifyExprCreationTest : public testing::Test {
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

  void testCreateNotificationNoParam() {
    input << "declare a is vertex;\n"
             "-> a;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();
    ASSERT_EQ(1, g.getVertices().size());
    shared_ptr<EN::Vertex> v = g.getVertex("a");

    ASSERT_EQ(1, g.getInitialNotifications().size());
    shared_ptr<EN::NotifyExpr> expr = g.getInitialNotifications().front();
    ASSERT_NE(nullptr, expr->target);
    shared_ptr<EN::VertexAccessExpr> access = dynamic_pointer_cast<EN::VertexAccessExpr>(expr->target);
    ASSERT_EQ(v, access->getVertex().lock());
    ASSERT_EQ(0, expr->params.size());
  }

  void testCreateNotificationOneParam() {
    input << "declare a is vertex (p1 is int32);\n"
             "10 -> a;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();

    ASSERT_EQ(1, g.getInitialNotifications().size());
    shared_ptr<EN::NotifyExpr> expr = g.getInitialNotifications().front();
    ASSERT_EQ(1, expr->params.size());
  }

  void testCreateNotificationParams() {
    input << "declare a is vertex (p1 is int32, p2 is int32);\n"
             "10, 15 -> a;";
    ASSERT_EQ(0, obj->parse());
    EN::Graph &g = obj->getGraph();

    ASSERT_EQ(1, g.getInitialNotifications().size());
    shared_ptr<EN::NotifyExpr> expr = g.getInitialNotifications().front();
    ASSERT_EQ(2, expr->params.size());
  }
};

#define NOTIFY_EXPR_CREATION_TEST(METHOD)                                                                              \
  TEST_F(NotifyExprCreationTest, METHOD) { this->METHOD(); }

NOTIFY_EXPR_CREATION_TEST(testCreateNotificationNoParam)
NOTIFY_EXPR_CREATION_TEST(testCreateNotificationOneParam)
NOTIFY_EXPR_CREATION_TEST(testCreateNotificationParams)
} // namespace Gnocchi