#include <Algorithm/Search/SumSearch/ThreeSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SumSearch = ThreeSum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using ThreeValuesForTest = SumSearch::ThreeValues;
}  // namespace

TEST(ThreeSumTest, GetNonDuplicateThreeValuesWithSumWorksOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 10};
    SumSearch search(sortedValues);

    ThreeValuesForTest threeValuesToVerify(search.getNonDuplicateThreeValuesWithSum(18));

    ThreeValuesForTest threeValuesToExpect{1, 7, 10};
    EXPECT_EQ(threeValuesToExpect, threeValuesToVerify);
}

TEST(ThreeSumTest, GetPossibleDuplicatedThreeValuesWithSumWorksOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 10};
    SumSearch search(sortedValues);

    ThreeValuesForTest threeValuesToVerify(search.getPossibleDuplicatedThreeValuesWithSum(30));

    ThreeValuesForTest threeValuesToExpect{10, 10, 10};
    EXPECT_EQ(threeValuesToExpect, threeValuesToVerify);
}

}  // namespace algorithm

}  // namespace alba
