#include "IntegrationUtilities.hpp"

#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

bool isTheIntegralDefinitionForFiniteCalculusIsTrue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b)
{
    // The fundamental theorem of finite calculus:

    // The discrete definite integral from a to b is equal to
    // The summation of terms from a to b-1.
    IntegrationForFiniteCalculus integration(variableName);
    Summation summation(term, variableName);
    return integration.integrateWithDefiniteValues(term, a, b) == summation.getSum(Term(a), Term(b-1));
}

Term solveADefiniteIntegral(
        Term const& integratedTerm,
        string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue)
{
    SubstitutionOfVariablesToValues substitution({{variableName, lowerValue}});
    Term integralWithLowerValue(substitution.performSubstitutionTo(integratedTerm));
    substitution.putVariableWithValue(variableName, higherValue);
    Term integralWithHigherValue(substitution.performSubstitutionTo(integratedTerm));
    return integralWithHigherValue-integralWithLowerValue;
}

}

}
