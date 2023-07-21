#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>
#include <Math/Types.hpp>

#include <cmath>

namespace alba {

namespace math {

using ValueAndProbabilityPair = std::pair<AlbaNumber, AlbaNumber>;
using ValueAndProbabilityPairs = std::vector<ValueAndProbabilityPair>;

bool doesExpectedValuesHaveLinearity(
    ValueAndProbabilityPairs const& firstSetOfValueAndProbabilityPairsOfX,
    ValueAndProbabilityPairs const& secondSetOfValueAndProbabilityPairsOfX);

AlbaNumber getCorrectProbability(AlbaNumber const& probability);

AlbaNumber getProbability(UnsignedInteger const numberOfDesiredOutcome, UnsignedInteger const totalNumberOfOutcomes);
AlbaNumber getProbabilityOnBinomialDistribution(
    AlbaNumber const& probabilityOfASingleAttempt, UnsignedInteger const xTarget, UnsignedInteger const nTries);
AlbaNumber getProbabilityOnGeometricDistribution(
    AlbaNumber const& probabilityOfASingleAttempt, UnsignedInteger const xTarget);

AlbaNumber getComplementOfProbability(AlbaNumber const& probability);
AlbaNumber getUnionOfProbabilitiesOfDisjointEvents(
    AlbaNumber const& probabilityOfEventA, AlbaNumber const& probabilityOfEventB);
AlbaNumber getUnionOfProbabilities(
    AlbaNumber const& probabilityOfEventA, AlbaNumber const& probabilityOfEventB,
    AlbaNumber const& probabilityOfEventAAndEventB);
AlbaNumber getIntersectionOfProbabilitiesOfIndependentEvents(
    AlbaNumber const& probabilityOfEventA, AlbaNumber const& probabilityOfEventB);
AlbaNumber getIntersectionOfProbabilities(
    AlbaNumber const& probabilityOfEventA, AlbaNumber const& probabilityOfEventB,
    AlbaNumber const& probabilityOfEventAAndEventB);
AlbaNumber getConditionalProbabilityOfEventAGivenThatEventBHappened(
    AlbaNumber const& probabilityOfEventB, AlbaNumber const& probabilityOfEventAAndEventB);

AlbaNumber getExpectedValue(ValueAndProbabilityPairs const& allValueAndProbabilityPairsOfX);
AlbaNumber getExpectedValueInUniformDistribution(AlbaNumber const& lowestValue, AlbaNumber const& highestValue);
AlbaNumber getExpectedValueInBinomialDistribution(
    AlbaNumber const& probabilityOfASingleAttempt, UnsignedInteger const nTries);
AlbaNumber getExpectedValueInGeometricDistribution(AlbaNumber const& probability);

AlbaNumber getNumberOfPeopleForTheBirthdayParadoxUsingQuadraticFormula(AlbaNumber const& propbabilityThatMustBeMet);
AlbaNumber getNumberOfPeopleForTheBirthdayParadoxUsingTaylorFormula(AlbaNumber const& propbabilityThatMustBeMet);

}  // namespace math
}  // namespace alba