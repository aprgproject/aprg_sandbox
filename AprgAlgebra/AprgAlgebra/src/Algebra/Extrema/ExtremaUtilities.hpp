#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <string>
#include <vector>

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
    std::pair<AlbaNumber, AlbaNumber> minimumInputOutputValues;
    std::pair<AlbaNumber, AlbaNumber> maximumInputOutputValues;
};

struct Extremum
{
    ExtremumType extremumType;
    std::pair<AlbaNumber, AlbaNumber> inputOutputValues;
};

using Extrema=std::vector<Extremum>;

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

bool isDerivativeZeroOnPossibleExtremum(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumberInterval const& interval);

bool isDecreasingAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

bool isIncreasingAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

bool isConcaveDownwardAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

bool isConcaveUpwardAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

bool hasPointOfInflectionAt(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value);

bool isRolleTheoremSatisfied(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c);

AlbaNumbers getInputValuesInIntervalWithSameAsMeanOfInterval(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b);

AlbaNumbers getInputValuesForCauchyMeanValueTheorem(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b);

Extremum getAbsoluteExtremumBasedOnRelativeExtremaOnInterval(
        Extrema const& relativeExtrema,
        AlbaNumberInterval const& interval);

AlbaNumbers getCriticalNumbers(
        Term const& term,
        std::string const& variableName);

AlbaNumbers getInputValuesAtPointsOfInflection(
        Term const& term,
        std::string const& variableName);

MinimumAndMaximum getMinimumAndMaximumAtClosedInterval(
        Term const& term,
        std::string const& variableName,
        AlbaNumberInterval const& closedInterval);

Extrema getRelativeExtrema(
        Term const& term,
        std::string const& variableName);

}

}
