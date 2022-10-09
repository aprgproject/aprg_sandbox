#include "Differentiation.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace alba::algebra::Functions;
using namespace alba::algebra::Simplification;
using namespace std;

namespace alba
{
namespace algebra
{

Differentiation::Differentiation(
        string const& nameOfVariableToDifferentiate)
    : m_nameOfVariableToDifferentiate(nameOfVariableToDifferentiate)
{}

Differentiation::Differentiation(
        string const& nameOfVariableToDifferentiate,
        VariableNamesSet const& namesOfDependentVariables)
    : m_nameOfVariableToDifferentiate(nameOfVariableToDifferentiate)
    , m_namesOfDependentVariables(namesOfDependentVariables)
{}

Term Differentiation::differentiate(
        Term const& term) const
{
    Term result;
    if(term.isConstant())
    {
        result = differentiate(term.getConstantConstReference());
    }
    else if(term.isVariable())
    {
        result = differentiate(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        result = differentiate(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = differentiate(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = differentiate(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        result = differentiate(term.getFunctionConstReference());
    }
    return result;
}

Term Differentiation::differentiate(
        Constant const& constant) const
{
    return differentiateConstant(constant);
}

Term Differentiation::differentiate(
        Variable const& variable) const
{
    Term result(differentiateVariable(variable));
    result.simplify();
    return result;
}

Term Differentiation::differentiate(
        Monomial const& monomial) const
{
    Term result(differentiateMonomial(monomial));
    result.simplify();
    return result;
}

Term Differentiation::differentiate(
        Polynomial const& polynomial) const
{
    Term result(differentiatePolynomial(polynomial));
    result.simplify();
    return result;
}

Term Differentiation::differentiate(
        Expression const& expression) const
{
    return differentiateExpression(expression);
}

Term Differentiation::differentiate(
        Function const& functionObject) const
{
    return differentiateFunction(functionObject);
}

Equation Differentiation::differentiate(
        Equation const& equation) const
{
    return differentiateEquation(equation);
}

Term Differentiation::differentiateWithDefiniteValue(
        Term const& term,
        AlbaNumber const& value) const
{
    return evaluateAtDefiniteValue(differentiate(term), m_nameOfVariableToDifferentiate, value);
}

Term Differentiation::differentiateMultipleTimes(
        Term const& term,
        unsigned int const numberOfTimes) const
{
    Term currentResult(term);
    for(unsigned int i=0; i<numberOfTimes; i++)
    {
        currentResult = differentiate(currentResult);
    }
    return currentResult;
}

Equation Differentiation::differentiateMultipleTimes(
        Equation const& equation,
        unsigned int const numberOfTimes) const
{
    Equation currentResult(equation);
    for(unsigned int i=0; i<numberOfTimes; i++)
    {
        currentResult = differentiate(currentResult);
    }
    return currentResult;
}

AlbaNumber Differentiation::differentiateConstant(
        Constant const&) const
{
    return 0;
}

Monomial Differentiation::differentiateVariable(
        Variable const& variable) const
{
    Monomial result;
    string const& nameOfVariable(variable.getVariableName());
    DerivativeVariableName derivativeVariableName(nameOfVariable);
    if(isVariableToDifferentiate(nameOfVariable))
    {
        result = Monomial(1, {});
    }
    else if(isDependentVariable(nameOfVariable))
    {
        DerivativeVariableName derivativeOfDependentVariableName(1U, m_nameOfVariableToDifferentiate, nameOfVariable);
        result = Monomial(1, {{derivativeOfDependentVariableName.getNameInLeibnizNotation(), 1}});
    }
    else if(isDerivativeVariableNameAndAffectedByThisDifferentiation(derivativeVariableName))
    {
        derivativeVariableName.differentiate();
        result = Monomial(1, {{derivativeVariableName.getNameInLeibnizNotation(), 1}});
    }
    else
    {
        result = Monomial(0, {});
    }
    return result;
}

Polynomial Differentiation::differentiateMonomial(
        Monomial const& monomial) const
{
    Monomial nonChangingVariablesAndConstant;
    Monomial changingVariables;

    separateNonChangingAndChangingVariables(nonChangingVariablesAndConstant, changingVariables, monomial);
    Polynomial result(differentiateMonomialWithChangingVariables(changingVariables));
    result.multiplyMonomial(nonChangingVariablesAndConstant);
    result.simplify();

    return result;
}

Polynomial Differentiation::differentiatePolynomial(
        Polynomial const& polynomial) const
{
    Polynomial result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result.addPolynomial(differentiateMonomial(monomial));
    }
    result.simplify();
    return result;
}

Term Differentiation::differentiateExpression(
        Expression const& expression) const
{
    Term result(differentiateAsTermOrExpressionIfNeeded(expression));
    simplifyForDifferentiation(result);
    return result;
}

Term Differentiation::differentiateFunction(
        Function const& functionObject) const
{
    Term derivativeOfFunctionOnly(differentiateFunctionOnly(functionObject));
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    Term derivativeOfInputTermOfFunction(differentiate(inputTerm));
    Term result(createExpressionIfPossible({derivativeOfFunctionOnly, "*", derivativeOfInputTermOfFunction}));
    simplifyForDifferentiation(result);
    return result;
}

Equation Differentiation::differentiateEquation(
        Equation const& equation) const
{
    Equation result(
                differentiate(equation.getLeftHandTerm()),
                equation.getEquationOperator().getOperatorString(),
                differentiate(equation.getRightHandTerm()));
    result.simplify();
    return result;
}

Term Differentiation::differentiateTwoMultipliedTerms(
        Term const& term1,
        Term const& term2) const
{
    Term term1Derivative(differentiate(term1));
    Term term2Derivative(differentiate(term2));
    Expression firstPart(createExpressionIfPossible({term1, "*", term2Derivative}));
    Expression secondPart(createExpressionIfPossible({term2, "*", term1Derivative}));
    return createExpressionIfPossible({firstPart, "+", secondPart});
}

Term Differentiation::differentiateTwoDividedTerms(
        Term const& numerator,
        Term const& denominator) const
{
    Term numeratorDerivative(differentiate(numerator));
    Term denominatorDerivative(differentiate(denominator));
    Expression resultNumeratorPart1(createExpressionIfPossible({denominator, "*", numeratorDerivative}));
    Expression resultNumeratorPart2(createExpressionIfPossible({numerator, "*", denominatorDerivative}));
    Expression resultNumerator(createExpressionIfPossible({resultNumeratorPart1, "-", resultNumeratorPart2}));
    Expression resultDenominator(createExpressionIfPossible({denominator, "^", 2}));
    return createExpressionIfPossible({resultNumerator, "/", resultDenominator});
}

void Differentiation::separateNonChangingAndChangingVariables(
        Monomial & nonChangingVariablesAndConstant,
        Monomial & changingVariables,
        Monomial const& monomial) const
{
    nonChangingVariablesAndConstant = Monomial(monomial.getConstantConstReference(), {});
    changingVariables = Monomial(1, {});
    for(auto const& variableExponentPair :
        monomial.getVariablesToExponentsMapConstReference())
    {
        string const& variableName(variableExponentPair.first);
        AlbaNumber const& exponent(variableExponentPair.second);
        if(exponent != 0)
        {
            if(isChangingVariableName(variableName))
            {
                changingVariables.putVariableWithExponent(variableName, exponent);
            }
            else
            {
                nonChangingVariablesAndConstant.putVariableWithExponent(variableName, exponent);
            }
        }
    }
}

Polynomial Differentiation::differentiateMonomialWithChangingVariables(
        Monomial const& changingVariables) const
{
    Polynomial result;
    for(auto const& variableExponentPair :
        changingVariables.getVariablesToExponentsMapConstReference())
    {
        string const& variableName(variableExponentPair.first);
        AlbaNumber const& exponent(variableExponentPair.second);
        Monomial monomialToAdd(changingVariables);
        DerivativeVariableName derivativeVariableName(variableName);
        if(isVariableToDifferentiate(variableName))
        {
            monomialToAdd.putVariableWithExponent(variableName, exponent-1);
            monomialToAdd.multiplyNumber(exponent);
        }
        else if(isDependentVariable(variableName))
        {
            monomialToAdd.putVariableWithExponent(variableName, exponent-1);
            monomialToAdd.multiplyNumber(exponent);
            DerivativeVariableName derivativeOfDependentVariableName(1U, m_nameOfVariableToDifferentiate, variableName);
            monomialToAdd.putVariableWithExponent(derivativeOfDependentVariableName.getNameInLeibnizNotation(), 1);
        }
        else if(isDerivativeVariableNameAndAffectedByThisDifferentiation(derivativeVariableName))
        {
            monomialToAdd.putVariableWithExponent(variableName, exponent-1);
            monomialToAdd.multiplyNumber(exponent);
            derivativeVariableName.differentiate();
            monomialToAdd.putVariableWithExponent(derivativeVariableName.getNameInLeibnizNotation(), 1);
        }
        result.addMonomial(monomialToAdd);
    }
    return result;
}

Term Differentiation::differentiateAsTermOrExpressionIfNeeded(
        Expression const& expression) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    Term simplifiedTerm(expression);
    simplifyForDifferentiation(simplifiedTerm);
    if(simplifiedTerm.isExpression())
    {
        result = differentiateSimplifiedExpressionOnly(simplifiedTerm.getExpressionConstReference());
    }
    else
    {
        result = differentiate(simplifiedTerm);
    }
    return result;
}

Term Differentiation::differentiateSimplifiedExpressionOnly(
        Expression const& expression) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        result = differentiateTermsInAdditionOrSubtraction(expression);
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        result = differentiateTermsInMultiplicationOrDivision(expression);
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = differentiateTermsInRaiseToPower(expression);
    }
    return result;
}

Term Differentiation::differentiateTermsInAdditionOrSubtraction(
        Expression const& expression) const
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    Expression accumulatedExpression(createOrCopyExpressionFromATerm(0));
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& currentTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term differentiatedTerm(differentiate(currentTerm));
        if(termWithDetails.hasPositiveAssociation())
        {
            accumulatedExpression.putTermWithAdditionIfNeeded(differentiatedTerm);
        }
        else
        {
            accumulatedExpression.putTermWithSubtractionIfNeeded(differentiatedTerm);
        }
    }
    return accumulatedExpression;
}

