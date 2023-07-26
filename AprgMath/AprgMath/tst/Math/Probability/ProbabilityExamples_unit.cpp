#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Math/Probability/ProbabilityUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace math {

TEST(ProbabilityExampleTest, DiceExampleWorks) {
    // For example, when throwing a dice, the outcome is an integer between 1 and 6, and the probability of each outcome
    // is 1/6. For example, we can calculate the following probabilities:

    // -> P("the outcome is 4") = 1/6
    EXPECT_EQ(AlbaNumber::createFraction(1, 6U), getProbability(1U, 6U));

    // -> P("the outcome is not 6") = 5/6
    EXPECT_EQ(AlbaNumber::createFraction(5, 6U), getProbability(5U, 6U));

    // -> P("the outcome is even") = 1/2
    EXPECT_EQ(AlbaNumber::createFraction(1, 2U), getProbability(3U, 6U));
}

TEST(ProbabilityExampleTest, DrawCardExampleWorks) {
    // As an example, let us calculate the probability of drawing three cards with the same value from a shuffled deck
    // of cards. For example: the 8 of hearts, 8 of diamonds and 8 spades satisfies the condition.

    // In this example, we draw three cards, so the process consists of three steps.
    // We require that each step of the process is successful.

    // -> Probability of the first card is 1 because theres nothing to compare yet.
    EXPECT_EQ(AlbaNumber(1), getProbability(1U, 1U));

    // -> Probability of the second card is 3/51, because there are 51 cards left and 3 of them have the same value as
    // the first card.
    EXPECT_EQ(AlbaNumber::createFraction(3, 51U), getProbability(3U, 51U));

    // -> Probability of the third card 2/50, because there are 51 cards left and 2 of them have the same value as the
    // first and second cards.
    EXPECT_EQ(AlbaNumber::createFraction(2, 50U), getProbability(2U, 50U));

    // Probability of all three steps
    EXPECT_EQ(
        AlbaNumber::createFraction(1, 425U),
        getProbability(1U, 1U) * getProbability(3U, 51U) * getProbability(2U, 50U));
}

TEST(ProbabilityExampleTest, BallsAndBoxesExample_ExpectedNumberOfBallsInABox) {
    // How many balls fall in a given box?
    // The number of balls that fall in given bin follows the binomial distribution.
    // The expected number of balls that fall in a box is numberOfBalls/numberOfBoxes

    auto numberOfBalls = 2;
    auto numberOfBoxes = 10;
    EXPECT_EQ(AlbaNumber::createFraction(1, 5), AlbaNumber::createFraction(numberOfBalls, numberOfBoxes));
}

TEST(ProbabilityExampleTest, BallsAndBoxesExample_ProbabilityOfOneBall) {
    // How many balls must we toss on the average until a given box contains a ball?

    auto numberOfBoxes = 2;
    AlbaNumber probabilityOfASingleEvent(AlbaNumber::createFraction(1, numberOfBoxes));
    EXPECT_EQ(AlbaNumber::createFraction(1, 2), getProbabilityOnGeometricDistribution(probabilityOfASingleEvent, 1));
}

TEST(ProbabilityExampleTest, BallsAndBoxesExample_ProbabilityOfEveryBinHasOneBall) {
    // How many balls must we toss until every bin contains at least one ball?

    // E[n] = E[ summation from 1 to b of i (ni0 ]
    // E[n] = b(ln b + O(1))
}

