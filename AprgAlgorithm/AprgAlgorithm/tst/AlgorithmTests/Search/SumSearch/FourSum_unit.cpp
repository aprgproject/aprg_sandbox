#include <Algorithm/Search/SumSearch/FourSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SumSearch = FourSum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using FourValuesForTest = SumSearch::FourValues;
}  // namespace

TEST(FourSumTest, GetPossibleDuplicatedFourValuesWithSumWorksOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 10};
    SumSearch search(sortedValues);

    FourValuesForTest fourValuesToVerify(search.getPossibleDuplicatedFourValuesWithSum(18));

    FourValuesForTest fourValuesToExpect{1, 1, 7, 9};
    EXPECT_EQ(fourValuesToExpect, fourValuesToVerify);
}

}  // namespace algorithm

}  // namespace alba
