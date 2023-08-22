#include <UniqueProblems/DynamicProgramming/Subsequence/LongestBitonicSubsequence.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace {
using Values = LongestBitonicSubsequence::Values;
}

TEST(LongestBitonicSubsequenceTest, GetLongestLengthWorksOnExample1) {
    LongestBitonicSubsequence queryForTest({6, 2, 5, 1, 7, 4, 8, 3});

    EXPECT_EQ(5, queryForTest.getLongestLength());
}

TEST(LongestBitonicSubsequenceTest, GetLongestLengthWorksOnExample2) {
    LongestBitonicSubsequence queryForTest({12, 11, 40, 5, 3, 1});

    EXPECT_EQ(5, queryForTest.getLongestLength());
}

TEST(LongestBitonicSubsequenceTest, GetLongestSubsequenceWorksOnExample1) {
    LongestBitonicSubsequence queryForTest({6, 2, 5, 1, 7, 4, 8, 3});

    EXPECT_EQ((Values{2, 5, 7, 4, 3}), queryForTest.getLongestSubsequence());
}

TEST(LongestBitonicSubsequenceTest, GetLongestSubsequenceWorksOnExample2) {
    LongestBitonicSubsequence queryForTest({12, 11, 40, 5, 3, 1});

    EXPECT_EQ((Values{12, 11, 5, 3, 1}), queryForTest.getLongestSubsequence());
}

}  // namespace alba
