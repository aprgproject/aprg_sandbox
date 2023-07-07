#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Math/Probability/ProbabilityUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba {

namespace math {

TEST(ProbabilityUtilitiesTest, DoesExpectedValuesHaveLinearityWorks) {
    ValueAndProbabilityPairs firstPairs{
        {1U, getProbability(1U, 5U)}, {2U, getProbability(1U, 5U)}, {3U, getProbability(1U, 5U)}};
    ValueAndProbabilityPairs secondPairs{{4U, getProbability(1U, 5U)}, {5U, getProbability(1U, 5U)}};

    EXPECT_TRUE(doesExpectedValuesHaveLinearity(firstPairs, secondPairs));
}

TEST(ProbabilityUtilitiesTest, GetCorrectProbabilityWorks) {
    EXPECT_EQ(AlbaNumber::createFraction(1, 2U), getCorrectProbability(AlbaNumber::createFraction(1, 2U)));
    EXPECT_EQ(AlbaNumber(1), getCorrectProbability(AlbaNumber::createFraction(3, 2U)));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(ALBA_NUMBER_POSITIVE_INFINITY));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(ALBA_NUMBER_NOT_A_NUMBER));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(AlbaNumber::createFraction(3, 0U)));
    EXPECT_EQ(AlbaNumber(0), getCorrectProbability(AlbaNumber::createFraction(0, 0U)));
}

TEST(ProbabilityUtilitiesTest, GetProbabilityWorks) {
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

TEST(ProbabilityUtilitiesTest, GetProbabilityOnBinomialDistributionWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(390625, 2519424U),
        getProbabilityOnBinomialDistribution(getProbability(1U, 6U), 3U, 10U));
}

TEST(ProbabilityUtilitiesTest, GetProbabilityOnGeometricDistributionWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(125, 1296U), getProbabilityOnGeometricDistribution(getProbability(1U, 6U), 4U));
}

TEST(ProbabilityUtilitiesTest, GetComplementOfProbabilityWorks) {
    EXPECT_EQ(AlbaNumber::createFraction(2, 5U), getComplementOfProbability(getProbability(3U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetUnionOfProbabilitiesOfDisjointEventsWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(3, 5U),
        getUnionOfProbabilitiesOfDisjointEvents(getProbability(1U, 5U), getProbability(2U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetUnionOfProbabilitiesWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(2, 5U),
        getUnionOfProbabilities(getProbability(1U, 5U), getProbability(2U, 5U), getProbability(1U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetIntersectionOfProbabilitiesOfIndependentEventsWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(4, 25U),
        getIntersectionOfProbabilitiesOfIndependentEvents(getProbability(2U, 5U), getProbability(2U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetIntersectionOfProbabilitiesWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(1, 5U),
        getIntersectionOfProbabilities(getProbability(2U, 5U), getProbability(2U, 5U), getProbability(1U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetConditionalProbabilityOfEventAGivenThatEventBHappenedWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(1, 2U),
        getConditionalProbabilityOfEventAGivenThatEventBHappened(getProbability(2U, 5U), getProbability(1U, 5U)));
}

TEST(ProbabilityUtilitiesTest, GetExpectedValueWorks) {
    ValueAndProbabilityPairs pairsToTest{
        {1U, getProbability(1U, 5U)},
        {2U, getProbability(1U, 5U)},
        {3U, getProbability(1U, 5U)},
        {4U, getProbability(1U, 5U)},
        {5U, getProbability(1U, 5U)}};

    EXPECT_EQ(AlbaNumber(3), getExpectedValue(pairsToTest));
}

TEST(ProbabilityUtilitiesTest, GetExpectedValueInUniformDistributionWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(101, 2U), getExpectedValueInUniformDistribution(AlbaNumber(1), AlbaNumber(100)));
}

TEST(ProbabilityUtilitiesTest, GetExpectedValueInBinomialDistributionWorks) {
    EXPECT_EQ(AlbaNumber(75), getExpectedValueInBinomialDistribution(AlbaNumber::createFraction(3, 4), 100U));
}

TEST(ProbabilityUtilitiesTest, GetExpectedValueInGeometricDistributionWorks) {
    EXPECT_EQ(
        AlbaNumber::createFraction(4, 3), getExpectedValueInGeometricDistribution(AlbaNumber::createFraction(3, 4)));
}

TEST(ProbabilityUtilitiesTest, GetNumberOfPeopleForTheBirthdayParadoxWorks) {
    EXPECT_EQ(AlbaNumber(1), getNumberOfPeopleForTheBirthdayParadox(0));
    EXPECT_EQ(AlbaNumber(20), getNumberOfPeopleForTheBirthdayParadox(AlbaNumber::createFraction(1, 2)));
    EXPECT_EQ(AlbaNumber(26), getNumberOfPeopleForTheBirthdayParadox(0.85));
    EXPECT_EQ(AlbaNumber(28), getNumberOfPeopleForTheBirthdayParadox(1));
}

}  // namespace math

}  // namespace alba
