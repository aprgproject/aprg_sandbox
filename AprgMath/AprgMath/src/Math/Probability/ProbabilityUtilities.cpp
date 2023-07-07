#include "ProbabilityUtilities.hpp"

#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Math/Types.hpp>

using namespace alba::mathHelper;using namespace std;

namespace alba {
namespace math {

bool doesExpectedValuesHaveLinearity(
    ValueAndProbabilityPairs const& firstSetOfValueAndProbabilityPairsOfX,
    ValueAndProbabilityPairs const& secondSetOfValueAndProbabilityPairsOfX) {
    // A useful property of expected values is linearity.
    // It means that the sum  E[X1+X2+...+Xn] always equals the sum E[X1]+E[X2]+...+E[Xn].
    // This formula holds even if random variables depend on each other.

    AlbaNumber expectedValueFromSeparated = getExpectedValue(firstSetOfValueAndProbabilityPairsOfX) +
                                            getExpectedValue(secondSetOfValueAndProbabilityPairsOfX);

    ValueAndProbabilityPairs all(firstSetOfValueAndProbabilityPairsOfX);
    all.reserve(all.size() + secondSetOfValueAndProbabilityPairsOfX.size());
    copy(
        secondSetOfValueAndProbabilityPairsOfX.cbegin(), secondSetOfValueAndProbabilityPairsOfX.cend(),
        back_inserter(all));
    AlbaNumber expectedValueFromCombined = getExpectedValue(all);

    return expectedValueFromSeparated == expectedValueFromCombined;
}

AlbaNumber getCorrectProbability(AlbaNumber const& probability) {
    // If an event is certain to happen, its probability is 1, and if an event is impossible, its probability is 0.

    AlbaNumber result(0);
    if (probability.isAFiniteValue()) {
        if (probability < 0) {
            result = 0;
        }
        if (probability > 1) {
            result = 1;
        } else {
            result = probability;
        }
    }
    return result;
}

AlbaNumber getProbability(UnsignedInteger const numberOfDesiredOutcome, UnsignedInteger const totalNumberOfOutcomes) {
    // A probability is a real number between 0 and 1 that indicates how probable an event is.
    // If an event is certain to happen, its probability is 1, and if an event is impossible, its probability is 0.
    // The probability of an event is denoted P(...) where the three dots describe the event.

    return getCorrectProbability(
        AlbaNumber::createFraction(static_cast<int>(numberOfDesiredOutcome), static_cast<int>(totalNumberOfOutcomes)));
}

AlbaNumber getProbabilityOnBinomialDistribution(
    AlbaNumber const& probabilityOfASingleAttempt, UnsignedInteger const xTarget, UnsignedInteger const nTries) {
    // In a binomial distribution, n attempts are made and the probability that a single attempt succeeds is p.

    // The random variable X counts the number of successful attempts, and the probability of a value x is    // P(X=x) = p^x * (1-p)^(n-x) * combinations of (n, x)
    // where p^x and (1-p)^(n-x) correspond to successful and unsuccessful attempts, and nx
    // combinations of (n, x)is the number of ways we can choose the order of the attempts.

    AlbaNumber probabilityOfSuccessfulAttempts = probabilityOfASingleAttempt ^ static_cast<int>(xTarget);
    AlbaNumber probabilityOfUnsuccessfulAttempts =
        (AlbaNumber(1) - probabilityOfASingleAttempt) ^ static_cast<int>(nTries - xTarget);
    int numberOfCombinations = static_cast<int>(getNumberOfCombinations(nTries, xTarget));
    return getCorrectProbability(
        probabilityOfSuccessfulAttempts * probabilityOfUnsuccessfulAttempts * numberOfCombinations);
}

AlbaNumber getProbabilityOnGeometricDistribution(
    AlbaNumber const& probabilityOfASingleAttempt, UnsignedInteger const xTarget) {
    // In a geometric distribution, the probability that an attempt succeeds is p, and we continue until the first
    // success happens.
    // The random variable X counts the number of attempts needed, and the probability of a value x is
    // P(X=x) = (1-p)^(x-1) * p
    // where (1-p)^(x-1) corresponds to the unsuccessful attempts and p corresponds to the first successful attempt.

    AlbaNumber probabilityOfUnsuccessfulAttempts =
        (AlbaNumber(1) - probabilityOfASingleAttempt) ^ static_cast<int>(xTarget - 1);
    AlbaNumber probabilityOfFirstSuccessfulAttempt = probabilityOfASingleAttempt;
    return getCorrectProbability(probabilityOfUnsuccessfulAttempts * probabilityOfFirstSuccessfulAttempt);
}
AlbaNumber getComplementOfProbability(AlbaNumber const& probability) {
    // The complement of A means the probability that "Event A does not happen".
    // Equation: P(A') = 1-P(A)
    return getCorrectProbability(AlbaNumber(1) - probability);
}

AlbaNumber getUnionOfProbabilitiesOfDisjointEvents(
    AlbaNumber const& probabilityOfEventA, AlbaNumber const& probabilityOfEventB) {
    // The union of A and B means the probability that "Event A OR Event B happen".
    // If events are disjoint, the union of probability is the sum of probabilities of events.
    // Equation if disjoint: P(A∪B) = P(A) + P(B)

    return getCorrectProbability(probabilityOfEventA + probabilityOfEventB);
}

AlbaNumber getUnionOfProbabilities(
    AlbaNumber const& probabilityOfEventA, AlbaNumber const& probabilityOfEventB,
    AlbaNumber const& probabilityOfEventAAndEventB) {
    // The union of A and B means the probability that "Event A OR Event B happen".
    // The union of probability is probabilityOfEventA + probabilityOfEventB - probabilityOfEventAAndEventB.
    // General equation: P(A∪B) = P(A) + P(B) - P(A∩B)

    return getCorrectProbability(probabilityOfEventA + probabilityOfEventB - probabilityOfEventAAndEventB);
}

AlbaNumber getIntersectionOfProbabilitiesOfIndependentEvents(
    AlbaNumber const& probabilityOfEventA, AlbaNumber const& probabilityOfEventB) {
    // The intersection of A and B means the probability that "Event A AND Event B happen".
    // If events are independent, the intersection of probability is the product of probabilities of events.
    // Equation if independent: P(A∩B) = P(A) * P(B)

    // Events A and B are independent if P(A|B) = P(A) and P(B|A) = P(B).
    // This means that the fact that B happens does not change the probability of A, and vice versa.

    return getCorrectProbability(probabilityOfEventA * probabilityOfEventB);
}

AlbaNumber getIntersectionOfProbabilities(
    AlbaNumber const& probabilityOfEventA, AlbaNumber const& probabilityOfEventB,
    AlbaNumber const& probabilityOfEventAAndEventB) {
    // The intersection of A and B means the probability that "Event A AND Event B happen".
    // The intersection of probability is product of probabilityOfEventA and "conditional probability of event B given
    // A" General equation: P(A∩B) = P(A) * P(B|A)

    return getCorrectProbability(
        probabilityOfEventA *
        getConditionalProbabilityOfEventAGivenThatEventBHappened(probabilityOfEventB, probabilityOfEventAAndEventB));
}

AlbaNumber getConditionalProbabilityOfEventAGivenThatEventBHappened(
    AlbaNumber const& probabilityOfEventB, AlbaNumber const& probabilityOfEventAAndEventB) {
    // The conditional probability is the probability of A assuming that B happens.
    // Equation: P(A|B) = P(A∩B) / P(B)

    return getCorrectProbability(probabilityOfEventAAndEventB / probabilityOfEventB);
}

AlbaNumber getExpectedValue(ValueAndProbabilityPairs const& allValueAndProbabilityPairsOfX) {
    // The expected value E[X] indicates the average value of a random variable X.
    // The expected value can be calculated as the summation of P(X=x) * x, where x goes through all possible values of
    // X.

    AlbaNumber result;
    for (ValueAndProbabilityPair const& valueAndProbabilityPair : allValueAndProbabilityPairsOfX) {
        result += valueAndProbabilityPair.first * valueAndProbabilityPair.second;
    }
    return result;
}

AlbaNumber getExpectedValueInUniformDistribution(AlbaNumber const& lowestValue, AlbaNumber const& highestValue) {
    // In a uniform distribution, the random variable X has n possible values a,a+1,...,b and the probability of each
    // value is 1/n. Equation: E[X] = (a+b)/2

    return (lowestValue + highestValue) / 2;
}

AlbaNumber getExpectedValueInBinomialDistribution(
    AlbaNumber const& probabilityOfASingleAttempt, UnsignedInteger const nTries) {
    // In a binomial distribution, n attempts are made and the probability that a single attempt succeeds is p.

    // The expected value of X in a binomial distribution is E[X] = p*n.
    // Equation: E[X] = p*n

    return probabilityOfASingleAttempt * AlbaNumber(static_cast<int>(nTries));
}

AlbaNumber getExpectedValueInGeometricDistribution(AlbaNumber const& probability) {
    // In a geometric distribution, the probability that an attempt succeeds is p, and we continue until the first
    // success happens.

    // The expected value of X in a binomial distribution is E[X] = 1/p.
    // Equation: E[X] = 1/p

    return AlbaNumber(1) / probability;
}

AlbaNumber getNumberOfPeopleForTheBirthdayParadox(AlbaNumber const& propbabilityThatMustBeMet) {
    // How many people must here be in a room before there is a 50% chance that two of them were born on the same day of
    // the year?

    // -> Let n be the number of days for a year.
    // -> Let k be the number of people in the room.
    // -> The probability that one person has a birthday on a day is 1/n.
    // -> We can look at this problem as a complementary of the probability that all birthdays are distinct.
    // ---> The probability that all birthdays are distinct with k people is:
    // -----> P(Bk) = P(Bk-1) * P(Ak | Bk-1)
    // ---> Bk is the probability of all distinct birthdays with k people.
    // ---> Ak is the probability of a birthday from kth person is different from all the previous people (so less than
    // k)
    // -> This expands to:
    // ---> P(Bk) = P(Bk-1) * P(Ak | Bk-1)
    // --->       = P(Bk-2) * P(Ak-1 | Bk-2)  * P(Ak | Bk-1)
    // --->       ...
    // --->       = P(B1) * P(A2|B1) * P(A3|B2) * P(A4|B3) ... P(Ak | Bk-1)
    // --->       = 1 * (n-1)/n * (n-2)/n * (n-3)/n ... (n-k+1/n)
    // --->       = 1 * (1-(1/n)) * 1-(2/n)) * 1-(3/n)) ... (1-((k-1)/n))
    // ---> This is a geometric sum and its becomes harder here to calculate it.
    //
    // -> Let Xij be a random indicator variable for(1<=i<j<=k) suchs that its 1 when its both the birthdays of person i
    // and person j, 0 otherwise.
    // ---> Then the expectation is: E[Xij] = probability of a birthday = 1/n
    // -> Let X be a random variable that counts the number of pairs of individuals having the same birthday, we have:
    // ---> X = summation of from 1 to k-1 for i (summation of from i+1 to k for j ( Xij ) )
    // ---> Then the expectation of X and since X is linear
    // -----> E[X] = summation of from 1 to k-1 for i (summation of from i+1 to k for j ( E[Xij] ) )
    // -----> E[X] = combinations of k taken 2 * E[Xij]
    // -----> E[X] = k*(k-1)/2 * 1/n = k(k-1)/2n
    // -----> Probability = (k^2 - k)/2n
    // -----> 0 = k^2 - k - Probability*2n

    AlbaNumber result(AlbaMathConstants::POSITIVE_INFINITY_DOUBLE_VALUE);

    constexpr auto DAYS_IN_YEAR = 365;
    AlbaNumbers roots =
        getQuadraticRoots(RootType::RealRootsOnly, 1, -1, propbabilityThatMustBeMet * -2 * DAYS_IN_YEAR);
    for (AlbaNumber const& root : roots) {
        if (root > 0 && result > root) {
            result = getIntegerAfterCeilingOfDoubleValue<AlbaNumber::IntDataType>(root.getDouble());
        }
    }

    return result;
}

}  // namespace math

}  // namespace alba