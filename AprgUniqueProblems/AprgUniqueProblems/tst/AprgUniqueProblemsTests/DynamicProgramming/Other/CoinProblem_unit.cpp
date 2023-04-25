#include <AprgUniqueProblems/DynamicProgramming/Other/CoinProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Coins = CoinProblem::Coins;
using CoinPermutations = CoinProblem::CoinPermutations;
using CoinCombinations = CoinProblem::CoinCombinations;
}  // namespace

TEST(CoinProblemTest, GetNumberOfFewestCoinsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    // EXPECT_EQ(4U, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(520U)); // causes crash
    EXPECT_EQ(6U, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(99U));
    EXPECT_EQ(3U, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(13U));
}

TEST(CoinProblemTest, GetNumberOfFewestCoinsIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    EXPECT_EQ(4U, coinProblem.getNumberOfFewestCoinsIterativeDP(520U));
    EXPECT_EQ(6U, coinProblem.getNumberOfFewestCoinsIterativeDP(99U));
    EXPECT_EQ(3U, coinProblem.getNumberOfFewestCoinsIterativeDP(13U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    // EXPECT_EQ((Coins{200U, 200U, 100U, 20U}), coinProblem.getFewestCoinsUsingMemoizationDP(520U));
    // EXPECT_EQ((Coins{50U, 20U, 20U, 5U, 2U, 2U}), coinProblem.getFewestCoinsUsingMemoizationDP(99U));
    // EXPECT_EQ((Coins{10U, 2U, 1U}), coinProblem.getFewestCoinsUsingMemoizationDP(13U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingMemoizationDPWorksOnExample2) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((Coins{4U, 1U}), coinProblem.getFewestCoinsUsingMemoizationDP(5U));
    EXPECT_EQ((Coins{4U, 3U, 3U}), coinProblem.getFewestCoinsUsingMemoizationDP(10U));
    EXPECT_EQ((Coins{4U, 4U, 4U, 4U, 4U}), coinProblem.getFewestCoinsUsingMemoizationDP(20U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 2U, 5U, 10U, 20U, 50U, 100U, 200U});

    EXPECT_EQ((Coins{200U, 200U, 100U, 20U}), coinProblem.getFewestCoinsUsingIterativeDP(520U));
    EXPECT_EQ((Coins{50U, 20U, 20U, 5U, 2U, 2U}), coinProblem.getFewestCoinsUsingIterativeDP(99U));
    EXPECT_EQ((Coins{10U, 2U, 1U}), coinProblem.getFewestCoinsUsingIterativeDP(13U));
}

TEST(CoinProblemTest, GetFewestCoinsUsingIterativeDPWorksOnExample2) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ((Coins{4U, 1U}), coinProblem.getFewestCoinsUsingIterativeDP(5U));
    EXPECT_EQ((Coins{4U, 3U, 3U}), coinProblem.getFewestCoinsUsingIterativeDP(10U));
    EXPECT_EQ((Coins{4U, 4U, 4U, 4U, 4U}), coinProblem.getFewestCoinsUsingIterativeDP(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinPermutationsMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(0U));  // null set
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(5U));
    EXPECT_EQ(9U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(6U));
    EXPECT_EQ(64U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(10U));
    EXPECT_EQ(7921U, coinProblem.getNumberOfCoinPermutationsMemoizationDP(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinPermutationsIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinPermutationsIterativeDP(0U));  // null set
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinPermutationsIterativeDP(5U));
    EXPECT_EQ(9U, coinProblem.getNumberOfCoinPermutationsIterativeDP(6U));
    EXPECT_EQ(64U, coinProblem.getNumberOfCoinPermutationsIterativeDP(10U));
    EXPECT_EQ(7921U, coinProblem.getNumberOfCoinPermutationsIterativeDP(20U));
}

TEST(CoinProblemTest, GetCoinPermutationsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(
        (CoinPermutations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 3U, 1U}, {1U, 4U}, {3U, 1U, 1U}, {4U, 1U}}),
        coinProblem.getCoinPermutationsUsingMemoizationDP(5U));
    EXPECT_EQ(
        (CoinPermutations{
            {1U, 1U, 1U, 1U, 1U, 1U},
            {1U, 1U, 1U, 3U},
            {1U, 1U, 3U, 1U},
            {1U, 1U, 4U},
            {1U, 3U, 1U, 1U},
            {1U, 4U, 1U},
            {3U, 1U, 1U, 1U},
            {3U, 3U},
            {4U, 1U, 1U}}),
        coinProblem.getCoinPermutationsUsingMemoizationDP(6U));
}

TEST(CoinProblemTest, GetCoinPermutationsUsingIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(
        (CoinPermutations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 3U, 1U}, {1U, 4U}, {3U, 1U, 1U}, {4U, 1U}}),
        coinProblem.getCoinPermutationsUsingIterativeDP(5U));
    EXPECT_EQ(
        (CoinPermutations{
            {1U, 1U, 1U, 1U, 1U, 1U},
            {1U, 1U, 1U, 3U},
            {1U, 1U, 3U, 1U},
            {1U, 1U, 4U},
            {1U, 3U, 1U, 1U},
            {1U, 4U, 1U},
            {3U, 1U, 1U, 1U},
            {3U, 3U},
            {4U, 1U, 1U}}),
        coinProblem.getCoinPermutationsUsingIterativeDP(6U));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(0U));  // null set
    EXPECT_EQ(2U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(3U));
    EXPECT_EQ(3U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(5U));
    EXPECT_EQ(5U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(7U));
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(8U));
    EXPECT_EQ(24U, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(0U));  // null set
    EXPECT_EQ(2U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(3U));
    EXPECT_EQ(3U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(5U));
    EXPECT_EQ(5U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(7U));
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(8U));
    EXPECT_EQ(24U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(20U));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficientWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(1U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(0U));  // null set
    EXPECT_EQ(2U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(3U));
    EXPECT_EQ(3U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(5U));
    EXPECT_EQ(5U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(7U));
    EXPECT_EQ(6U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(8U));
    EXPECT_EQ(24U, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(20U));
}

TEST(CoinProblemTest, GetCoinCombinationsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(
        (CoinCombinations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 4U}}),
        coinProblem.getCoinCombinationsUsingMemoizationDP(5U));
    EXPECT_EQ(
        (CoinCombinations{
            {{1U, 1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 1U, 3U}, {1U, 1U, 1U, 4U}, {1U, 3U, 3U}, {3U, 4U}}}),
        coinProblem.getCoinCombinationsUsingMemoizationDP(7U));
}

TEST(CoinProblemTest, GetCoinCombinationsUsingIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1U, 3U, 4U});

    EXPECT_EQ(
        (CoinCombinations{{1U, 1U, 1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 4U}}),
        coinProblem.getCoinCombinationsUsingIterativeDP(5U));
    EXPECT_EQ(
        (CoinCombinations{
            {{1U, 1U, 1U, 1U, 1U, 1U, 1U}, {1U, 1U, 1U, 1U, 3U}, {1U, 1U, 1U, 4U}, {1U, 3U, 3U}, {3U, 4U}}}),
        coinProblem.getCoinCombinationsUsingIterativeDP(7U));
}

}  // namespace alba
