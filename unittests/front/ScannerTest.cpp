#include "gtest/gtest.h"
#include "scanner.h"
#include <iostream>

namespace Gnocchi
{

  class ScannerTest : public testing::Test
  {
  protected:
    Scanner *obj;
    LocationProvider provider{"mock.gno"};

    virtual void SetUp() override
    {
      obj = new Scanner(provider);
    }

    virtual void TearDown() override
    {
      provider.reset();
      delete obj;
    }

    void testCreateScanner()
    {
      ASSERT_NE(nullptr, obj);
    }

    void testSwitchStream() {
      std::stringstream stream;
      stream << "";
      obj->switch_streams(&stream, nullptr);
      ASSERT_EQ(0, obj->get_next_token().kind());

      stream << "+";
      ASSERT_NE(0, obj->get_next_token().kind());
    }
  };

  TEST_F(ScannerTest, testCreateScanner)
  {
    this->testCreateScanner();
  }

  TEST_F(ScannerTest, testSwitchStream)
  {
    this->testSwitchStream();
  }

}