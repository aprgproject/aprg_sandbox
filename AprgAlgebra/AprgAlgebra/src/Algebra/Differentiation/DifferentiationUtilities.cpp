#include "DifferentiationUtilities.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Retrieval/SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace alba::algebra::DomainAndRange;
using namespace alba::algebra::Functions;
using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;
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

bool isTheFirstFundamentalTheoremOfCalculusTrue(
        Term const& term,
        string const& variableName)
{
    // The first fundamental theorem of calculus
    // Let the function f be continuous on the closed interval [a, b] and let x be any number in [a, b].
    // If F is the definite integral of f from a to x then the derivative of F at x is equal to f at x.

    Integration integration(variableName);
    Differentiation differentiation(variableName);
    Term capitalF(integration.integrate(term));
    Term derivativeOfCapitalF(differentiation.differentiate(capitalF));
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();
    return derivativeOfCapitalF == simplifiedTerm;
}

bool isDifferentiableAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    bool result(false);
    Differentiation differentiation(variableName);
    Term derivative(differentiation.differentiate(term));
    SubstitutionOfVariablesToValues substitution{{"x", value}};
    Term derivativeValue(substitution.performSubstitutionTo(derivative));
    if(derivativeValue.isConstant())
    {
        result = derivativeValue.getConstantValueConstReference().isARealFiniteValue();
    }
    return result;
}

bool isDifferentiableAtUsingDerivativeDefinition(
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

bool isFirstOrderDifferentialEquation(
        Term const& dyOverDx,
        Term const& p,
        Term const& q,
        string const& xVariableName,
        string const& yVariableName)
{
    // First order differential equation should follow this:
    // dy/dx = P(x)*y + Q(x)

    bool result(false);
    DerivativeVariableName derivativeVariableName(1, xVariableName, yVariableName);
    Term remainingTermWithoutDyOverDx = dyOverDx/Term(derivativeVariableName.getNameInLeibnizNotation());
    remainingTermWithoutDyOverDx.simplify();
    if(Term(1) == remainingTermWithoutDyOverDx)
    {
        VariableNamesRetriever retriever;
        retriever.retrieveFromTerm(p);
        VariableNamesSet const& namesFromP(retriever.getSavedData());
        if(namesFromP.find(yVariableName) != namesFromP.cend())
        {
            VariableNamesRetriever retriever;
            retriever.retrieveFromTerm(q);
            VariableNamesSet const& namesFromQ(retriever.getSavedData());
            if(namesFromQ.find(xVariableName) != namesFromQ.cend())
            {
                result = true;
            }
        }
    }
    return result;
}

Term evaluateAtDefiniteValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    SubstitutionOfVariablesToValues substitution{{variableName, value}};
    return substitution.performSubstitutionTo(term);
}

