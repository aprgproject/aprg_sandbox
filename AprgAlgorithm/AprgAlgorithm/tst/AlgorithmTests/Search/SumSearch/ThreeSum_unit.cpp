#include <Algorithm/Search/SumSearch/ThreeSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SumSearch = ThreeSum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using ThreeValuesForTest = SumSearch::ThreeValues;
}

TEST(ThreeSumTest, GetThreeValuesWithSumWorksOnExample1)
{
    SumSearch search;
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};

    ThreeValuesForTest threeValuesToVerify(search.getThreeValuesWithSum(18U, sortedValues));

    ThreeValuesForTest threeValuesToExpect{1U, 7U, 10U};
    EXPECT_EQ(threeValuesToExpect, threeValuesToVerify);
}

}

}
