#include <AprgUniqueProblems/GreedyAlgorithm/GreedyAlgorithmForFewestCoins.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(GreedyAlgorithmForFewestCoinsTest, GetTasksAsPossibleWorksOnExample1) {
    GreedyAlgorithmForFewestCoins fewestCoins({1U, 2U, 5U, 10U, 20U, 50U, 100U});

    EXPECT_EQ(2U, fewestCoins.getFewestNumberOfCoins(70U));
    EXPECT_EQ(5U, fewestCoins.getFewestNumberOfCoins(93U));
    EXPECT_EQ(3U, fewestCoins.getFewestNumberOfCoins(121U));
}

}  // namespace alba