Term evaluateAtDefiniteTerm(
        Term const& term,
        string const& variableName,
        Term const& valueTerm)
{
    SubstitutionOfVariablesToTerms substitution{{variableName, valueTerm}};
    return substitution.performSubstitutionTo(term);
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

Term getDerivativeDefinitionForFiniteCalculus(
        Term const& term,
        string const& variableName)
{
    // Discrete derivative
    Polynomial variableNamePlusOne{Monomial(1, {{variableName, 1}}), Monomial(1, {})};
    SubstitutionOfVariablesToTerms substitution{{variableName, Term(variableNamePlusOne)}};
    Term discreteDerivativeDefinition(createExpressionIfPossible({substitution.performSubstitutionTo(term), Term("-"), term}));
    discreteDerivativeDefinition.simplify();
    return discreteDerivativeDefinition;
}

Term getLogarithmicDifferentiationToYieldDyOverDx(
        Term const& yInTermsOfX,
        string const& xVariableName,
        string const& yVariableName)
{
    // y = f(x)
    // -> ln(|y|) = ln(|f(x)|)
    // -> Dx(ln(|y|)) = Dx(ln(|f(x)|))
    // -> y'/y = Dx(ln(|f(x)|))
    // -> y' = y * Dx(ln(|f(x)|))
    // -> dy/dx = f(x) * Dx(ln(|f(x)|))

    // dy/dx = f(x) * Dx(ln|f(x)|)
    // if domain is inside positive, then absolute value can be removed
    Term result;
    SolutionSet solutionSet(calculateDomainForEquation(xVariableName, Equation(Term(yVariableName), "=", yInTermsOfX)));
    AlbaNumberIntervals const& domainOfX(solutionSet.getAcceptedIntervals());
    AlbaNumberInterval allPositiveNumbers(createCloseEndpoint(AlbaNumber(0)), createPositiveInfinityOpenEndpoint());
    if(areTheIntervalsInsideTheInterval(domainOfX, allPositiveNumbers))
    {
        Differentiation differentiation(xVariableName);
        Term logarithm(ln(yInTermsOfX));
        logarithm.simplify();
        result = yInTermsOfX * differentiation.differentiate(logarithm);
        simplifyToNonDoubleFactors(result);
    }
    return result;
}

Term getCartesianDerivativeOfTermInPolarCoordinates(
        Term const& radiusInTermsOfTheta,
        string const& thetaName)
{
    // dy/dx = (dr/dt*sin(t) + r(t)*cos(t)) / (dr/dt*cos(t) - r(t)*sin(t))
    Term theta(thetaName);
    Differentiation differentiation(thetaName);
    Term drOverDTheta(differentiation.differentiate(radiusInTermsOfTheta));
    Term sinTheta(sin(theta));
    Term cosTheta(cos(theta));
    Term numerator(createExpressionIfPossible({drOverDTheta, Term("*"), sinTheta, Term("+"), radiusInTermsOfTheta, Term("*"), cosTheta}));
    Term denominator(createExpressionIfPossible({drOverDTheta, Term("*"), cosTheta, Term("-"), radiusInTermsOfTheta, Term("*"), sinTheta}));
    Term result(createExpressionIfPossible({numerator, Term("/"), denominator}));
    result.simplify();
    return result;
}

Term getSlopeOfTermInPolarCoordinates(
        Term const& radiusInTermsOfTheta,
        string const& thetaName,
        AlbaNumber const& thetaValue)
{
    Term dyOverDx(getCartesianDerivativeOfTermInPolarCoordinates(radiusInTermsOfTheta, thetaName));
    SubstitutionOfVariablesToValues substitution{{thetaName, thetaValue}};
    return substitution.performSubstitutionTo(dyOverDx);
}

Term getApproximationUsingTaylorsFormula(
        Term const& term,
        string const& variableName,
        Term const& startingValue,
        Term const& valueToApproach,
        unsigned int const numberOfTimes)
{
    // taylors formula:
    // f(b) = f(a) + f'(a)*(b-a)/1! + f''(a)*(b-a)^2/2! ...
    Differentiation differentiation(variableName);
    Term difference(valueToApproach-startingValue);
    Term currentDerivative(term);
    Term differenceRaiseToPower(1);
    AlbaNumber factorialValue(1);
    Term result(evaluateAtDefiniteTerm(term, variableName, startingValue));
    for(unsigned int n=1; n<=numberOfTimes; n++)
    {
        currentDerivative = differentiation.differentiate(currentDerivative);
        differenceRaiseToPower *= difference;
        factorialValue *= n;
        Term currentDerivativeValue(evaluateAtDefiniteTerm(currentDerivative, variableName, startingValue));
        Term currentTerm(currentDerivativeValue * differenceRaiseToPower / factorialValue);
        result += currentTerm;
    }
    result.simplify();
    return result;
}

Term getApproximationUsingTaylorsRemainder(
        Term const& term,
        string const& variableName,
        Term const& startingValue,
        Term const& valueToApproach,
        Term const& valueForEstimation,
        unsigned int const numberOfTimes)
{
    // taylors formula:
    // R(x) = f(n+1)(E) * (x-a)^(n+1) / (n+1)!
    // E or valueForEstimation should be between startingValue and valueToApproach
    Differentiation differentiation(variableName);
    Term difference(valueToApproach-startingValue);
    unsigned int nPlusOne = numberOfTimes+1;
    Term derivative(differentiation.differentiateMultipleTimes(term, nPlusOne));
    Term derivativeValue(evaluateAtDefiniteTerm(derivative, variableName, valueForEstimation));
    Term differenceRaiseToPower(difference^(nPlusOne));
    Term factorialValue(getFactorial(nPlusOne));
    Term result(derivativeValue*differenceRaiseToPower/factorialValue);
    result.simplify();
    return result;
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

Equation getRelationshipOfDerivativeOfTheInverseAndTheDerivative(
        Term const& term,
        string const& variableName,
        string const& variableForNonInverse,
        string const& variableForInverse)
{
    // Suppose the function f is continuous and monotonic on a closed interval [a, b] containing the number c, and let f(c) = d.
    // If f'(c) exists and f'(c) != 0, then (f-1)'(d) exists then:
    // The relationship of the derivatives is (f-1)'(d) = 1/f'(c)

    Differentiation differentiation(variableName);
    Term inverseOfTerm(invertTerm(term, variableName));
    Term derivative(differentiation.differentiate(term));
    Term derivativeOfInverse(differentiation.differentiate(inverseOfTerm));
    SubstitutionOfVariablesToTerms substitution{{variableName, Term(variableForNonInverse)}};
    Term derivativeWithNewVariable(substitution.performSubstitutionTo(derivative));
    substitution.putVariableWithTerm(variableName, Term(variableForInverse));
    Term derivativeOfInverseWithNewVariable(substitution.performSubstitutionTo(derivativeOfInverse));
    Term oneOverDerivativeWithNewVariable(createExpressionIfPossible({Term(1), Term("/"), derivativeWithNewVariable}));
    derivativeOfInverseWithNewVariable.simplify();
    oneOverDerivativeWithNewVariable.simplify();
    return Equation(derivativeOfInverseWithNewVariable, "=", oneOverDerivativeWithNewVariable);
}

Equation getIntegralEquationForFirstOrderDifferentialEquation(
        Equation const& equation,
        string const& xVariableName,
        string const& yVariableName)
{
    Equation result;
    DerivativeVariableName derivativeVariableName(1, xVariableName, yVariableName);
    string derivativeName(derivativeVariableName.getNameInLeibnizNotation());
    IsolationOfOneVariableOnEqualityEquation isolation(equation);
    Term termWithDerivative;
    Term termWithoutDerivative;
    isolation.isolateTermWithVariable(derivativeName, termWithDerivative, termWithoutDerivative);
    SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever retriever;
    retriever.putVariableNamesToCheckInOrder({derivativeName, yVariableName});
    retriever.retrieveFromTerm(termWithoutDerivative);
    SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::VariableNameToExpressionMap const& variableNameToExpressionMap(
                retriever.getVariableNameToExpressionMap());
    Term dyOverDx = termWithDerivative;
    Term p = -Term(variableNameToExpressionMap.at(yVariableName));
    Term q = retriever.getRemainingTermsExpression();

    dyOverDx.simplify();
    p.simplify();
    q.simplify();
    if(isFirstOrderDifferentialEquation(dyOverDx, p, q, xVariableName, yVariableName))
    {
        result = getIntegralEquationForFirstOrderDifferentialEquation(p, q, xVariableName, yVariableName);
    }
    return result;
}

Equation getIntegralEquationForFirstOrderDifferentialEquation(
        Term const& p,
        Term const& q,
        string const& xVariableName,
        string const& yVariableName)
{
    // First order differential equation should follow this:
    // dy/dx = P(x)*y + Q(x)

    Integration integration(xVariableName);
    Term integralOfP(integration.integrate(p));
    Term eToTheIntegralOfP(createExpressionIfPossible({getEAsTerm(), Term("^"), integralOfP}));
    Term eToTheNegativeIntegralOfP(createExpressionIfPossible({getEAsTerm(), Term("^"), -integralOfP}));
    Term qWithoutY(q/Term(yVariableName));
    Term qExpression(createExpressionIfPossible({qWithoutY, Term("*"), eToTheIntegralOfP}));
    Term cExpression(createExpressionIfPossible({getEAsTerm(), Term("*"), eToTheNegativeIntegralOfP}));
    Term integralOfQExpression(integration.integrate(qExpression));
    Term qcExpression(createExpressionIfPossible({integralOfQExpression, Term("+"), cExpression}));
    Term pqcExpression(createExpressionIfPossible({eToTheNegativeIntegralOfP, Term("*"), qcExpression}));
    return Equation(Term(yVariableName), "=", pqcExpression);
}

void simplifyDerivativeByDefinition(Term & term)
{
    SimplificationOfExpression::ConfigurationDetails rationalizeConfigurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    rationalizeConfigurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    rationalizeConfigurationDetails.shouldSimplifyByRationalizingNumerator = true;
    rationalizeConfigurationDetails.shouldSimplifyToFactors = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(rationalizeConfigurationDetails);

    term.simplify();
}

void simplifyToNonDoubleFactors(
        Term& term)
{
    simplifyTermByFactoringToNonDoubleFactors(term);
}


}

}
