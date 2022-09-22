#include <Math/Probability/ProbabilityUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(ProbabilityExampleTest, DiceExampleWorks)
{
    // For example, when throwing a dice, the outcome is an integer between 1 and 6, and the probability of each outcome is 1/6.
    // For example, we can calculate the following probabilities:

    // -> P("the outcome is 4") = 1/6
    EXPECT_EQ(AlbaNumber::createFraction(1, 6U), getProbability(1U, 6U));

    // -> P("the outcome is not 6") = 5/6
    EXPECT_EQ(AlbaNumber::createFraction(5, 6U), getProbability(5U, 6U));

    // -> P("the outcome is even") = 1/2
    EXPECT_EQ(AlbaNumber::createFraction(1, 2U), getProbability(3U, 6U));
}

TEST(ProbabilityExampleTest, DrawCardExampleWorks)
{
    // As an example, let us calculate the probability of drawing three cards with the same value from a shuffled deck of cards.
    // For example: the 8 of hearts, 8 of diamonds and 8 spades satisfies the condition.

    // In this example, we draw three cards, so the process consists of three steps.
    // We require that each step of the process is successful.

    // -> Probability of the first card is 1 because theres nothing to compare yet.
    EXPECT_EQ(AlbaNumber(1U), getProbability(1U, 1U));

    // -> Probability of the second card is 3/51, because there are 51 cards left and 3 of them have the same value as the first card.
    EXPECT_EQ(AlbaNumber::createFraction(3, 51U), getProbability(3U, 51U));

    // -> Probability of the third card 2/50, because there are 51 cards left and 2 of them have the same value as the first and second cards.
    EXPECT_EQ(AlbaNumber::createFraction(2, 50U), getProbability(2U, 50U));

    // Probability of all three steps
    EXPECT_EQ(AlbaNumber::createFraction(1, 425U), getProbability(1U, 1U) * getProbability(3U, 51U) * getProbability(2U, 50U));
}

TEST(ProbabilityExampleTest, ComplementExampleWorks)
{
    // What is thhe probability of getting at least one six when throwing a dice ten times?
    // Take note that probability of getting NOT a six on single throw is (5/6)
    // Take note that probability of getting NOT a six on when throwing a dice ten times is (5/6)^10
    // The complement of NOT getting a six is getting a six.
    // Hence the probability is 1-(5/6)^10.

    AlbaNumber probabilityToVerify = getComplementOfProbability(getProbability(5U, 6U)^10);

    AlbaNumber expectedProbability(AlbaNumber::createFraction(50700551, 60466176U));
    EXPECT_EQ(expectedProbability, probabilityToVerify);
}

TEST(ProbabilityExampleTest, UnionExampleWorks)
{
    // For example, when throwing a dice.
    // Here are sample events:
    // -> A = "the outcome is even" -> P(A) = 3/6
    // -> B = "the outcome is less than 4" -> P(B) = 3/6
    // -> A∩B = "the outcome is even or less than 4" -> P(A∩B) = 1/6

    // What is the probability of the union of A and B? Or P(A∪B)?

    AlbaNumber probabilityToVerify = getUnionOfProbabilities(getProbability(3U, 6U), getProbability(3U, 6U), getProbability(1U, 6U));

    AlbaNumber expectedProbability(AlbaNumber::createFraction(5, 6U));
    EXPECT_EQ(expectedProbability, probabilityToVerify);
}

TEST(ProbabilityExampleTest, ConditionalProbabilityExampleWorks)
{
    // For example, when throwing a dice.
    // Here are sample events:
    // -> A = "the outcome is even" -> P(A) = 3/6
    // -> B = "the outcome is less than 4" -> P(B) = 3/6
    // -> A∩B = "the outcome is even or less than 4" -> P(A∩B) = 1/6

    // What is the conditional probability of A given B? Or P(A|B)?

    AlbaNumber probabilityToVerify = getConditionalProbabilityOfEventAGivenThatEventBHappened(
                getProbability(3U, 6U), getProbability(1U, 6U));

    AlbaNumber expectedProbability(AlbaNumber::createFraction(1, 3U));
    EXPECT_EQ(expectedProbability, probabilityToVerify);
}

TEST(ProbabilityExampleTest, IntersectionExampleWorks)
{
    // For example, when drawing a card from a deck.
    // Here are sample events:
    // -> A = "the suit is clubs" -> P(A) = 13/52
    // -> B = "the value is four" -> P(B) = 4/52
    // -> A and B are independent -> P(A|B) = P(A) and P(B|A) = P(B)

    // What is the probability of the intersection of A and B? Or P(A∪B)?

    AlbaNumber probabilityToVerify = getIntersectionOfProbabilitiesOfIndependentEvents(
                getProbability(13U, 52U), getProbability(4U, 52U));

    AlbaNumber expectedProbability(AlbaNumber::createFraction(1, 52U));
    EXPECT_EQ(expectedProbability, probabilityToVerify);
}

TEST(ProbabilityExampleTest, ExpectedValueExampleWorks)
{
    // For example, when throwing a dice.
    // Probability of value of 1 is 1/6.
    // Probability of value of 2 is 1/6.
    // Probability of value of 3 is 1/6.
    // Probability of value of 4 is 1/6.
    // Probability of value of 5 is 1/6.
    // Probability of value of 6 is 1/6.

    ValueAndProbabilityPairs pairsToTest
    {{1U, getProbability(1U, 6U)},
        {2U, getProbability(1U, 6U)},
        {3U, getProbability(1U, 6U)},
        {4U, getProbability(1U, 6U)},
        {5U, getProbability(1U, 6U)},
        {6U, getProbability(1U, 6U)}};

    EXPECT_EQ(AlbaNumber::createFraction(7, 2U), getExpectedValue(pairsToTest));
}

}

}