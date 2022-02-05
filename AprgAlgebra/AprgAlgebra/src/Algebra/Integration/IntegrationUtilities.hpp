#pragma once

#include <Algebra/Integration/DetailsForDefiniteIntegralWithTerms.hpp>
#include <Algebra/Integration/DetailsForDefiniteIntegralWithValues.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Utilities/LowerAndHigherValues.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

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
        AlbaNumber const& lowerEndInInterval,
        AlbaNumber const& higherEndInInterval);

Term getAverageValueInBetweenTwoValues(
        Term const& term,
        DetailsForDefiniteIntegralWithValues const& integralDetails);

Term evaluateValuesAndGetDifference(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerEnd,
        AlbaNumber const& higherEnd);

Term evaluateTermsAndGetDifference(
        Term const& term,
        std::string const& variableName,
        Term const& lowerEnd,
        Term const& higherEnd);

Term evaluate(
        Term const& term,
        std::string const& variableName,
        Term const& value);

Term getAreaUnderACurveUsingReimannSums(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerEndInInterval,
        AlbaNumber const& higherEndInInterval);

LowerAndHigherValues getApproximateValuesForDefiniteIntegral(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& lowerEndInInterval,
        AlbaNumber const& higherEndInInterval);
}

}
