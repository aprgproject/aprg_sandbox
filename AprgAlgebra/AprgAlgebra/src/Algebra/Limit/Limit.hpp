#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace algebra
{

enum class LimitApproachType
{
    BothSides,
    PositiveSide,
    NegativeSide
};

bool isRejectedLimitValueForDirectSubstitutionAndIterativeMethods(AlbaNumber const& value);
AlbaNumber getLimitValueByApproachType(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitApproachType const limitApproachType);
AlbaNumber getLimitInBothSides(
        Term const& term,
        std::string const& variableName,        AlbaNumber const& valueToApproach);
AlbaNumber getLimitInPositiveSide(
        Term const& term,
        std::string const& variableName,        AlbaNumber const& valueToApproach);
AlbaNumber getLimitInNegativeSide(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);
AlbaNumber getLimitByIterationAndLinearInterpolation(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach,
        AlbaNumber const& initialValueForIteration,
        unsigned int maxNumberOfIterations);
AlbaNumber getLimitValue(
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
Term getLimitAsItApproachesAValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value,
        LimitApproachType const limitApproachType);

}
}