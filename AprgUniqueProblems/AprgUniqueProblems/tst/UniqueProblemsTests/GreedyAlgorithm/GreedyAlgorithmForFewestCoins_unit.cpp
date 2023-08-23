#include <UniqueProblems/GreedyAlgorithm/GreedyAlgorithmForFewestCoins.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(GreedyAlgorithmForFewestCoinsTest, GetTasksAsPossibleWorksOnExample1) {
    GreedyAlgorithmForFewestCoins fewestCoins({1, 2, 5, 10, 20, 50, 100});

    EXPECT_EQ(2, fewestCoins.getFewestNumberOfCoins(70));
    EXPECT_EQ(5, fewestCoins.getFewestNumberOfCoins(93));
    EXPECT_EQ(3, fewestCoins.getFewestNumberOfCoins(121));
}

}  // namespace alba
