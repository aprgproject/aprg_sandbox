#include "ProbabilityUtilities.hpp"

#include <Math/Types.hpp>

namespace alba
{

namespace math
{

AlbaNumber getCorrectProbability(
        AlbaNumber const& probability)
{
    // If an event is certain to happen, its probability is 1, and if an event is impossible, its probability is 0.

    AlbaNumber result(0);
    if(probability.isAFiniteValue())
    {
        if(probability < 0)
        {
            result = 0;
        }
        if(probability > 1)
        {
            result = 1;
        }
        else
        {
            result = probability;
        }
    }
    return result;
}

AlbaNumber getProbability(
        UnsignedInteger const numberOfDesiredOutcome,
        UnsignedInteger const totalNumberOfOutcomes)
{
    // A probability is a real number between 0 and 1 that indicates how probable an event is.
    // If an event is certain to happen, its probability is 1, and if an event is impossible, its probability is 0.
    // The probability of an event is denoted P(...) where the three dots describe the event.

    return getCorrectProbability(
                AlbaNumber::createFraction(
                    static_cast<int>(numberOfDesiredOutcome),
                    static_cast<unsigned int>(totalNumberOfOutcomes)));
}

AlbaNumber getComplementOfProbability(
        AlbaNumber const& probability)
{
    // The complement of A means the probability that "Event A does not happen".
    // Equation: P(A') = 1-P(A)

    return getCorrectProbability(AlbaNumber(1) - probability);
}

AlbaNumber getUnionOfProbabilitiesOfDisjointEvents(
        AlbaNumber const& probabilityOfEventA,
        AlbaNumber const& probabilityOfEventB)
{
    // The union of A and B means the probability that "Event A OR Event B happen".
    // If events are disjoint, the union of probability is the sum of probabilities of events.
    // Equation if disjoint: P(A∪B) = P(A) + P(B)

    return getCorrectProbability(probabilityOfEventA + probabilityOfEventB);
}

AlbaNumber getUnionOfProbabilities(
        AlbaNumber const& probabilityOfEventA,
        AlbaNumber const& probabilityOfEventB,
        AlbaNumber const& probabilityOfEventAAndEventB)
{
    // The union of A and B means the probability that "Event A OR Event B happen".
    // The union of probability is probabilityOfEventA + probabilityOfEventB - probabilityOfEventAAndEventB.
    // General equation: P(A∪B) = P(A) + P(B) - P(A∩B)

    return getCorrectProbability(probabilityOfEventA + probabilityOfEventB - probabilityOfEventAAndEventB);
}

AlbaNumber getIntersectionOfProbabilitiesOfIndependentEvents(
        AlbaNumber const& probabilityOfEventA,
        AlbaNumber const& probabilityOfEventB)
{
    // The intersection of A and B means the probability that "Event A AND Event B happen".
    // If events are independent, the intersection of probability is the product of probabilities of events.
    // Equation if independent: P(A∩B) = P(A) * P(B)

    // Events A and B are independent if P(A|B) = P(A) and P(B|A) = P(B).
    // This means that the fact that B happens does not change the probability of A, and vice versa.

    return getCorrectProbability(probabilityOfEventA * probabilityOfEventB);
}

AlbaNumber getIntersectionOfProbabilities(
        AlbaNumber const& probabilityOfEventA,
        AlbaNumber const& probabilityOfEventB,
        AlbaNumber const& probabilityOfEventAAndEventB)
{
    // The intersection of A and B means the probability that "Event A AND Event B happen".
    // The intersection of probability is product of probabilityOfEventA and "conditional probability of event B given A"
    // General equation: P(A∩B) = P(A) * P(B|A)

    return getCorrectProbability(
                probabilityOfEventA * getConditionalProbabilityOfEventAGivenThatEventBHappened(probabilityOfEventB, probabilityOfEventAAndEventB));
}

AlbaNumber getConditionalProbabilityOfEventAGivenThatEventBHappened(
        AlbaNumber const& probabilityOfEventB,
        AlbaNumber const& probabilityOfEventAAndEventB)
{
    // The conditional probability is the probability of A assuming that B happens.
    // Equation: P(A|B) = P(A∩B) / P(B)

    return getCorrectProbability(probabilityOfEventAAndEventB / probabilityOfEventB);
}

AlbaNumber getExpectedValue(
        ValueAndProbabilityPairs const& allValueAndProbabilityPairsOfX)
{
    // The expected value E[X] indicates the average value of a random variable X.
    // The expected value can be calculated as the summation of P(X=x) * x, where x goes through all possible values of X.

    AlbaNumber result;
    for(ValueAndProbabilityPair const& valueAndProbabilityPair: allValueAndProbabilityPairsOfX)
    {
        result += valueAndProbabilityPair.first * valueAndProbabilityPair.second;
    }
    return result;
}

AlbaNumber getExpectedValueInUniformDistribution(
        AlbaNumber const& firstValue,
        AlbaNumber const& secondValue)
{
    // In a uniform distribution, the random variable X has n possible values a,a+1,...,b and the probability of each value is 1/n.
    // Equation: E[X] = (a+b)/2

    return (firstValue + secondValue)/2;
}

AlbaNumber getExpectedValueInBinomialDistribution(
        AlbaNumber const& probability,
        UnsignedInteger const n)
{
    // In a binomial distribution, n attempts are made and the probability that a single attempt succeeds is p.
    // The expected value of X in a binomial distribution is E[X] = pn.

    return probability * AlbaNumber(static_cast<unsigned int>(n));
}

AlbaNumber getExpectedValueInGeometricDistribution(
        AlbaNumber const& probability)
{
    // In a binomial distribution, n attempts are made and the probability that a single attempt succeeds is p.
    // The expected value of X in a binomial distribution is E[X] = pn.

    return AlbaNumber(1) / probability;
}


}

}