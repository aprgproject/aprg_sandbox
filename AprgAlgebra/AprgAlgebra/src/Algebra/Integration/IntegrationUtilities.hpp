#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Utilities/LowerAndHigherValues.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <string>

namespace alba
{

namespace algebra
{

bool isTheSecondFundamentalTheoremOfCalculusTrue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b);

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
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval);

Term getAverageValueInBetweenTwoValues(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval);

Term getAverageValueInBetweenTwoValues(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval);

Term substituteValuesAndGetDifference(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval);

Term substituteTermsAndGetDifference(
        Term const& term,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm);

Term getAreaUnderACurveUsingReimannSums(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval);

LowerAndHigherValues getApproximateValueForDefiniteIntegral(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval);
}

}
