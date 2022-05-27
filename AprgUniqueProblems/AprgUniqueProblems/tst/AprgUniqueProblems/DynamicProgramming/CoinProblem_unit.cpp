#include <AprgUniqueProblems/DynamicProgramming/CoinProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Coins=CoinProblem::Coins;
using CoinPermutations=CoinProblem::CoinPermutations;
using CoinCombinations=CoinProblem::CoinCombinations;
}

TEST(CoinProblemTest, GetFewestCoinsUsingRecursionWorksOnExample1)
{
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    EXPECT_EQ((Coins{200U, 200U, 100U, 20U}), coinProblem.getFewestCoinsUsingRecursion(520U));
    EXPECT_EQ((Coins{50U, 20U, 20U, 5U, 2U, 2U}), coinProblem.getFewestCoinsUsingRecursion(99U));
    EXPECT_EQ((Coins{10U, 2U, 1U}), coinProblem.getFewestCoinsUsingRecursion(13U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingRecursionWorksOnExample2)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((Coins{4U, 1U}), coinProblem.getFewestCoinsUsingRecursion(5U));
    EXPECT_EQ((Coins{4U, 3U, 3U}), coinProblem.getFewestCoinsUsingRecursion(10U));
    EXPECT_EQ((Coins{4U, 4U, 4U, 4U, 4U}), coinProblem.getFewestCoinsUsingRecursion(20U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingLoopsWorksOnExample1)
{
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    EXPECT_EQ((Coins{200U, 200U, 100U, 20U}), coinProblem.getFewestCoinsUsingLoops(520U));
    EXPECT_EQ((Coins{50U, 20U, 20U, 5U, 2U, 2U}), coinProblem.getFewestCoinsUsingLoops(99U));
    EXPECT_EQ((Coins{10U, 2U, 1U}), coinProblem.getFewestCoinsUsingLoops(13U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingLoopsWorksOnExample2)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((Coins{4U, 1U}), coinProblem.getFewestCoinsUsingLoops(5U));
    EXPECT_EQ((Coins{4U, 3U, 3U}), coinProblem.getFewestCoinsUsingLoops(10U));
    EXPECT_EQ((Coins{4U, 4U, 4U, 4U, 4U}), coinProblem.getFewestCoinsUsingLoops(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinPermutationsWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(6U, coinProblem.getNumberOfCoinPermutations(5U));
    EXPECT_EQ(49U, coinProblem.getNumberOfCoinPermutations(10U));
    EXPECT_EQ(5881U, coinProblem.getNumberOfCoinPermutations(20U));
}

TEST(CoinProblemTest, GetCoinPermutationsUsingLoopsWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((CoinPermutations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 3U, 1U}, {1U, 4U}, {3U, 1U, 1U}, {4U, 1U}}),
              coinProblem.getCoinPermutationsUsingLoops(5U));
    EXPECT_EQ((CoinPermutations{{1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 3U}, {1U, 1U, 3U, 1U}, {1U, 1U, 4U},
                                {1U, 3U, 1U, 1U}, {1U, 4U, 1U}, {3U, 1U, 1U, 1U}, {3U, 3U}, {4U, 1U, 1U}}),
              coinProblem.getCoinPermutationsUsingLoops(6U));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(2U, coinProblem.getNumberOfCoinCombinations(3U));
    EXPECT_EQ(3U, coinProblem.getNumberOfCoinCombinations(5U));
    EXPECT_EQ(5U, coinProblem.getNumberOfCoinCombinations(7U));
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinCombinations(8U));
    EXPECT_EQ(24U, coinProblem.getNumberOfCoinCombinations(20U));
}

TEST(CoinProblemTest, GetCoinCombinationsUsingRecursionWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((CoinCombinations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 4U}}),
              coinProblem.getCoinCombinationsUsingRecursion(5U));
    EXPECT_EQ((CoinCombinations{{{1U, 1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 1U, 3U}, {1U, 1U, 1U, 4U}, {1U, 3U, 3U}, {3U, 4U}}}),
              coinProblem.getCoinCombinationsUsingRecursion(7U));
}

TEST(CoinProblemTest, GetCoinCombinationsUsingLoopsWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((CoinCombinations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 4U}}),
              coinProblem.getCoinCombinationsUsingLoops(5U));
    EXPECT_EQ((CoinCombinations{{{1U, 1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 1U, 3U}, {1U, 1U, 1U, 4U}, {1U, 3U, 3U}, {3U, 4U}}}),
              coinProblem.getCoinCombinationsUsingLoops(7U));
}

}