TEST(ProbabilityExampleTest, BallsAndBoxesExample_ProbabilityOfSingleEmptyBoxes) {
    // Let us now consider a problem where n balls are randomly placed in n boxes, and our task is to calculate the
    // probability of single empty boxes. Assume that each ball has an uniform probability to be placed in any of the
    // boxes.

    // Total number of combinations:
    // -> Using balls and boxes scenario 2 : Combination(n+n-1, n) = Combination(2n-1, n)
    // Number of single empty boxes (for n=2):
    // |oo|  |    Positions: {1, 1}    Representation: o o > >
    // |o |o |    Positions: {1, 2}    Representation: o > o >
    // |  |oo|    Positions: {2, 2}    Representation: > > o o
    // -> Form should have single "o o" and "> >" the rest "o >"
    // ---> All forms of single "o o" and "> >" the rest "o >" = Number of permutations (n, n)
    // ---> All forms "o >" = Number of permutations (n-2, n-2)
    // -> Number of permutations (n, n) / Number of permutations (n-2, n-2)

    // Probability = (Number of permutations (n, n) / Number of permutations (n-2, n-2)) / Combination(2n-1, n)

    auto numberOfBoxes = 2;
    auto calculatedProbability = AlbaNumber::createFraction(
        (getNumberOfPermutations(numberOfBoxes, numberOfBoxes) /
         getNumberOfPermutations(numberOfBoxes - 2, numberOfBoxes - 2)),
        getNumberOfCombinations(numberOfBoxes * 2 - 1, numberOfBoxes));
    EXPECT_EQ(AlbaNumber::createFraction(2, 3), calculatedProbability);
}

TEST(ProbabilityExampleTest, StreaksExample_LongestStreak) {
    // Suppose you flip a fair coin n times.
    // What is the longest streak of consecutive heads that you expect to see?
    // Probability that all k flips are head is P(AllHeads) = 1/(2^k).
    // Answer for this lg(n)

    auto numberOfTries = 16;
    EXPECT_EQ(4, getLogarithmWithBase2Of(numberOfTries));
}

TEST(ProbabilityExampleTest, BinomialDistributionProbabilityExampleWorks) {
    // In a binomial distribution, n attempts are made and the probability that a single attempt succeeds is p.

    // For example, when throwing a dice ten times, the probability of throwing a six exactly three times is (1/6)^3 *
    // (5/6)^7 * Combinations(10, 3)

    EXPECT_EQ(
        AlbaNumber::createFraction(390625, 2519424U),
        getProbabilityOnBinomialDistribution(getProbability(1U, 6U), 3U, 10U));
}

TEST(ProbabilityExampleTest, GeometricDistributionProbabilityExampleWorks) {
    // In a geometric distribution, the probability that an attempt succeeds is p, and we continue until the first
    // success happens.

    // For example, if we throw a dice until we throw a six, the probability that the number of throws is exactly 4 is
    // (5/6)^3 * (1/6).

    EXPECT_EQ(
        AlbaNumber::createFraction(125, 1296U), getProbabilityOnGeometricDistribution(getProbability(1U, 6U), 4U));
}

TEST(ProbabilityExampleTest, ComplementExampleWorks) {
    // What is the probability of getting at least one six when throwing a dice ten times?
    // Take note that probability of getting NOT a six on single throw is (5/6)
    // Take note that probability of getting NOT a six on when throwing a dice ten times is (5/6)^10
    // The complement of NOT getting a six is getting a six.
    // Hence the probability is 1-(5/6)^10.

    AlbaNumber probabilityToVerify = getComplementOfProbability(getProbability(5U, 6U) ^ 10);

    AlbaNumber expectedProbability(AlbaNumber::createFraction(50700551, 60466176U));
    EXPECT_EQ(expectedProbability, probabilityToVerify);
}

TEST(ProbabilityExampleTest, UnionExampleWorks) {
    // For example, when throwing a dice:
    // Here are sample events:
    // -> A = "the outcome is even" -> P(A) = 3/6
    // -> B = "the outcome is less than 4" -> P(B) = 3/6
    // -> A∩B = "the outcome is even or less than 4" -> P(A∩B) = 1/6

    // What is the probability of the union of A and B? Or P(A∪B)?

    AlbaNumber probabilityToVerify =
        getUnionOfProbabilities(getProbability(3U, 6U), getProbability(3U, 6U), getProbability(1U, 6U));

    AlbaNumber expectedProbability(AlbaNumber::createFraction(5, 6U));
    EXPECT_EQ(expectedProbability, probabilityToVerify);
}

