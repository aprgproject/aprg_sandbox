#include <Algorithm/String/RegularExpression/RegularExpressionPatternMatching.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Index = unsigned int;
using PatternMatchingToTest = RegularExpressionPatternMatching<unsigned int>;
}  // namespace

TEST(RegularExpressionPatternMatchingTest, SearchWorksUsingExample1) {
    PatternMatchingToTest patternMatching("((A*B|AC)D)");

    EXPECT_TRUE(patternMatching.isAMatch("AABD"));
    EXPECT_FALSE(patternMatching.isAMatch("DDD"));
}

}  // namespace algorithm

}  // namespace alba
