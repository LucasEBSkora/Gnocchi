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
  };

  TEST_F(ScannerTest, testCreateScanner)
  {
    this->testCreateScanner();
  }

}