TEST(ProbabilityExampleTest, ConditionalProbabilityExampleWorks) {
    // For example, when throwing a dice:
    // Here are sample events:
    // -> A = "the outcome is even" -> P(A) = 3/6
    // -> B = "the outcome is less than 4" -> P(B) = 3/6
    // -> A∩B = "the outcome is even or less than 4" -> P(A∩B) = 1/6

    // What is the conditional probability of A given B? Or P(A|B)?

    AlbaNumber probabilityToVerify =
        getConditionalProbabilityOfEventAGivenThatEventBHappened(getProbability(3U, 6U), getProbability(1U, 6U));

    AlbaNumber expectedProbability(AlbaNumber::createFraction(1, 3U));
    EXPECT_EQ(expectedProbability, probabilityToVerify);
}

TEST(ProbabilityExampleTest, IntersectionExampleWorks) {
    // For example, when drawing a card from a deck:
    // Here are sample events:
    // -> A = "the suit is clubs" -> P(A) = 13/52
    // -> B = "the value is four" -> P(B) = 4/52
    // -> A and B are independent -> P(A|B) = P(A) and P(B|A) = P(B)

    // What is the probability of the intersection of A and B? Or P(A∪B)?

    AlbaNumber probabilityToVerify =
        getIntersectionOfProbabilitiesOfIndependentEvents(getProbability(13U, 52U), getProbability(4U, 52U));

    AlbaNumber expectedProbability(AlbaNumber::createFraction(1, 52U));
    EXPECT_EQ(expectedProbability, probabilityToVerify);
}

TEST(ProbabilityExampleTest, ExpectedValueExampleWorks) {
    // For example, when throwing a dice:
    // Probability of value of 1 is 1/6.
    // Probability of value of 2 is 1/6.
    // Probability of value of 3 is 1/6.
    // Probability of value of 4 is 1/6.
    // Probability of value of 5 is 1/6.
    // Probability of value of 6 is 1/6.
    // Expected value is 7/2

    ValueAndProbabilityPairs pairsToTest{{1U, getProbability(1U, 6U)}, {2U, getProbability(1U, 6U)},
                                         {3U, getProbability(1U, 6U)}, {4U, getProbability(1U, 6U)},
                                         {5U, getProbability(1U, 6U)}, {6U, getProbability(1U, 6U)}};

    EXPECT_EQ(AlbaNumber::createFraction(7, 2U), getExpectedValue(pairsToTest));
}

TEST(ProbabilityExampleTest, UniformExpectedValueExampleWorks) {
    // In a uniform distribution, the random variable X has n possible values a,a+1,...,b and the probability of each
    // value is 1/n.

    // For example, when throwing a dice:
    // lowestValue=1
    // highestValue=6
    // P(X=x) = 1/6 for each value x
    // Expected value is 7/2

    EXPECT_EQ(AlbaNumber::createFraction(7, 2U), getExpectedValueInUniformDistribution(1U, 6U));
}

TEST(ProbabilityExampleTest, BinomialDistributionExpectedValueExampleWorks) {
    // In a binomial distribution, n attempts are made and the probability that a single attempt succeeds is p.

    // For example, when throwing a dice ten times, what is approximate number of attempts for throwing a six exactly
    // three times? The expected value is 5/3. This is the approximately the number of attempts to be made for the
    // condition to be successful.

    EXPECT_EQ(AlbaNumber::createFraction(5, 3U), getExpectedValueInBinomialDistribution(getProbability(1U, 6U), 10U));
}

TEST(ProbabilityExampleTest, GeometricDistributionExpectedValueWorks_OnExample1) {
    // In a geometric distribution, the probability that an attempt succeeds is p, and we continue until the first
    // success happens.

    // For example, if we throw a dice, what is approximate number of attempts until we throw a six?
    // The expected value is 6.
    // This is the approximately the number of attempts to be made for the condition to be successful.

    EXPECT_EQ(AlbaNumber(6), getExpectedValueInGeometricDistribution(getProbability(1U, 6U)));
}

TEST(ProbabilityExampleTest, GeometricDistributionExpectedValueWorks_OnBirthExample) {
    // In a country, all families want a boy.
    // They keep having babies till a boy is born.
    // What is the expected ratio of boys and girls in the country?

    EXPECT_EQ(AlbaNumber(2), getExpectedValueInGeometricDistribution(getProbability(1U, 2U)));
    EXPECT_EQ(AlbaNumber::createFraction(1, 2), getProbability(1U, 2U));
}

}  // namespace math

}  // namespace alba
