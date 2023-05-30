#include <AprgUniqueProblems/DynamicProgramming/SubArray/LongestEqualLengthSubArraysWithSameSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(LongestEqualLengthSubArraysWithSameSumTest, GetLongestTotalLengthOfSubArraysWorksOnEmpty) {
    LongestEqualLengthSubArraysWithSameSum queryForTest({});

    EXPECT_EQ(0, queryForTest.getLongestTotalLengthOfSubArraysUsingPartialSums());
    EXPECT_EQ(0, queryForTest.getLongestTotalLengthOfSubArraysByAccumulatingSum());
}

TEST(LongestEqualLengthSubArraysWithSameSumTest, GetLongestTotalLengthOfSubArraysWorksOnOneElement) {
    LongestEqualLengthSubArraysWithSameSum queryForTest({10});

    EXPECT_EQ(0, queryForTest.getLongestTotalLengthOfSubArraysUsingPartialSums());
    EXPECT_EQ(0, queryForTest.getLongestTotalLengthOfSubArraysByAccumulatingSum());
}

TEST(LongestEqualLengthSubArraysWithSameSumTest, GetLongestTotalLengthOfSubArraysWorksOnTwoElements) {
    LongestEqualLengthSubArraysWithSameSum queryForTest({10, 10});

    EXPECT_EQ(2, queryForTest.getLongestTotalLengthOfSubArraysUsingPartialSums());
    EXPECT_EQ(2, queryForTest.getLongestTotalLengthOfSubArraysByAccumulatingSum());
}

TEST(LongestEqualLengthSubArraysWithSameSumTest, GetLongestTotalLengthOfSubArraysWorksOnExample1) {
    LongestEqualLengthSubArraysWithSameSum queryForTest({1, 2, 3, 1, 2, 3});

    EXPECT_EQ(6, queryForTest.getLongestTotalLengthOfSubArraysUsingPartialSums());
    EXPECT_EQ(6, queryForTest.getLongestTotalLengthOfSubArraysByAccumulatingSum());
}

TEST(LongestEqualLengthSubArraysWithSameSumTest, GetLongestTotalLengthOfSubArraysWorksOnExample2) {
    LongestEqualLengthSubArraysWithSameSum queryForTest({1, 5, 3, 8, 0, 2, 3});

    EXPECT_EQ(4, queryForTest.getLongestTotalLengthOfSubArraysUsingPartialSums());
    EXPECT_EQ(4, queryForTest.getLongestTotalLengthOfSubArraysByAccumulatingSum());
}

}  // namespace alba
