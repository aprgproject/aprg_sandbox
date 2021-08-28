#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace algebra
{

enum class LimitAtAValueApproachType
{
    BothSides,
    PositiveSide,
    NegativeSide
};

bool isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber const& value);
bool hasVerticalAsymptoteAtValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);
bool hasHorizontalAsymptoteAtValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);

AlbaNumber getLimitAtAValueByApproachType(
        Term const& term,        std::string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitAtAValueApproachType const limitApproachType);
AlbaNumber getLimitAtAValueInBothSides(        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);
AlbaNumber getLimitAtAValueInThePositiveSide(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);
AlbaNumber getLimitAtAValueInTheNegativeSide(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);
AlbaNumber getLimitAtAValueByIterationAndLinearInterpolation(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach,
        AlbaNumber const& initialValueForIteration,
        unsigned int maxNumberOfIterations);
AlbaNumber getLimitAtAValueUsingTrendOfValues(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach,
        AlbaNumber const& previousAcceptedInput,
        AlbaNumber const& previousPreviousAcceptedInput);
AlbaNumber getValueUsingLinearInterpolation(
        AlbaNumber const& input1,
        AlbaNumber const& input2,        AlbaNumber const& inputValue,
        AlbaNumber const& output1,
        AlbaNumber const& output2);
Term getLimitAtAValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value,
        LimitAtAValueApproachType const limitApproachType);
Term getLimitAtInfinity(
        Term const& term,
        std::string const& variableName,
        AlbaNumber::Value const infinityValue);

}
}