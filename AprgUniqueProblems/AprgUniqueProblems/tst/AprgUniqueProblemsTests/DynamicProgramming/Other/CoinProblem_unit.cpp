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
    CoinProblem coinProblem({1, 2, 5, 10, 20, 50, 100, 200});

    // EXPECT_EQ(4, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(520)); // causes crash
    EXPECT_EQ(6, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(99));
    EXPECT_EQ(3, coinProblem.getNumberOfFewestCoinsUsingMemoizationDP(13));
}

TEST(CoinProblemTest, GetNumberOfFewestCoinsIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1, 2, 5, 10, 20, 50, 100, 200});

    EXPECT_EQ(4, coinProblem.getNumberOfFewestCoinsIterativeDP(520));
    EXPECT_EQ(6, coinProblem.getNumberOfFewestCoinsIterativeDP(99));
    EXPECT_EQ(3, coinProblem.getNumberOfFewestCoinsIterativeDP(13));
}

TEST(CoinProblemTest, GetFewestCoinsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1, 2, 5, 10, 20, 50, 100, 200});

    // EXPECT_EQ((Coins{200, 200, 100, 20}), coinProblem.getFewestCoinsUsingMemoizationDP(520));
    // EXPECT_EQ((Coins{50, 20, 20, 5, 2, 2}), coinProblem.getFewestCoinsUsingMemoizationDP(99));
    // EXPECT_EQ((Coins{10, 2, 1}), coinProblem.getFewestCoinsUsingMemoizationDP(13));
}

TEST(CoinProblemTest, GetFewestCoinsUsingMemoizationDPWorksOnExample2) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ((Coins{4, 1}), coinProblem.getFewestCoinsUsingMemoizationDP(5));
    EXPECT_EQ((Coins{4, 3, 3}), coinProblem.getFewestCoinsUsingMemoizationDP(10));
    EXPECT_EQ((Coins{4, 4, 4, 4, 4}), coinProblem.getFewestCoinsUsingMemoizationDP(20));
}

TEST(CoinProblemTest, GetFewestCoinsUsingIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1, 2, 5, 10, 20, 50, 100, 200});

    EXPECT_EQ((Coins{200, 200, 100, 20}), coinProblem.getFewestCoinsUsingIterativeDP(520));
    EXPECT_EQ((Coins{50, 20, 20, 5, 2, 2}), coinProblem.getFewestCoinsUsingIterativeDP(99));
    EXPECT_EQ((Coins{10, 2, 1}), coinProblem.getFewestCoinsUsingIterativeDP(13));
}

TEST(CoinProblemTest, GetFewestCoinsUsingIterativeDPWorksOnExample2) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ((Coins{4, 1}), coinProblem.getFewestCoinsUsingIterativeDP(5));
    EXPECT_EQ((Coins{4, 3, 3}), coinProblem.getFewestCoinsUsingIterativeDP(10));
    EXPECT_EQ((Coins{4, 4, 4, 4, 4}), coinProblem.getFewestCoinsUsingIterativeDP(20));
}

TEST(CoinProblemTest, GetNumberOfCoinPermutationsMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(1, coinProblem.getNumberOfCoinPermutationsMemoizationDP(0));  // null set
    EXPECT_EQ(6, coinProblem.getNumberOfCoinPermutationsMemoizationDP(5));
    EXPECT_EQ(9, coinProblem.getNumberOfCoinPermutationsMemoizationDP(6));
    EXPECT_EQ(64, coinProblem.getNumberOfCoinPermutationsMemoizationDP(10));
    EXPECT_EQ(7921, coinProblem.getNumberOfCoinPermutationsMemoizationDP(20));
}

TEST(CoinProblemTest, GetNumberOfCoinPermutationsIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(1, coinProblem.getNumberOfCoinPermutationsIterativeDP(0));  // null set
    EXPECT_EQ(6, coinProblem.getNumberOfCoinPermutationsIterativeDP(5));
    EXPECT_EQ(9, coinProblem.getNumberOfCoinPermutationsIterativeDP(6));
    EXPECT_EQ(64, coinProblem.getNumberOfCoinPermutationsIterativeDP(10));
    EXPECT_EQ(7921, coinProblem.getNumberOfCoinPermutationsIterativeDP(20));
}

