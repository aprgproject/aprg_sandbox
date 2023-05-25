#include <Algorithm/String/SuffixArray/LongestRepeatedSubstring.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using LongestRepeatedSubstringForTest = LongestRepeatedSubstring<int>;
}

TEST(LongestRepeatedSubstringTest, GetLongestRepeatedSubstringWorks) {
    string stringToTest(
        "it was the best of times it was the worst of times "
        "it was the age of wisdom it was the age of foolishness "
        "it was the epoch of belief if was the epoch of incredulity "
        "it was the season of light it was the season of darkness "
        "it was the spring of hope it was the winter of despair ");

    EXPECT_EQ("st of times it was the ", LongestRepeatedSubstringForTest::getLongestRepeatedSubstring(stringToTest));
}

}  // namespace algorithm

}  // namespace alba
