#include "ParametersParser.h"
#include "Parameters.h"
#include "gtest/gtest.h"

namespace Gnocchi {
using namespace std;

class ParametersParserTest : public testing::Test {
protected:
  ParametersParser *parser;

  virtual void SetUp() override { parser = new ParametersParser(); }

  virtual void TearDown() override { delete parser; }

  void testErrorWhenEmpty() {
    const char *argv[1] = {"gnocchi"};
    ASSERT_EQ(-1, parser->parse(1, argv));
  }

  void testOnlyInput() {
    const char *argv[2] = {"gnocchi", "main.gno"};
    ASSERT_EQ(0, parser->parse(2, argv));
    const Parameters p = parser->getParameters();
    ASSERT_EQ("main.gno", p.inputFile);
  }

  void testInputOutputShort() {
    const char *argv[4] = {"gnocchi", "-o", "build", "main.gno"};
    ASSERT_EQ(0, parser->parse(4, argv));
    const Parameters p = parser->getParameters();
    ASSERT_EQ("main.gno", p.inputFile);
    ASSERT_EQ("build", p.outputPath);
  }

  void testInputOutputLong() {
    const char *argv[4] = {"gnocchi", "--output-path", "build", "main.gno"};
    ASSERT_EQ(0, parser->parse(4, argv));
    const Parameters p = parser->getParameters();
    ASSERT_EQ("main.gno", p.inputFile);
    ASSERT_EQ("build", p.outputPath);
  }

  void testMissingOutputPath() {
    const char *argv[3] = {"gnocchi", "--output-path", "main.gno"};
    ASSERT_EQ(-2, parser->parse(3, argv));
  }

  void testHelpFlagShort() {
    const char *argv[2] = {"gnocchi", "-h"};
    ASSERT_EQ(-1, parser->parse(2, argv));
  }

  void testHelpFlagLong() {
    const char *argv[2] = {"gnocchi", "--help"};
    ASSERT_EQ(-1, parser->parse(2, argv));
  }

  void testUnrecognizedOption() {
    const char *argv[4] = {"gnocchi", "--ouput-path", "build", "main.gno"};
    ASSERT_EQ(-1, parser->parse(4, argv));
  }
};

#define PARAMETERS_PARSER_TEST(METHOD)                                                                                 \
  TEST_F(ParametersParserTest, METHOD) { this->METHOD(); }

PARAMETERS_PARSER_TEST(testErrorWhenEmpty)
PARAMETERS_PARSER_TEST(testOnlyInput)
PARAMETERS_PARSER_TEST(testInputOutputShort)
PARAMETERS_PARSER_TEST(testInputOutputLong)
PARAMETERS_PARSER_TEST(testMissingOutputPath)
PARAMETERS_PARSER_TEST(testHelpFlagShort)
PARAMETERS_PARSER_TEST(testHelpFlagLong)
PARAMETERS_PARSER_TEST(testUnrecognizedOption)
} // namespace Gnocchi