Term Differentiation::differentiateTermsInMultiplicationOrDivision(
        Expression const& expression) const
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    Term result(differentiateByProcessingAsPolynomialsOverPolynomials(expression));
    if(result.isEmpty())
    {
        result = differentiateTermsInMultiplicationOrDivisionTermByTerm(termsWithDetails);
    }
    return result;
}

Term Differentiation::differentiateByProcessingAsPolynomialsOverPolynomials(
        Term const& term) const
{
    Term result;
    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(term));
    if(popOptional.hasContent())
    {
        PolynomialOverPolynomial & pop(popOptional.getReference());
        PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(pop.simplifyAndDivide());
        if(!quotientAndRemainder.quotient.isEmpty()
                && !hasNegativeExponentsWithVariable(quotientAndRemainder.quotient, m_nameOfVariableToDifferentiate))
        {
            result = differentiate(quotientAndRemainder.quotient)
                    + differentiate(quotientAndRemainder.remainder / pop.getDenominator());
        }
    }
    return result;
}

Term Differentiation::differentiateTermsInMultiplicationOrDivisionTermByTerm(
        TermsWithDetails const& termsWithDetails) const
{
    Term accumulatedTerm(1);
    if(!termsWithDetails.empty())
    {
        TermWithDetails const& firstTermWithDetails(termsWithDetails.front());
        Term const& firstTerm(getTermConstReferenceFromSharedPointer(firstTermWithDetails.baseTermSharedPointer));
        if(firstTermWithDetails.hasPositiveAssociation())
        {
            accumulatedTerm = firstTerm;
        }
        else
        {
            accumulatedTerm = differentiateTwoDividedTerms(accumulatedTerm, firstTerm);
        }
        for(auto it=termsWithDetails.cbegin()+1; it!=termsWithDetails.cend(); it++)
        {
            TermWithDetails const& termWithDetails(*it);
            Term const& currentTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
            if(termWithDetails.hasPositiveAssociation())
            {
                accumulatedTerm = differentiateTwoMultipliedTerms(accumulatedTerm, currentTerm);
            }
            else
            {
                accumulatedTerm = differentiateTwoDividedTerms(accumulatedTerm, currentTerm);
            }
        }
    }
    return accumulatedTerm;
}

