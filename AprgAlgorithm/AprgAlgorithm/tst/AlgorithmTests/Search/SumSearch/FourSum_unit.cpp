#include <Algorithm/Search/SumSearch/FourSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<unsigned int>;
using SumSearch = FourSum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using FourValuesForTest = SumSearch::FourValues;
}  // namespace

TEST(FourSumTest, GetPossibleDuplicatedFourValuesWithSumWorksOnExample1) {
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    FourValuesForTest fourValuesToVerify(search.getPossibleDuplicatedFourValuesWithSum(18U));

    FourValuesForTest fourValuesToExpect{1U, 1U, 7U, 9U};
    EXPECT_EQ(fourValuesToExpect, fourValuesToVerify);
}

}  // namespace algorithm

}  // namespace alba
