#include "Differentiation.hpp"

#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

constexpr char const*const DELTA_X_NAME = "deltaX";

namespace alba
{
namespace algebra
{
bool isDifferentiableAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    bool result(false);
    Term derivativeDefinition(getDerivativeDefinition(term, variableName, Term(variableName)));
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(DELTA_X_NAME, 0);
    Term derivativeDefinitionWithDeltaZero(substitution.performSubstitutionTo(derivativeDefinition));
    substitution.putVariableWithValue(variableName, value);
    Term derivativeValue(substitution.performSubstitutionTo(derivativeDefinitionWithDeltaZero));
    if(derivativeValue.isConstant())
    {
        result = derivativeValue.getConstantValueConstReference().isARealFiniteValue();
    }
    return result;
}

Term getDerivativeUsingLimit(
        Term const& term,
        string const& variableName,
        Term const& x,
        LimitAtAValueApproachType const approachType)
{
    string const& deltaXName("deltaX");
    Term derivativeDefinition(getDerivativeDefinition(term, variableName, x));
    return simplifyAndGetLimitAtAValue(derivativeDefinition, deltaXName, 0, approachType);
}

Term getDerivativeDefinition(
        Term const& term,
        string const& variableName,
        Term const& x)
{
    Term deltaX(DELTA_X_NAME);
    Term xPlusDeltaX(createExpressionIfPossible({x, Term("+"), deltaX}));
    SubstitutionOfVariablesToTerms substitution{{variableName, xPlusDeltaX}};
    Term fOfXPlusDeltaX(substitution.performSubstitutionTo(term));    substitution.putVariableWithTerm(variableName, x);
    Term fOfX(substitution.performSubstitutionTo(term));
    Term derivativeDefinition(createExpressionIfPossible({Term("("), fOfXPlusDeltaX, Term("-"), fOfX, Term(")"), Term("/"), deltaX}));
    simplifyDerivativeByDefinition(derivativeDefinition);

    return derivativeDefinition;
}

void simplifyDerivativeByDefinition(Term & term){
    SimplificationOfExpression::ConfigurationDetails rationalizeConfigurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    rationalizeConfigurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;    rationalizeConfigurationDetails.shouldSimplifyByRationalizingNumerator = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(rationalizeConfigurationDetails);
    term.simplify();
}

}

}
