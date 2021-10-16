#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <string>
#include <utility>

namespace alba
{

namespace algebra
{

enum class ExtremumType
{
    Maximum,
    Minimum
};

struct MinimumAndMaximum
{
    std::pair<AlbaNumber, AlbaNumber> minimumInputOutput;
    std::pair<AlbaNumber, AlbaNumber> maximumInputOutput;
};

bool willYieldToAbsoluteMinimumValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation);

bool willYieldToAbsoluteMaximumValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation);

bool willYieldToRelativeMinimumValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& minimumValueToTest,
        AlbaNumberInterval const& openInterval);

bool willYieldToRelativeMaximumValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumberInterval const& openInterval);

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

AlbaNumbers getCriticalNumbers(
        Term const& term,
        std::string const& variableName);

MinimumAndMaximum getMinimumAndMaximumAtClosedInterval(
        Term const& term,
        std::string const& variableName,
        AlbaNumberInterval const& closedInterval);

void putArbitiaryValuesBasedFromDomainOfTerm(
        AlbaNumbers & arbitiaryValues,
        Term const& term);

void putArbitiaryValuesFromInterval(
        AlbaNumbers & arbitiaryValues,
        AlbaNumberInterval const& interval);

}

}
