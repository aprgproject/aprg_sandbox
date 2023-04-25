#include <Math/Probability/MarkovChains.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace math {

namespace {
using MarkovChainsForTest = MarkovChains<5U>;
using DistributionForTest = MarkovChainsForTest::ProbabilityDistribution;
}  // namespace

TEST(MarkovChainsTest, GetProbabilityWorks) {
    MarkovChainsForTest markovChain;
    markovChain.setProbability(0U, 0U, 0.0);
    markovChain.setProbability(0U, 1U, 0.1);
    markovChain.setProbability(0U, 2U, 0.2);
    markovChain.setProbability(0U, 3U, 0.3);
    markovChain.setProbability(0U, 4U, 0.4);

    EXPECT_EQ(AlbaNumber(0), markovChain.getProbability(0U, 0U));
    EXPECT_EQ(AlbaNumber(0.1), markovChain.getProbability(0U, 1U));
    EXPECT_EQ(AlbaNumber(0.2), markovChain.getProbability(0U, 2U));
    EXPECT_EQ(AlbaNumber(0.3), markovChain.getProbability(0U, 3U));
    EXPECT_EQ(AlbaNumber(0.4), markovChain.getProbability(0U, 4U));
    EXPECT_EQ(AlbaNumber(0), markovChain.getProbability(1U, 0U));
    EXPECT_EQ(AlbaNumber(0), markovChain.getProbability(1U, 1U));
    EXPECT_EQ(AlbaNumber(0), markovChain.getProbability(1U, 2U));
    EXPECT_EQ(AlbaNumber(0), markovChain.getProbability(1U, 3U));
    EXPECT_EQ(AlbaNumber(0), markovChain.getProbability(1U, 4U));
}

TEST(MarkovChainsTest, SetProbabilityWorks) {
    MarkovChainsForTest markovChain;

    markovChain.setProbability(0U, 0U, 0.5);

    EXPECT_EQ(AlbaNumber(0.5), markovChain.getProbability(0U, 0U));
}

TEST(MarkovChainsTest, GetNextProbabilityDistributionWorksWithNoSteps) {
    MarkovChainsForTest markovChain;
    markovChain.setProbability(0U, 1U, 1.0);
    markovChain.setProbability(1U, 0U, 0.5);
    markovChain.setProbability(1U, 2U, 0.5);
    markovChain.setProbability(2U, 1U, 0.5);
    markovChain.setProbability(2U, 3U, 0.5);
    markovChain.setProbability(3U, 2U, 0.5);
    markovChain.setProbability(3U, 4U, 0.5);
    markovChain.setProbability(4U, 3U, 1.0);

    EXPECT_EQ((DistributionForTest{0, 1, 0, 0, 0}), markovChain.getNextProbabilityDistribution({1, 0, 0, 0, 0}));
    EXPECT_EQ((DistributionForTest{0.5, 0, 0.5, 0, 0}), markovChain.getNextProbabilityDistribution({0, 1, 0, 0, 0}));
    EXPECT_EQ(
        (DistributionForTest{0, 0.75, 0, 0.25, 0}), markovChain.getNextProbabilityDistribution({0.5, 0, 0.5, 0, 0}));
    EXPECT_EQ(
        (DistributionForTest{0.375, 0, 0.5, 0, 0.125}),
        markovChain.getNextProbabilityDistribution({0, 0.75, 0, 0.25, 0}));
    EXPECT_EQ(
        (DistributionForTest{0, 0.625, 0, 0.375, 0}),
        markovChain.getNextProbabilityDistribution({0.375, 0, 0.5, 0, 0.125}));
    EXPECT_EQ(
        (DistributionForTest{0.3125, 0, 0.5, 0, 0.1875}),
        markovChain.getNextProbabilityDistribution({0, 0.625, 0, 0.375, 0}));
}

TEST(MarkovChainsTest, GetNextProbabilityDistributionWorksWithSteps) {
    MarkovChainsForTest markovChain;
    markovChain.setProbability(0U, 1U, 1.0);
    markovChain.setProbability(1U, 0U, 0.5);
    markovChain.setProbability(1U, 2U, 0.5);
    markovChain.setProbability(2U, 1U, 0.5);
    markovChain.setProbability(2U, 3U, 0.5);
    markovChain.setProbability(3U, 2U, 0.5);
    markovChain.setProbability(3U, 4U, 0.5);
    markovChain.setProbability(4U, 3U, 1.0);

    EXPECT_EQ((DistributionForTest{0, 1, 0, 0, 0}), markovChain.getNextProbabilityDistribution({1, 0, 0, 0, 0}, 1));
    EXPECT_EQ((DistributionForTest{0.5, 0, 0.5, 0, 0}), markovChain.getNextProbabilityDistribution({1, 0, 0, 0, 0}, 2));
    EXPECT_EQ(
        (DistributionForTest{0, 0.75, 0, 0.25, 0}), markovChain.getNextProbabilityDistribution({1, 0, 0, 0, 0}, 3));
    EXPECT_EQ(
        (DistributionForTest{0.375, 0, 0.5, 0, 0.125}), markovChain.getNextProbabilityDistribution({1, 0, 0, 0, 0}, 4));
    EXPECT_EQ(
        (DistributionForTest{0, 0.625, 0, 0.375, 0}), markovChain.getNextProbabilityDistribution({1, 0, 0, 0, 0}, 5));
    EXPECT_EQ(
        (DistributionForTest{0.3125, 0, 0.5, 0, 0.1875}),
        markovChain.getNextProbabilityDistribution({1, 0, 0, 0, 0}, 6));
}

}  // namespace math

}  // namespace alba
