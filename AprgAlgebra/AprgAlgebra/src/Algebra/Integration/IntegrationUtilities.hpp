#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <string>

namespace alba
{

namespace algebra
{

struct LowerAndHigherValues
{
    AlbaNumber lowerValue;
    AlbaNumber higherValue;
};

bool isTheIntegralDefinitionForFiniteCalculusIsTrue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b);

bool isAreaUnderTheCurveEqualToDefiniteIntegral(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b);

AlbaNumbers getInputForAverageValueInBetweenTwoValues(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue);

Term getAverageValueInBetweenTwoValues(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue);

Term getAverageValueInBetweenTwoValues(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue);

Term substituteValuesAndGetDifference(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue);

Term getAreaUnderACurveUsingReimannSums(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue);

LowerAndHigherValues getApproximateValueForDefiniteIntegral(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue);
}

}
