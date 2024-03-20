#include "gtest/gtest.h"
#include "LocationProvider.h"

#include <iostream>

namespace Gnocchi
{

  class LocationProviderTest : public testing::Test
  {
  protected:
    const std::string defaultFilename{"mock.gno"};
    LocationProvider provider{defaultFilename};

    virtual void SetUp() override
    {
      provider.setFileName(defaultFilename);
    }

    virtual void TearDown() override
    {
      provider.reset();
    }

    void testFilename()
    {
      ASSERT_EQ("mock.gno", *provider.getFileName());
      std::string otherName{"f2.gno"};
      provider.setFileName(otherName);
      ASSERT_EQ("f2.gno", *provider.getFileName());
    }

    void testLocationCol()
    {
      ASSERT_EQ(0, provider.getLocationCol());
      provider.increaseLocationCol(10);
      ASSERT_EQ(10, provider.getLocationCol());
      provider.increaseLocationCol(24);
      ASSERT_EQ(34, provider.getLocationCol());
      provider.reset();
      ASSERT_EQ(0, provider.getLocationCol());
    }
  };

  TEST_F(LocationProviderTest, testFilename)
  {
    this->testFilename();
  }

  TEST_F(LocationProviderTest, testLocationCol)
  {
    this->testLocationCol();
  }
}