Term Differentiation::differentiateTermsInRaiseToPower(
        Expression const& expression) const
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    TermRaiseToTerms termRaiseToTerms(termsWithDetails);
    termRaiseToTerms.simplify();
    Term firstTerm(termRaiseToTerms.getBase());
    Term secondTerm(termRaiseToTerms.getCombinedExponents());
    bool isFirstAChangingTerm = isChangingTerm(firstTerm);
    bool isSecondAChangingTerm = isChangingTerm(secondTerm);
    if(!isFirstAChangingTerm && !isSecondAChangingTerm)
    {
        result = 0;
    }
    else if(!isFirstAChangingTerm && isSecondAChangingTerm)
    {
        result = differentiateNonChangingTermRaiseToChangingTerm(firstTerm, secondTerm);
    }
    else if(isFirstAChangingTerm && !isSecondAChangingTerm)
    {
        result = differentiateChangingTermRaiseToNonChangingTerm(firstTerm, secondTerm);
    }
    else
    {
        result = differentiateChangingTermRaiseToChangingTerm(firstTerm, secondTerm);
    }
    return result;
}

Term Differentiation::differentiateNonChangingTermRaiseToChangingTerm(
        Term const& base,
        Term const& exponent) const
{
    Term derivativeCauseOfChainRule(differentiate(exponent));
    return createExpressionIfPossible({base, "^", exponent, "*", ln(base), "*", derivativeCauseOfChainRule});
}

