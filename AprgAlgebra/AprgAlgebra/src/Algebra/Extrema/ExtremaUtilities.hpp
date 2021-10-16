#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <string>

namespace alba
{

namespace algebra
{

enum class ExtremumType
{
    Maximum,
    Minimum
};

bool willYieldToAbsoluteMaximumValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation);

bool willYieldToAbsoluteMinimumValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation);

bool willYieldToRelativeMaximumValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumberInterval const& interval);

bool willYieldToRelativeMinimumValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& minimumValueToTest,
        AlbaNumberInterval const& interval);

bool willYieldToExtremumValue(
        ExtremumType const extremumType,
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumbers const& valuesUsedForChecking);

bool isDerivativeZeroOnExtremum(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumberInterval const& interval);

void putArbitiaryValuesBasedFromDomainOfTerm(
        AlbaNumbers & valuesUsedForChecking,
        Term const& term);

void putArbitiaryValuesFromInterval(
        AlbaNumbers & values,
        AlbaNumberInterval const& interval);

}

}
