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

TEST(ThreeSumTest, GetNonDuplicateThreeValuesWithSumWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ThreeValuesForTest threeValuesToVerify(search.getNonDuplicateThreeValuesWithSum(18U));

    ThreeValuesForTest threeValuesToExpect{1U, 7U, 10U};
    EXPECT_EQ(threeValuesToExpect, threeValuesToVerify);
}

TEST(ThreeSumTest, GetPossibleDuplicatesThreeValuesWithSumWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ThreeValuesForTest threeValuesToVerify(search.getPossibleDuplicatesThreeValuesWithSum(30U));

    ThreeValuesForTest threeValuesToExpect{10U, 10U, 10U};
    EXPECT_EQ(threeValuesToExpect, threeValuesToVerify);
}

}

}