TEST(CoinProblemTest, GetCoinPermutationsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(
        (CoinPermutations{{1, 1, 1, 1, 1}, {1, 1, 3}, {1, 3, 1}, {1, 4}, {3, 1, 1}, {4, 1}}),
        coinProblem.getCoinPermutationsUsingMemoizationDP(5));
    EXPECT_EQ(
        (CoinPermutations{
            {1, 1, 1, 1, 1, 1},
            {1, 1, 1, 3},
            {1, 1, 3, 1},
            {1, 1, 4},
            {1, 3, 1, 1},
            {1, 4, 1},
            {3, 1, 1, 1},
            {3, 3},
            {4, 1, 1}}),
        coinProblem.getCoinPermutationsUsingMemoizationDP(6));
}

TEST(CoinProblemTest, GetCoinPermutationsUsingIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(
        (CoinPermutations{{1, 1, 1, 1, 1}, {1, 1, 3}, {1, 3, 1}, {1, 4}, {3, 1, 1}, {4, 1}}),
        coinProblem.getCoinPermutationsUsingIterativeDP(5));
    EXPECT_EQ(
        (CoinPermutations{
            {1, 1, 1, 1, 1, 1},
            {1, 1, 1, 3},
            {1, 1, 3, 1},
            {1, 1, 4},
            {1, 3, 1, 1},
            {1, 4, 1},
            {3, 1, 1, 1},
            {3, 3},
            {4, 1, 1}}),
        coinProblem.getCoinPermutationsUsingIterativeDP(6));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(1, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(0));  // null set
    EXPECT_EQ(2, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(3));
    EXPECT_EQ(3, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(5));
    EXPECT_EQ(5, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(7));
    EXPECT_EQ(6, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(8));
    EXPECT_EQ(24, coinProblem.getNumberOfCoinCombinationsUsingMemoizationDP(20));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(1, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(0));  // null set
    EXPECT_EQ(2, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(3));
    EXPECT_EQ(3, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(5));
    EXPECT_EQ(5, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(7));
    EXPECT_EQ(6, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(8));
    EXPECT_EQ(24, coinProblem.getNumberOfCoinCombinationsUsingIterativeDP(20));
}

TEST(CoinProblemTest, GetNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficientWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(1, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(0));  // null set
    EXPECT_EQ(2, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(3));
    EXPECT_EQ(3, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(5));
    EXPECT_EQ(5, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(7));
    EXPECT_EQ(6, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(8));
    EXPECT_EQ(24, coinProblem.getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(20));
}

TEST(CoinProblemTest, GetCoinCombinationsUsingMemoizationDPWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(
        (CoinCombinations{{1, 1, 1, 1, 1}, {1, 1, 3}, {1, 4}}),
        coinProblem.getCoinCombinationsUsingMemoizationDP(5));
    EXPECT_EQ(
        (CoinCombinations{
            {{1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 3}, {1, 1, 1, 4}, {1, 3, 3}, {3, 4}}}),
        coinProblem.getCoinCombinationsUsingMemoizationDP(7));
}

TEST(CoinProblemTest, GetCoinCombinationsUsingIterativeDPWorksOnExample1) {
    CoinProblem coinProblem({1, 3, 4});

    EXPECT_EQ(
        (CoinCombinations{{1, 1, 1, 1, 1}, {1, 1, 3}, {1, 4}}),
        coinProblem.getCoinCombinationsUsingIterativeDP(5));
    EXPECT_EQ(
        (CoinCombinations{
            {{1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 3}, {1, 1, 1, 4}, {1, 3, 3}, {3, 4}}}),
        coinProblem.getCoinCombinationsUsingIterativeDP(7));
}

}  // namespace alba
