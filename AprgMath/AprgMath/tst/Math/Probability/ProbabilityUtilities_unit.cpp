#include <Math/Probability/ProbabilityUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(ProbabilityUtilitiesTest, GetCorrectProbabilityWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(1, 2U), getCorrectProbability(AlbaNumber::createFraction(1, 2U)));
    EXPECT_EQ(AlbaNumber(1), getCorrectProbability(AlbaNumber::createFraction(3, 2U)));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(AlbaNumber(AlbaNumber::Value::NegativeInfinity)));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(AlbaNumber(AlbaNumber::Value::NotANumber)));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(AlbaNumber::createFraction(3, 0U)));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(AlbaNumber::createFraction(0, 0U)));
}

TEST(ProbabilityUtilitiesTest, GetProbabilityWorks)
{
    EXPECT_EQ(AlbaNumber(0), getProbability(0U, 0U));
    EXPECT_EQ(AlbaNumber(0), getProbability(0U, 1U));
    EXPECT_EQ(AlbaNumber(0), getProbability(1U, 0U));
    EXPECT_EQ(AlbaNumber(0), getProbability(-11U, 0U));
    EXPECT_EQ(AlbaNumber(1), getProbability(3U, 1U));
    EXPECT_EQ(AlbaNumber(1), getProbability(3U, 2U));
    EXPECT_EQ(AlbaNumber(1), getProbability(3U, 3U));
    EXPECT_EQ(AlbaNumber::createFraction(3, 4U), getProbability(3U, 4U));
    EXPECT_EQ(AlbaNumber::createFraction(3, 5U), getProbability(3U, 5U));
}

TEST(ProbabilityUtilitiesTest, GetComplementOfProbabilityWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(2, 5U), getComplementOfProbability(getProbability(3U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetUnionOfProbabilitiesOfDisjointEventsWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(3, 5U),
              getUnionOfProbabilitiesOfDisjointEvents(getProbability(1U, 5U), getProbability(2U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetUnionOfProbabilitiesWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(2, 5U),
              getUnionOfProbabilities(getProbability(1U, 5U), getProbability(2U, 5U), getProbability(1U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetIntersectionOfProbabilitiesOfIndependentEventsWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(4, 25U),
              getIntersectionOfProbabilitiesOfIndependentEvents(getProbability(2U, 5U), getProbability(2U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetIntersectionOfProbabilitiesWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(1, 5U),
              getIntersectionOfProbabilities(getProbability(2U, 5U), getProbability(2U, 5U), getProbability(1U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetConditionalProbabilityOfEventAGivenThatEventBHappenedWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(1, 2U),
              getConditionalProbabilityOfEventAGivenThatEventBHappened(getProbability(2U, 5U), getProbability(1U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetExpectedValueWorks)
{
    ValueAndProbabilityPairs pairsToTest
    {{1U, getProbability(1U, 5U)},
        {2U, getProbability(1U, 5U)},
        {3U, getProbability(1U, 5U)},
        {4U, getProbability(1U, 5U)},
        {5U, getProbability(1U, 5U)}};

    EXPECT_EQ(AlbaNumber(3), getExpectedValue(pairsToTest));
}

TEST(ProbabilityUtilitiesTest, GetExpectedValueInUniformDistributionWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(101, 2U), getExpectedValueInUniformDistribution(AlbaNumber(1), AlbaNumber(100)));
}

TEST(ProbabilityUtilitiesTest, GetExpectedValueInBinomialDistributionWorks)
{
    EXPECT_EQ(AlbaNumber(75U), getExpectedValueInBinomialDistribution(AlbaNumber::createFraction(3, 4), 100U));
}

TEST(ProbabilityUtilitiesTest, GetExpectedValueInGeometricDistributionWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(4, 3), getExpectedValueInGeometricDistribution(AlbaNumber::createFraction(3, 4)));
}

}

}