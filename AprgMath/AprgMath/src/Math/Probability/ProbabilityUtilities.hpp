#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>
#include <Math/Types.hpp>

#include <cmath>

namespace alba
{

namespace math
{

AlbaNumber getCorrectProbability(AlbaNumber const& probability);
AlbaNumber getProbability(UnsignedInteger const numberOfDesiredOutcome, UnsignedInteger const totalNumberOfOutcomes);

AlbaNumber getComplementOfProbability(AlbaNumber const& probability);

AlbaNumber getUnionOfProbabilitiesOfDisjointEvents(
        AlbaNumber const& probabilityOfEventA,
        AlbaNumber const& probabilityOfEventB);

AlbaNumber getUnionOfProbabilities(
        AlbaNumber const& probabilityOfEventA,
        AlbaNumber const& probabilityOfEventB,
        AlbaNumber const& probabilityOfEventAAndEventB);

AlbaNumber getIntersectionOfProbabilitiesOfIndependentEvents(
        AlbaNumber const& probabilityOfEventA,
        AlbaNumber const& probabilityOfEventB);

AlbaNumber getIntersectionOfProbabilities(
        AlbaNumber const& probabilityOfEventA,
        AlbaNumber const& probabilityOfEventB,
        AlbaNumber const& probabilityOfEventAAndEventB);

AlbaNumber getConditionalProbabilityOfEventAGivenThatEventBHappened(
        AlbaNumber const& probabilityOfEventB,
        AlbaNumber const& probabilityOfEventAAndEventB);

}

}
