#include "Differentiation.hpp"

#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

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
    Term derivativeExpression(getDerivativeByDefinition(term, variableName, Term(variableName)));
    SubstitutionOfVariablesToValues substitution{{variableName, value}};
    Term derivativeConstant(substitution.performSubstitutionTo(derivativeExpression));
    if(derivativeConstant.isConstant())
    {
        result = derivativeConstant.getConstantValueConstReference().isARealFiniteValue();
    }
    return result;
}

Term getDerivativeByDefinition(
        Term const& term,
        string const& variableName,
        Term const& x)
{
    Term result;

    string const& deltaXName("deltaX");
    Term deltaX(deltaXName);
    Term xPlusDeltaX(createExpressionIfPossible({x, Term("+"), deltaX}));
    SubstitutionOfVariablesToTerms substitution{{variableName, xPlusDeltaX}};
    Term fOfXPlusDeltaX(substitution.performSubstitutionTo(term));
    substitution.putVariableWithTerm(variableName, x);
    Term fOfX(substitution.performSubstitutionTo(term));
    Term derivativeDefinition(createExpressionIfPossible({Term("("), fOfXPlusDeltaX, Term("-"), fOfX, Term(")"), Term("/"), deltaX}));
    simplifyDerivativeByDefinition(derivativeDefinition);

    Term limitAtPositiveSide(simplifyAndGetLimitAtAValue(derivativeDefinition, deltaXName, 0, LimitAtAValueApproachType::PositiveSide));
    Term limitAtNegativeSide(simplifyAndGetLimitAtAValue(derivativeDefinition, deltaXName, 0, LimitAtAValueApproachType::NegativeSide));
    if(limitAtPositiveSide.isConstant() && limitAtNegativeSide.isConstant())
    {
        if(limitAtPositiveSide.getConstantValueConstReference().isPositiveOrNegativeInfinity()
                && limitAtPositiveSide.getConstantValueConstReference().isPositiveOrNegativeInfinity())
        {
            result = x;
        }
        else if(limitAtPositiveSide != limitAtNegativeSide)
        {
            result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
        }
        else
        {
            result = limitAtPositiveSide;
        }
    }
    else
    {
        result = limitAtPositiveSide;
    }
    return result;
}

void simplifyDerivativeByDefinition(Term & term)
{
    SimplificationOfExpression::ConfigurationDetails rationalizeConfigurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    rationalizeConfigurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    rationalizeConfigurationDetails.shouldSimplifyByRationalizingNumerator = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(rationalizeConfigurationDetails);
    term.simplify();
}

}

}