Term Differentiation::differentiateChangingTermRaiseToNonChangingTerm(
        Term const& base,
        Term const& exponent) const
{
    Term derivativeCauseOfChainRule(differentiate(base));
    return createExpressionIfPossible({base, "^", exponent-1, "*", exponent, "*", derivativeCauseOfChainRule});
}

Term Differentiation::differentiateChangingTermRaiseToChangingTerm(
        Term const& ,
        Term const& ) const
{
    return AlbaNumber(AlbaNumber::Value::NotANumber);
}

Term Differentiation::differentiateFunctionOnly(
        Function const& functionObject) const
{
    Term derivativeOfFunction(AlbaNumber(AlbaNumber::Value::NotANumber));
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if("abs" == functionObject.getFunctionName())
    {
        derivativeOfFunction = sgn(inputTerm);
    }
    else if("ln" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({1, "/", inputTerm});
    }
    else if("log" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({::log(10), "/", inputTerm});
    }
    else if("sin" == functionObject.getFunctionName())
    {
        derivativeOfFunction = cos(inputTerm);
    }
    else if("cos" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({-1, "*", sin(inputTerm)});
    }
    else if("tan" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({sec(inputTerm), "^", 2});
    }
    else if("csc" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({-1, "*", csc(inputTerm), "*", cot(inputTerm)});
    }
    else if("sec" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({sec(inputTerm), "*", tan(inputTerm)});
    }
    else if("cot" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({-1, "*", csc(inputTerm), "^", 2});
    }
    else if("arcsin" == functionObject.getFunctionName())
    {
        Term oneMinusInputSquared(createExpressionIfPossible({1, "-", inputTerm, "^", 2}));
        Term squareRootTerm(createExpressionIfPossible({oneMinusInputSquared, "^", AlbaNumber::createFraction(1, 2)}));
        derivativeOfFunction = createExpressionIfPossible({1, "/", squareRootTerm});
    }
    else if("arccos" == functionObject.getFunctionName())
    {
        Term oneMinusInputSquared(createExpressionIfPossible({1, "-", inputTerm, "^", 2}));
        Term squareRootTerm(createExpressionIfPossible({oneMinusInputSquared, "^", AlbaNumber::createFraction(1, 2)}));
        derivativeOfFunction = createExpressionIfPossible({-1, "/", squareRootTerm});
    }
    else if("arctan" == functionObject.getFunctionName())
    {
        Term onePlusInputSquared(createExpressionIfPossible({1, "+", inputTerm, "^", 2}));
        derivativeOfFunction = createExpressionIfPossible({1, "/", onePlusInputSquared});
    }
    else if("arccsc" == functionObject.getFunctionName())
    {
        Term inputSquaredMinusOne(createExpressionIfPossible({inputTerm, "^", 2, "-", 1}));
        Term squareRootTerm(createExpressionIfPossible({inputSquaredMinusOne, "^", AlbaNumber::createFraction(1, 2)}));
        derivativeOfFunction = createExpressionIfPossible({-1, "/", inputTerm, "/", squareRootTerm});
    }
    else if("arcsec" == functionObject.getFunctionName())
    {
        Term inputSquaredMinusOne(createExpressionIfPossible({inputTerm, "^", 2, "-", 1}));
        Term squareRootTerm(createExpressionIfPossible({inputSquaredMinusOne, "^", AlbaNumber::createFraction(1, 2)}));
        derivativeOfFunction = createExpressionIfPossible({1, "/", inputTerm, "/", squareRootTerm});
    }
    else if("arccot" == functionObject.getFunctionName())
    {
        Term onePlusInputSquared(createExpressionIfPossible({1, "+", inputTerm, "^", 2}));
        derivativeOfFunction = createExpressionIfPossible({-1, "/", onePlusInputSquared});
    }
    else if("sinh" == functionObject.getFunctionName())
    {
        derivativeOfFunction = cosh(inputTerm);
    }
    else if("cosh" == functionObject.getFunctionName())
    {
        derivativeOfFunction = sinh(inputTerm);
    }
    else if("tanh" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({sech(inputTerm), "^", 2});
    }
    else if("csch" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({-1, "*", csch(inputTerm), "*", coth(inputTerm)});
    }
    else if("sech" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({-1, "*", sech(inputTerm), "*", tanh(inputTerm)});
    }
    else if("coth" == functionObject.getFunctionName())
    {
        derivativeOfFunction = createExpressionIfPossible({-1, "*", csch(inputTerm), "^", 2});
    }
    return derivativeOfFunction;
}

