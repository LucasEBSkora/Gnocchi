#include "gtest/gtest.h"
#include "VertexBuilder.h"
#include "LiteralExpr.h"

namespace Gnocchi
{

  class VertexBuilderTest : public testing::Test
  {
  public:
    VertexBuilder *obj;

    virtual void SetUp() override
    {
      obj = new VertexBuilder();
    }

    virtual void TearDown() override
    {
      delete obj;
    }

    void testBuildEmpty()
    {
      std::shared_ptr<Vertex> v = obj->build();
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

    void testSetType()
    {
      std::weak_ptr<Type> t = PrimitiveType::getPrimitiveType(PrimitiveType::BOOL);
      obj->setType(t);
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_FALSE(v->type.expired());
      ASSERT_EQ("bool", v->type.lock()->toString());
    }

    void testSetId()
    {
      obj->setId("10");
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_EQ("10", v->id);
    }

    void testSetVisibility()
    {
      obj->setVisibility(Visibility::PRIVATE);
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_EQ(Visibility::PRIVATE, v->visibility);
    }

    void testAddNotificationparameter()
    {
      obj->addNotificationParameter({"first", PrimitiveType::getPrimitiveType(PrimitiveType::INT8)});
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_EQ(1, v->notificationParameters.size());
      ASSERT_EQ("first", v->notificationParameters[0].name);
    }

    void testSetStateExpr()
    {
      std::shared_ptr<Expr> expr = std::make_shared<LiteralExpr>(20);
      obj->setStateExpr(expr);
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_TRUE(v->stateExpr);
      ASSERT_EQ("20", v->stateExpr->toString());
    }

    void testsetBoundState()
    {
      obj->setBoundState(true);
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_TRUE(v->boundState);
    }

    void testAddInterface()
    {
      obj->addInterface("Rule");
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_EQ(1, v->interfaces.size());
      ASSERT_EQ("Rule", v->interfaces[0]);
    }

    void testSetInitialValue()
    {
      std::shared_ptr<Expr> expr = std::make_shared<LiteralExpr>("potato");
      obj->setInitialValue(expr);
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_TRUE(v->initialValue);
      ASSERT_EQ("potato", v->initialValue->toString());
    }

    void testDisableAllOperations()
    {
      obj->disableAllOperations();
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_EQ(AllowedOperations::NONE, v->allowedOperations);
    }

    void testEnableAllOperations()
    {
      obj->enableAllOperations();
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_EQ(AllowedOperations::ALL, v->allowedOperations);
    }

    void testToggleOperationEnabled()
    {
      obj->enableAllOperations().toggleOperationEnabled(AllowedOperations::READ);
      ASSERT_EQ(int(AllowedOperations::WRITE) | int(AllowedOperations::NOTIFY), obj->build()->allowedOperations);

      obj->disableAllOperations().toggleOperationEnabled(AllowedOperations::NOTIFY);
      ASSERT_EQ(AllowedOperations::NOTIFY, obj->build()->allowedOperations);
    }

    void testSetDefaultWhen()
    {
      std::shared_ptr<Expr> expr = std::make_shared<LiteralExpr>(true);
      obj->setDefaultWhen(expr);
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_TRUE(v->defaultWhen);
      ASSERT_EQ("true", v->defaultWhen->toString());
    }

    void testSetDefaultWith()
    {
      std::shared_ptr<Expr> expr = std::make_shared<LiteralExpr>(20.5);
      obj->setDefaultWith(expr);
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_TRUE(v->defaultWith);
      ASSERT_EQ("20.5", v->defaultWith->toString());
    }

    void testAddBodyEdge()
    {
      obj->addBodyEdge(std::make_shared<Edge>());
      std::shared_ptr<Vertex> v = obj->build();
      ASSERT_EQ(1, v->getEdges().size());
    }
  };

#define VERTEX_BUILDER_TEST(METHOD) \
  TEST_F(VertexBuilderTest, METHOD) \
  {                                 \
    this->METHOD();                 \
  }

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
  VERTEX_BUILDER_TEST(testToggleOperationEnabled)
  VERTEX_BUILDER_TEST(testSetDefaultWhen)
  VERTEX_BUILDER_TEST(testSetDefaultWith)
  VERTEX_BUILDER_TEST(testAddBodyEdge)

}