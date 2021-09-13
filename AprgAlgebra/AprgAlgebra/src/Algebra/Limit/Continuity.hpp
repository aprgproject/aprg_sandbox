#pragma once

#include <Algebra/Limit/LimitAtAValueApproachType.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace algebra
{

enum class ContinuityType
{
    Unknown,
    ContinuousAtBothSides,
    DiscontinuousWithRemovableDiscontinuity,
    DiscontinuousWithEssentialDiscontinuity
};

bool isContinuousAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value,
        LimitAtAValueApproachType const limitApproachType);

bool isIntermediateValueTheoremSatisfied(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& firstValue,
        AlbaNumber const& secondValue,
        AlbaNumber const& valueToTest);

ContinuityType getContinuityTypeAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

SolutionSet getContinuityDomain(
        Term const& term);

}

}
