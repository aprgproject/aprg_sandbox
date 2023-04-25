#include <AprgUniqueProblems/DynamicProgramming/String/WordWrapProblemWithLineWidth.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(WordWrapProblemWithLineWidthTest, GetWordWrapProblemWithLineWidthWorksOnExample1) {
    WordWrapProblemWithLineWidth queryForTest(15U, {"Geeks", "for", "Geeks", "presents", "word", "wrap", "problem"});

    EXPECT_EQ(35U, queryForTest.getOptimizedCostUsingNaiveRecursion());
    EXPECT_EQ(35U, queryForTest.getOptimizedCostByTryingAllLengths());
    EXPECT_EQ(35U, queryForTest.getOptimizedCostByCheckingFirstAndLastWords());
}

TEST(WordWrapProblemWithLineWidthTest, GetWordWrapProblemWithLineWidthWorksOnExample2) {
    WordWrapProblemWithLineWidth queryForTest(6U, {"aaa", "bb", "cc", "ddddd"});

    EXPECT_EQ(29U, queryForTest.getOptimizedCostUsingNaiveRecursion());
    EXPECT_EQ(29U, queryForTest.getOptimizedCostByTryingAllLengths());
    EXPECT_EQ(29U, queryForTest.getOptimizedCostByCheckingFirstAndLastWords());
}

}  // namespace alba
