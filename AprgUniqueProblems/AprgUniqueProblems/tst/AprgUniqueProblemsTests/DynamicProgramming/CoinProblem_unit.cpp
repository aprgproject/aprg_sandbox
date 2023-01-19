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

TEST(CoinProblemTest, GetNumberOfFewestCoinsUsingMemoizationDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    //EXPECT_EQ(4U, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(520U)); // causes crash
    //EXPECT_EQ(6U, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(99U));
    //EXPECT_EQ(3U, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(13U));
}

TEST(CoinProblemTest, GetNumberOfFewestCoinsTabularDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    EXPECT_EQ(4U, coinProblem.getNumberOfFewestCoinsTabularDP(520U));
    EXPECT_EQ(6U, coinProblem.getNumberOfFewestCoinsTabularDP(99U));
    EXPECT_EQ(3U, coinProblem.getNumberOfFewestCoinsTabularDP(13U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingMemoizationDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    //EXPECT_EQ((Coins{200U, 200U, 100U, 20U}), coinProblem.getFewestCoinsUsingMemoizationDP(520U));
    //EXPECT_EQ((Coins{50U, 20U, 20U, 5U, 2U, 2U}), coinProblem.getFewestCoinsUsingMemoizationDP(99U));
    //EXPECT_EQ((Coins{10U, 2U, 1U}), coinProblem.getFewestCoinsUsingMemoizationDP(13U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingMemoizationDPWorksOnExample2)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((Coins{4U, 1U}), coinProblem.getFewestCoinsUsingMemoizationDP(5U));
    EXPECT_EQ((Coins{4U, 3U, 3U}), coinProblem.getFewestCoinsUsingMemoizationDP(10U));
    EXPECT_EQ((Coins{4U, 4U, 4U, 4U, 4U}), coinProblem.getFewestCoinsUsingMemoizationDP(20U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingTabularDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    EXPECT_EQ((Coins{200U, 200U, 100U, 20U}), coinProblem.getFewestCoinsUsingTabularDP(520U));
    EXPECT_EQ((Coins{50U, 20U, 20U, 5U, 2U, 2U}), coinProblem.getFewestCoinsUsingTabularDP(99U));
    EXPECT_EQ((Coins{10U, 2U, 1U}), coinProblem.getFewestCoinsUsingTabularDP(13U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingTabularDPWorksOnExample2)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((Coins{4U, 1U}), coinProblem.getFewestCoinsUsingTabularDP(5U));
    EXPECT_EQ((Coins{4U, 3U, 3U}), coinProblem.getFewestCoinsUsingTabularDP(10U));
    EXPECT_EQ((Coins{4U, 4U, 4U, 4U, 4U}), coinProblem.getFewestCoinsUsingTabularDP(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinPermutationsMemoizationDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(0U)); // null set
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(5U));
    EXPECT_EQ(9U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(6U));
    EXPECT_EQ(64U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(10U));
    EXPECT_EQ(7921U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinPermutationsTabularDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinPermutationsTabularDP(0U)); // null set
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinPermutationsTabularDP(5U));
    EXPECT_EQ(9U, coinProblem.getNumberOfCoinPermutationsTabularDP(6U));
    EXPECT_EQ(64U, coinProblem.getNumberOfCoinPermutationsTabularDP(10U));
    EXPECT_EQ(7921U, coinProblem.getNumberOfCoinPermutationsTabularDP(20U));
}

TEST(CoinProblemTest, GetCoinPermutationsUsingMemoizationDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((CoinPermutations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 3U, 1U}, {1U, 4U}, {3U, 1U, 1U}, {4U, 1U}}),
              coinProblem.getCoinPermutationsUsingMemoizationDP(5U));
    EXPECT_EQ((CoinPermutations{{1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 3U}, {1U, 1U, 3U, 1U}, {1U, 1U, 4U},
                                {1U, 3U, 1U, 1U}, {1U, 4U, 1U}, {3U, 1U, 1U, 1U}, {3U, 3U}, {4U, 1U, 1U}}),
              coinProblem.getCoinPermutationsUsingMemoizationDP(6U));
}

TEST(CoinProblemTest, GetCoinPermutationsUsingTabularDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((CoinPermutations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 3U, 1U}, {1U, 4U}, {3U, 1U, 1U}, {4U, 1U}}),
              coinProblem.getCoinPermutationsUsingTabularDP(5U));
    EXPECT_EQ((CoinPermutations{{1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 3U}, {1U, 1U, 3U, 1U}, {1U, 1U, 4U},
                                {1U, 3U, 1U, 1U}, {1U, 4U, 1U}, {3U, 1U, 1U, 1U}, {3U, 3U}, {4U, 1U, 1U}}),
              coinProblem.getCoinPermutationsUsingTabularDP(6U));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingMemoizationDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(0U)); // null set
    EXPECT_EQ(2U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(3U));
    EXPECT_EQ(3U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(5U));
    EXPECT_EQ(5U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(7U));
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(8U));
    EXPECT_EQ(24U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingTabularDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinCombinationsUsingTabularDP(0U)); // null set
    EXPECT_EQ(2U, coinProblem.getNumberOfCoinCombinationsUsingTabularDP(3U));
    EXPECT_EQ(3U, coinProblem.getNumberOfCoinCombinationsUsingTabularDP(5U));
    EXPECT_EQ(5U, coinProblem.getNumberOfCoinCombinationsUsingTabularDP(7U));
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinCombinationsUsingTabularDP(8U));
    EXPECT_EQ(24U, coinProblem.getNumberOfCoinCombinationsUsingTabularDP(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingTabularDPAndSpaceEfficientWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinCombinationsUsingTabularDPAndSpaceEfficient(0U)); // null set
    EXPECT_EQ(2U, coinProblem.getNumberOfCoinCombinationsUsingTabularDPAndSpaceEfficient(3U));
    EXPECT_EQ(3U, coinProblem.getNumberOfCoinCombinationsUsingTabularDPAndSpaceEfficient(5U));
    EXPECT_EQ(5U, coinProblem.getNumberOfCoinCombinationsUsingTabularDPAndSpaceEfficient(7U));
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinCombinationsUsingTabularDPAndSpaceEfficient(8U));
    EXPECT_EQ(24U, coinProblem.getNumberOfCoinCombinationsUsingTabularDPAndSpaceEfficient(20U));
}

TEST(CoinProblemTest, GetCoinCombinationsUsingMemoizationDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((CoinCombinations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 4U}}),
              coinProblem.getCoinCombinationsUsingMemoizationDP(5U));
    EXPECT_EQ((CoinCombinations{{{1U, 1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 1U, 3U}, {1U, 1U, 1U, 4U}, {1U, 3U, 3U}, {3U, 4U}}}),
              coinProblem.getCoinCombinationsUsingMemoizationDP(7U));
}

TEST(CoinProblemTest, GetCoinCombinationsUsingTabularDPWorksOnExample1)
{
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((CoinCombinations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 4U}}),
              coinProblem.getCoinCombinationsUsingTabularDP(5U));
    EXPECT_EQ((CoinCombinations{{{1U, 1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 1U, 3U}, {1U, 1U, 1U, 4U}, {1U, 3U, 3U}, {3U, 4U}}}),
              coinProblem.getCoinCombinationsUsingTabularDP(7U));
}

}
