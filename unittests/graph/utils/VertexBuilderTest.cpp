#include "VertexBuilder.h"
#include "ENVertex.h"
#include "LiteralExpr.h"
#include "gtest/gtest.h"

namespace EN {

using namespace std;

class VertexBuilderTest : public testing::Test {
public:
  VertexBuilder *obj;

  virtual void SetUp() override { obj = new VertexBuilder(); }

  virtual void TearDown() override { delete obj; }

  void testBuildEmpty() {
    shared_ptr<Vertex> v = obj->build();
    ASSERT_TRUE(v->type.expired());
    ASSERT_EQ("", v->id);
    ASSERT_EQ(Visibility::DEFAULT, v->visibility);
    ASSERT_EQ(0, v->notificationParameters.size());
    ASSERT_FALSE(v->stateExpr);
    ASSERT_FALSE(v->boundState);
    ASSERT_EQ(0, v->interfaces.size());
    ASSERT_FALSE(v->initialValue);
    ASSERT_EQ(int(AllowedOperations::ALL), v->allowedOperations);
    ASSERT_FALSE(v->defaultWhen);
    ASSERT_FALSE(v->defaultWith);
    ASSERT_EQ(0, v->getEdges().size());
  }

  void testSetType() {
    weak_ptr<Type> t = PrimitiveType::getPrimitiveType(PrimitiveType::BOOL);
    obj->setType(t);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_FALSE(v->type.expired());
    ASSERT_EQ("bool", v->type.lock()->toString());
  }

  void testSetId() {
    obj->setId("10");
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ("10", v->id);
  }

  void testSetVisibility() {
    obj->setVisibility(Visibility::PRIVATE);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ(Visibility::PRIVATE, v->visibility);
  }

  void testAddNotificationparameter() {
    obj->addNotificationParameter({"first", PrimitiveType::getPrimitiveType(PrimitiveType::INT8)});
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ(1, v->notificationParameters.size());
    ASSERT_EQ("first", v->notificationParameters[0].name);
  }

  void testSetStateExpr() {
    shared_ptr<Expr> expr = make_shared<LiteralExpr>(20);
    obj->setStateExpr(expr);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_TRUE(v->stateExpr);
    ASSERT_EQ("20", v->stateExpr->toString());
  }

  void testsetBoundState() {
    obj->setBoundState(true);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_TRUE(v->boundState);
  }

  void testAddInterface() {
    obj->addInterface("Rule");
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ(1, v->interfaces.size());
    ASSERT_EQ("Rule", v->interfaces[0]);
  }

  void testSetInitialValue() {
    shared_ptr<Expr> expr = make_shared<LiteralExpr>("potato");
    obj->setInitialValue(expr);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_TRUE(v->initialValue);
    ASSERT_EQ("\"potato\"", v->initialValue->toString());
  }

  void testDisableAllOperations() {
    obj->setDisabledOperations(AllowedOperations::ALL);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ(AllowedOperations::NONE, v->allowedOperations);
  }

  void testEnableAllOperations() {
    obj->setEnabledOperations(AllowedOperations::ALL);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ(AllowedOperations::ALL, v->allowedOperations);
  }

  void testEnableOneOperation() {
    obj->setEnabledOperations(AllowedOperations::NOTIFY);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ(AllowedOperations::NOTIFY, v->allowedOperations);
  }

  void testDisableOneOperation() {
    obj->setDisabledOperations(AllowedOperations::READ);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ(AllowedOperations::LISTEN | AllowedOperations::NOTIFY, v->allowedOperations);
  }

  void testSetDefaultWhen() {
    shared_ptr<Expr> expr = make_shared<LiteralExpr>(true);
    obj->setDefaultWhen(expr);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_TRUE(v->defaultWhen);
    ASSERT_EQ("true", v->defaultWhen->toString());
  }

  void testSetDefaultWith() {
    shared_ptr<Expr> expr = make_shared<LiteralExpr>(20.5);
    obj->setDefaultWith(expr);
    shared_ptr<Vertex> v = obj->build();
    ASSERT_TRUE(v->defaultWith);
    ASSERT_EQ("20.5", v->defaultWith->toString());
  }

  void testAddBodyEdge() {
    obj->addBodyEdge(
        make_shared<Edge>(shared_ptr<Expr>(), shared_ptr<Expr>(), shared_ptr<Expr>(), make_shared<LiteralExpr>(10)));
    shared_ptr<Vertex> v = obj->build();
    ASSERT_EQ(1, v->getEdges().size());
    ASSERT_EQ("10", v->getEdges()[0]->with->toString());
  }
};

#define VERTEX_BUILDER_TEST(METHOD)                                                                                    \
  TEST_F(VertexBuilderTest, METHOD) { this->METHOD(); }

VERTEX_BUILDER_TEST(testBuildEmpty)
VERTEX_BUILDER_TEST(testSetType)
VERTEX_BUILDER_TEST(testSetId)
VERTEX_BUILDER_TEST(testSetVisibility)
VERTEX_BUILDER_TEST(testAddNotificationparameter)
VERTEX_BUILDER_TEST(testSetStateExpr)
VERTEX_BUILDER_TEST(testsetBoundState)
VERTEX_BUILDER_TEST(testAddInterface)
VERTEX_BUILDER_TEST(testSetInitialValue)
VERTEX_BUILDER_TEST(testDisableAllOperations)
VERTEX_BUILDER_TEST(testEnableAllOperations)
VERTEX_BUILDER_TEST(testEnableOneOperation)
VERTEX_BUILDER_TEST(testDisableOneOperation)
VERTEX_BUILDER_TEST(testSetDefaultWhen)
VERTEX_BUILDER_TEST(testSetDefaultWith)
VERTEX_BUILDER_TEST(testAddBodyEdge)

} // namespace EN