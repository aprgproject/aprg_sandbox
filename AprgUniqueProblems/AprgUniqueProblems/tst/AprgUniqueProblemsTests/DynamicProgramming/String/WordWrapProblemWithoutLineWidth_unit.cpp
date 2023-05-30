#include <AprgUniqueProblems/DynamicProgramming/String/WordWrapProblemWithoutLineWidth.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(WordWrapProblemWithoutLineWidthTest, GetWordWrapProblemWithoutLineWidthWorksOnExample1) {
    WordWrapProblemWithoutLineWidth queryForTest({"Geeks", "for", "Geeks", "presents", "word", "wrap", "problem"});

    EXPECT_EQ(35, queryForTest.getOptimizedCostUsingNaiveRecursion());
    EXPECT_EQ(35, queryForTest.getOptimizedCostByTryingAllLengths());
}

TEST(WordWrapProblemWithoutLineWidthTest, GetWordWrapProblemWithoutLineWidthWorksOnExample2) {
    WordWrapProblemWithoutLineWidth queryForTest({"aaa", "bb", "cc", "ddddd"});

    EXPECT_EQ(8, queryForTest.getOptimizedCostUsingNaiveRecursion());
    EXPECT_EQ(8, queryForTest.getOptimizedCostByTryingAllLengths());
}

}  // namespace alba
