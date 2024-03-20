#include "gtest/gtest.h"
#include "scanner.h"

#include <iostream>

namespace Gnocchi
{

  

    class ScannerTest : public testing::Test
    {
    protected:
        Scanner* obj;


        virtual void SetUp() override
        {
          obj = new Scanner(nullptr);
        }

        virtual void TearDown() override
        {
            delete obj;
        }

        void testCreateScanner() {
          ASSERT_NE(nullptr, obj);
        }

        void testThrowInvalidOperatorException()
        {
            try
            {
                Expression::throwInvalidOperatorException("test", Operator::EQ);
            }
            catch (ModularNOPGraph::NOPCompileException e)
            {
                ASSERT_STREQ("NOPL compilation exception: operator of type == invalid for expression node of type test", e.what());
            }
        }

        void testGetOperatorStringReturnsAppropriateString()
        {
            typedef struct
            {
                Operator op;
                std::string expected;
            } testPair;

            std::vector<testPair> tests = {
                {Operator::EQ, "=="},
                {Operator::NE, "!="},
                {Operator::LT, "<"},
                {Operator::GT, ">"},
                {Operator::LE, "<="},
                {Operator::GE, ">="},
                {Operator::SUM, "+"},
                {Operator::SUB, "-"},
                {Operator::MULT, "*"},
                {Operator::DIV, "/"},
                {Operator::CALL, ""},
                {Operator::NOT, "!"},
            };

            for (testPair test : tests)
            {
                ASSERT_EQ(test.expected, getOperatorString(test.op));
            }
        }

        void testGetOperatorStringThrowsOnInvalidOperator()
        {
            try
            {
                std::string str = getOperatorString((Operator)-1);
                ASSERT_TRUE(false);
            }
            catch (ModularNOPGraph::NOPCompileException e)
            {
                ASSERT_STREQ("NOPL compilation exception: value -1 not valid operator!", e.what());
            }
        }

        void testCreateLiteral()
        {
            ASSERT_NE(nullptr, literal);
        }

        void testCreateReference()
        {
            ASSERT_NE(nullptr, reference);
        }

        void testCreateUnary()
        {
            ASSERT_NE(nullptr, unary);
        }

        void testUnaryConstructorThrowsOnInvalidOperator()
        {
            try
            {
                UnaryExpression *b = new UnaryExpression(Operator::EQ, *unary);
                ASSERT_TRUE(false);
            }
            catch (ModularNOPGraph::NOPCompileException e)
            {
                ASSERT_STREQ("NOPL compilation exception: operator == invalid for unary expression", e.what());
            }
        }

        void notValidOperatorForUnaryReturnsTrueForInvalid()
        {
            std::vector<Operator> operators = {
                Operator::EQ,
                Operator::NE,
                Operator::LT,
                Operator::GT,
                Operator::LE,
                Operator::GE,
                Operator::SUM,
                Operator::MULT,
                Operator::DIV,
                Operator::CALL,
            };

            for (Operator op : operators)
            {
                ASSERT_TRUE(unary->notValidOperatorForUnary(op));
            }
        }

        void notValidOperatorForUnaryReturnsFalseForValid()
        {
            ASSERT_FALSE(unary->notValidOperatorForUnary(Operator::NOT));
            ASSERT_FALSE(unary->notValidOperatorForUnary(Operator::SUB));
        }

        void testCreateBinary()
        {
            ASSERT_NE(nullptr, binary);
            binary->notValidOperatorForBinary(Operator::LT);
        }

        void testBinaryConstructorThrowsOnInvalidOperator()
        {
            try
            {
                BinaryExpression *b = new BinaryExpression(*unary, Operator::NOT, *unary);
                ASSERT_TRUE(false);
            }
            catch (ModularNOPGraph::NOPCompileException e)
            {
                ASSERT_STREQ("NOPL compilation exception: operator ! invalid for binary expression", e.what());
            }
        }

        void notValidOperatorForBinaryReturnsTrueForInvalid()
        {
            ASSERT_TRUE(binary->notValidOperatorForBinary(Operator::NOT));
        }

        void notValidOperatorForBinaryReturnsFalseForValid()
        {
            std::vector<Operator> operators = {
                Operator::EQ,
                Operator::NE,
                Operator::LT,
                Operator::GT,
                Operator::LE,
                Operator::GE,
                Operator::SUM,
                Operator::SUB,
                Operator::MULT,
                Operator::DIV,
                Operator::CALL,
            };

            for (Operator op : operators)
            {
                ASSERT_FALSE(binary->notValidOperatorForBinary(op));
            }
        }

