#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/LongestBitonicSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Values = LongestBitonicSubsequence::Values;
}

TEST(LongestBitonicSubsequenceTest, GetLongestLengthWorksOnExample1) {
    LongestBitonicSubsequence queryForTest({6U, 2U, 5U, 1U, 7U, 4U, 8U, 3U});

    EXPECT_EQ(5U, queryForTest.getLongestLength());
}

TEST(LongestBitonicSubsequenceTest, GetLongestLengthWorksOnExample2) {
    LongestBitonicSubsequence queryForTest({12U, 11U, 40U, 5U, 3U, 1U});

    EXPECT_EQ(5U, queryForTest.getLongestLength());
}

TEST(LongestBitonicSubsequenceTest, GetLongestSubsequenceWorksOnExample1) {
    LongestBitonicSubsequence queryForTest({6U, 2U, 5U, 1U, 7U, 4U, 8U, 3U});

    EXPECT_EQ((Values{2U, 5U, 7U, 4U, 3U}), queryForTest.getLongestSubsequence());
}

TEST(LongestBitonicSubsequenceTest, GetLongestSubsequenceWorksOnExample2) {
    LongestBitonicSubsequence queryForTest({12U, 11U, 40U, 5U, 3U, 1U});

    EXPECT_EQ((Values{12U, 11U, 5U, 3U, 1U}), queryForTest.getLongestSubsequence());
}

}  // namespace alba
