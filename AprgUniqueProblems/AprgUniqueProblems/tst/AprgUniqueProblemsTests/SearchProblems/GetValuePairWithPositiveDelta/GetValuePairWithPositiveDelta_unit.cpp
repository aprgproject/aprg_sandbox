#include <AprgUniqueProblems/SearchProblems/GetValuePairWithPositiveDelta/GetValuePairWithPositiveDelta.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using QueryForTest = GetValuePairWithPositiveDelta<ValuesForTest>;
using ValuePairForTest = QueryForTest::ValuePair;
}  // namespace
TEST(GetValuePairWithPositiveDeltaTest, GetNumberOfOnesInASortedBinaryContainerWorksOnEmpty) {
    ValuesForTest sortedValues;
    QueryForTest query(sortedValues);

    ValuePairForTest pairToExpect{};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8));
}

TEST(GetValuePairWithPositiveDeltaTest, GetNumberOfOnesInASortedBinaryContainerWorksOnOneValue) {
    ValuesForTest sortedValues{5};
    QueryForTest query(sortedValues);

    ValuePairForTest pairToExpect{};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8));
}

TEST(GetValuePairWithPositiveDeltaTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesDoesNotWorkOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 10};
    QueryForTest query(sortedValues);

    ValuePairForTest pairToExpect{1, 9};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8));
}

}  // namespace algorithm
}  // namespace alba