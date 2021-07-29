#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace MathSeries
{

TEST(UtilitiesTest, GetSumUsingFirstAndLastTermWorks)
{
    EXPECT_DOUBLE_EQ(60, getSumUsingFirstAndLastTerm(12, 18, 4));
}

}

}