bool Differentiation::isVariableToDifferentiate(
        string const& variableName) const
{
    return variableName == m_nameOfVariableToDifferentiate;
}

bool Differentiation::isDependentVariable(
        string const& variableName) const
{
    return m_namesOfDependentVariables.find(variableName) != m_namesOfDependentVariables.cend();
}

bool Differentiation::isDerivativeVariableNameAndAffectedByThisDifferentiation(
        DerivativeVariableName const& derivativeVariableName) const
{
    return derivativeVariableName.isValid()
            && isVariableToDifferentiate(derivativeVariableName.getBaseVariable())
            && isDependentVariable(derivativeVariableName.getDependentVariable());
}

bool Differentiation::isChangingVariableName(
        string const& variableName) const
{
    bool result(false);
    if(isVariableToDifferentiate(variableName) || isDependentVariable(variableName))
    {
        result = true;
    }
    else
    {
        DerivativeVariableName derivativeVariableName(variableName);
        result = isDerivativeVariableNameAndAffectedByThisDifferentiation(derivativeVariableName);
    }
    return result;
}

bool Differentiation::isChangingTerm(
        Term const& term) const
{
    VariableNamesRetriever retriever;
    retriever.retrieveFromTerm(term);
    VariableNamesSet const& variableNames(retriever.getSavedData());
    return any_of(variableNames.cbegin(), variableNames.cend(),
                  [&](string const& variableName)
    {
        return isChangingVariableName(variableName);
    });
}


}

}
