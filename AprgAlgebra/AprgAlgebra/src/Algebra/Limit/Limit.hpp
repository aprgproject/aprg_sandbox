#pragma once

#include <Algebra/Limit/LimitAtAValueApproachType.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace algebra
{

bool isAlmostEqualForLimitIteration(AlbaNumber const& value1, AlbaNumber const& value2);
bool isAlmostEqualForLimitChecking(AlbaNumber const& value1, AlbaNumber const& value2);
bool hasVerticalAsymptoteAtValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);
bool hasHorizontalAsymptoteAtValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);
bool isSqueezeTheoremSatisfied(
        Term const& alwaysLowerTermAtInterval,
        Term const& termInBetweenAtInterval,
        Term const& alwaysHigherTermAtInterval,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);

AlbaNumber getLimitAtAValueByApproachType(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitAtAValueApproachType const limitApproachType);
AlbaNumber getLimitAtAValueInBothSides(
        Term const& term,
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
        AlbaNumber const& input2,
        AlbaNumber const& inputValue,
        AlbaNumber const& output1,
        AlbaNumber const& output2);

Term getLimit(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);

Term getLimitUsingLhopitalsRule(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);

Term getTermUsingLhopitalsRule(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);

void calculateTermAndLimitUsingLhopitalsRule(
        Term & newTerm,
        Term & limitValue,
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);

Term getLimitAtAValueOrInfinity(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach);

Term getLimitAtAValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& value,
        LimitAtAValueApproachType const limitApproachType);

Term simplifyAndGetLimitAtAValue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitAtAValueApproachType const limitApproachType);

Term getLimitAtInfinity(
        Term const& term,
        std::string const& variableName,
        AlbaNumber::Value const infinityValue);

Term getObliqueAsymptote(Term const& term);

bool continueToDifferentiateForLhopitalsRule(
        Term const& numerator,
        Term const& denominator,
        Term const& numeratorValue,
        Term const& denominatorValue);

}

}