        void testCreateArray()
        {
            ASSERT_NE(nullptr, array);
        }

        void testToStringLiteral()
        {
            ASSERT_EQ("10", literal->toString());
        }

        void testToStringReference()
        {
            ASSERT_EQ("vertex", reference->toString());
        }

        void testToStringUnary()
        {
            ASSERT_EQ("!vertex", unary->toString());
        }

        void testToStringBinary()
        {
            ASSERT_EQ("10 == !vertex", binary->toString());
        }

        void testToStringArray()
        {
            ASSERT_EQ("(10, vertex, !vertex, 10 == !vertex)", array->toString());
        }

        void testGetArrayExpressionBegin()
        {
            const ArrayExpression::iterator begin = array->begin();
            ASSERT_EQ(literal, &(*begin));
        }

        void testGetArrayExpressionEnd()
        {
            ASSERT_NE(array->begin(), array->end());
        }

        void testForInArrayExpression()
        {
            for (Expression &expr : *array)
            {
                expr.toString();
            }
        }

        void testWhileLoopWithIterators()
        {
            ArrayExpression::iterator iterator = array->begin();
            while (iterator != array->end())
            {
                (*iterator++).toString();
            }
        }
    };

    TEST_F(testENGraphExpression, testGetOperatorStringReturnsAppropriateString)
    {
        this->testGetOperatorStringReturnsAppropriateString();
    }

    TEST_F(testENGraphExpression, testGetOperatorStringThrowsOnInvalidOperator)
    {
        this->testGetOperatorStringThrowsOnInvalidOperator();
    }

    TEST_F(testENGraphExpression, testCreateLiteral)
    {
        this->testCreateLiteral();
    }

    TEST_F(testENGraphExpression, testCreateReference)
    {
        this->testCreateReference();
    }

    TEST_F(testENGraphExpression, testCreateUnary)
    {
        this->testCreateUnary();
    }

    TEST_F(testENGraphExpression, testUnaryConstructorThrowsOnInvalidOperator)
    {
        this->testUnaryConstructorThrowsOnInvalidOperator();
    }

    TEST_F(testENGraphExpression, notValidOperatorForUnaryReturnsTrueForInvalid)
    {
        this->notValidOperatorForUnaryReturnsTrueForInvalid();
    }

    TEST_F(testENGraphExpression, notValidOperatorForUnaryReturnsFalseForValid)
    {
        this->notValidOperatorForUnaryReturnsFalseForValid();
    }

    TEST_F(testENGraphExpression, testCreateBinary)
    {
        this->testCreateBinary();
    }

    TEST_F(testENGraphExpression, testBinaryConstructorThrowsOnInvalidOperator)
    {
        this->testBinaryConstructorThrowsOnInvalidOperator();
    }

    TEST_F(testENGraphExpression, notValidOperatorForBinaryReturnsTrueForInvalid)
    {
        this->notValidOperatorForBinaryReturnsTrueForInvalid();
    }

    TEST_F(testENGraphExpression, notValidOperatorForBinaryReturnsFalseForValid)
    {
        this->notValidOperatorForBinaryReturnsFalseForValid();
    }

    TEST_F(testENGraphExpression, testCreateArray)
    {
        this->testCreateArray();
    }

    TEST_F(testENGraphExpression, testToStringLiteral)
    {
        this->testToStringLiteral();
    }

    TEST_F(testENGraphExpression, testToStringReference)
    {
        this->testToStringReference();
    }

    TEST_F(testENGraphExpression, testToStringUnary)
    {
        this->testToStringUnary();
    }

    TEST_F(testENGraphExpression, testToStringBinary)
    {
        this->testToStringBinary();
    }

    TEST_F(testENGraphExpression, testToStringArray)
    {
        this->testToStringArray();
    }

    TEST_F(testENGraphExpression, testGetArrayExpressionBegin)
    {
        this->testGetArrayExpressionBegin();
    }

    TEST_F(testENGraphExpression, testGetArrayExpressionEnd)
    {
        this->testGetArrayExpressionEnd();
    }

    TEST_F(testENGraphExpression, testForInArrayExpression)
    {
        this->testForInArrayExpression();
    }

    TEST_F(testENGraphExpression, testWhileLoopWithIterators)
    {
        this->testWhileLoopWithIterators();
    }

}