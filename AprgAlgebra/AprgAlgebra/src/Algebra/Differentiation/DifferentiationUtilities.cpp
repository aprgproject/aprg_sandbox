#include "DifferentiationUtilities.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
using namespace alba::algebra::DomainAndRange;
using namespace alba::algebra::Simplification;
using namespace std;

namespace
{

constexpr char const*const X_NAME = "x";
constexpr char const*const DELTA_X_NAME = "deltaX";

}

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
    Term derivative(getDerivativeAtUsingLimit(term, variableName, Term("x"), LimitAtAValueApproachType::BothSides));
    SubstitutionOfVariablesToValues substitution{{"x", value}};
    Term derivativeValue(substitution.performSubstitutionTo(derivative));
    if(derivativeValue.isConstant())
    {
        result = derivativeValue.getConstantValueConstReference().isARealFiniteValue();
    }
    return result;
}

Term getDerivativeAtUsingLimit(
        Term const& term,
        string const& variableName,
        Term const& termSubstituteToBack,
        LimitAtAValueApproachType const approachType)
{
    string const& deltaXName(DELTA_X_NAME);
    Term derivativeDefinition(getDerivativeDefinition(term, variableName));
    SubstitutionOfVariablesToTerms substitution{{X_NAME, termSubstituteToBack}};
    Term derivativeAfterSubstitution(substitution.performSubstitutionTo(derivativeDefinition));
    return simplifyAndGetLimitAtAValue(derivativeAfterSubstitution, deltaXName, 0, approachType);
}

Term getDerivativeDefinition(
        Term const& term,
        string const& variableName)
{
    Term x(X_NAME);
    Term deltaX(DELTA_X_NAME);
    Term xPlusDeltaX(createExpressionIfPossible({x, Term("+"), deltaX}));
    SubstitutionOfVariablesToTerms substitution{{variableName, xPlusDeltaX}};
    Term fOfXPlusDeltaX(substitution.performSubstitutionTo(term));
    substitution.putVariableWithTerm(variableName, x);
    Term fOfX(substitution.performSubstitutionTo(term));
    Term derivativeDefinition(createExpressionIfPossible({Term("("), fOfXPlusDeltaX, Term("-"), fOfX, Term(")"), Term("/"), deltaX}));
    simplifyDerivativeByDefinition(derivativeDefinition);

    return derivativeDefinition;
}

void simplifyDerivativeByDefinition(Term & term)
{
    SimplificationOfExpression::ConfigurationDetails rationalizeConfigurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    rationalizeConfigurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    rationalizeConfigurationDetails.shouldSimplifyByRationalizingNumerator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(rationalizeConfigurationDetails);

    term.simplify();
}

SolutionSet getDifferentiabilityDomain(
        Term const& term,
        string const& variableName)
{
    // This code is not accurate.
    // How about piecewise function?
    // How about absolute value function?

    Differentiation differentiation(variableName);
    Term derivativeTerm(differentiation.differentiate(term));
    return calculateDomainForTermWithOneVariable(derivativeTerm);
}

}
}
