#include "Differentiation.hpp"

#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
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
        std::string const& nameOfVariableToDifferentiate,
        VariableNamesSet const& namesOfDependentVariables)
    : m_nameOfVariableToDifferentiate(nameOfVariableToDifferentiate)
    , m_namesOfDependentVariables(namesOfDependentVariables)
{}

Term Differentiation::differentiate(Term const& term) const
{
    return differentiateTerm(term);
}

Term Differentiation::differentiate(Constant const& constant) const
{
    return Term(differentiateConstant(constant));
}

Term Differentiation::differentiate(Variable const& variable) const
{
    Term result(differentiateVariable(variable));
    result.simplify();
    return result;
}

Term Differentiation::differentiate(Monomial const& monomial) const
{
    Term result(differentiateMonomial(monomial));
    result.simplify();
    return result;
}

Term Differentiation::differentiate(Polynomial const& polynomial) const
{
    Term result(differentiatePolynomial(polynomial));
    result.simplify();
    return result;
}

Term Differentiation::differentiate(Expression const& expression) const
{
    return differentiateExpression(expression);
}

Term Differentiation::differentiate(Function const& functionObject) const
{
    return differentiateFunction(functionObject);
}

Equation Differentiation::differentiate(Equation const& equation) const
{
    return differentiateEquation(equation);
}

Term Differentiation::differentiateTerm(Term const& term) const
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

AlbaNumber Differentiation::differentiateConstant(Constant const&) const
{
    return 0;
}

Monomial Differentiation::differentiateVariable(Variable const& variable) const
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

Polynomial Differentiation::differentiateMonomial(Monomial const& monomial) const
{
    Monomial unaffectedVariablesAndConstant(monomial.getConstantConstReference(), {});
    Monomial affectedVariables(1, {});

    for(auto const& variableExponentPair :
        monomial.getVariablesToExponentsMapConstReference())
    {
        std::string const& variableName(variableExponentPair.first);
        AlbaNumber const& exponent(variableExponentPair.second);
        DerivativeVariableName derivativeVariableName(variableName);
        if(exponent != 0)
        {
            if(isVariableToDifferentiate(variableName)
                    || isDependentVariable(variableName)
                    || isDerivativeVariableNameAndAffectedByThisDifferentiation(derivativeVariableName))
            {
                affectedVariables.putVariableWithExponent(variableName, exponent);
            }
            else
            {
                unaffectedVariablesAndConstant.putVariableWithExponent(variableName, exponent);
            }
        }
    }

    Polynomial result;
    for(auto const& variableExponentPair :
        affectedVariables.getVariablesToExponentsMapConstReference())
    {
        std::string const& variableName(variableExponentPair.first);
        AlbaNumber const& exponent(variableExponentPair.second);
        Monomial monomialToAdd(affectedVariables);
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
    result.multiplyMonomial(unaffectedVariablesAndConstant);
    result.simplify();
    return result;
}

Polynomial Differentiation::differentiatePolynomial(Polynomial const& polynomial) const
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
    return differentiateAsTermOrExpressionIfNeeded(expression);
}

Term Differentiation::differentiateFunction(
        Function const& functionObject) const
{
    Term derivativeOfFunctionOnly(differentiateFunctionOnly(functionObject));
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    Term derivativeOfInputTermOfFunction(differentiate(inputTerm));
    Term result(createExpressionIfPossible({derivativeOfFunctionOnly, Term("*"), derivativeOfInputTermOfFunction}));
    result.simplify();
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
    Expression firstPart(createExpressionIfPossible({term1, Term("*"), term2Derivative}));
    Expression secondPart(createExpressionIfPossible({term2, Term("*"), term1Derivative}));
    Term result(createExpressionIfPossible({firstPart, Term("+"), secondPart}));
    result.simplify();
    return result;
}

Term Differentiation::differentiateTwoDividedTerms(
        Term const& numerator,
        Term const& denominator) const
{
    Term numeratorDerivative(differentiate(numerator));
    Term denominatorDerivative(differentiate(denominator));
    Expression resultNumeratorPart1(createExpressionIfPossible({denominator, Term("*"), numeratorDerivative}));
    Expression resultNumeratorPart2(createExpressionIfPossible({numerator, Term("*"), denominatorDerivative}));
    Expression resultNumerator(createExpressionIfPossible({resultNumeratorPart1, Term("-"), resultNumeratorPart2}));
    Expression resultDenominator(createExpressionIfPossible({denominator, Term("^"), Term(2)}));
    Term result(createExpressionIfPossible({resultNumerator, Term("/"), resultDenominator}));
    result.simplify();
    return result;
}

bool Differentiation::isVariableToDifferentiate(
        std::string const& variableName) const
{
    return variableName == m_nameOfVariableToDifferentiate;
}

bool Differentiation::isDependentVariable(
        std::string const& variableName) const
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

Term Differentiation::differentiateAsTermOrExpressionIfNeeded(
        Expression const& expression) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    Term simplifiedTerm(expression);
    simplifiedTerm.simplify();
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
        result = differentiateTermsInAdditionOrSubtraction(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        result = differentiateTermsInMultiplicationOrDivision(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = differentiateTermsInRaiseToPower(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    result.simplify();
    return result;
}

Term Differentiation::differentiateTermsInAdditionOrSubtraction(
        TermsWithDetails const& termsWithDetails) const
{
    Expression accumulatedExpression(createOrCopyExpressionFromATerm(Constant(0)));
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
    return Term(accumulatedExpression);
}

Term Differentiation::differentiateTermsInMultiplicationOrDivision(
        TermsWithDetails const& termsWithDetails) const
{
    bool isFirst(true);
    Term accumulatedTerm;
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& currentTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(isFirst)
        {
            accumulatedTerm = currentTerm;
            isFirst = false;
        }
        else
        {
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
        TermsWithDetails const& termsWithDetails) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    if(termsWithDetails.size() == 2)
    {
        Term const& firstTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
        Term const& secondTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
        if(firstTerm.isConstant())
        {
            result = differentiateConstantRaiseToTerm(firstTerm.getConstantValueConstReference(), secondTerm);
        }
        else if(secondTerm.isConstant())
        {
            result = differentiateTermRaiseToConstant(firstTerm, secondTerm.getConstantValueConstReference());
        }
        else
        {
            result = differentiateTermRaiseToTerm(firstTerm, secondTerm);
        }
    }
    return result;
}

Term Differentiation::differentiateConstantRaiseToTerm(
        AlbaNumber const& number,
        Term const& term) const
{
    Term derivativeCauseOfChainRule(differentiate(term));
    return Term(createExpressionIfPossible({Term(number), Term("^"), term, Term("*"), Term(ln(Term(number))), Term("*"), derivativeCauseOfChainRule}));
}

Term Differentiation::differentiateTermRaiseToConstant(
        Term const& term,
        AlbaNumber const& number) const
{
    Term derivativeCauseOfChainRule(differentiate(term));
    return Term(createExpressionIfPossible({Term(number), Term("*"), term, Term("^"), Term(number-1), Term("*"), derivativeCauseOfChainRule}));
}

Term Differentiation::differentiateTermRaiseToTerm(
        Term const& ,
        Term const& ) const
{
    return Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

Term Differentiation::differentiateFunctionOnly(
        Function const& functionObject) const
{
    Term derivativeOfFunction(AlbaNumber(AlbaNumber::Value::NotANumber));
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if("sin" == functionObject.getFunctionName())
    {
        derivativeOfFunction = Term(cos(inputTerm));
    }
    else if("cos" == functionObject.getFunctionName())
    {
        derivativeOfFunction = Term(createExpressionIfPossible({Term(-1), Term("*"), sin(inputTerm)}));
    }
    else if("tan" == functionObject.getFunctionName())
    {
        derivativeOfFunction = Term(createExpressionIfPossible({sec(inputTerm), Term("^"), Term(2)}));
    }
    else if("csc" == functionObject.getFunctionName())
    {
        derivativeOfFunction = Term(createExpressionIfPossible({Term(-1), Term("*"), csc(inputTerm), Term("*"), cot(inputTerm)}));
    }
    else if("sec" == functionObject.getFunctionName())
    {
        derivativeOfFunction = Term(createExpressionIfPossible({sec(inputTerm), Term("*"), tan(inputTerm)}));
    }
    else if("cot" == functionObject.getFunctionName())
    {
        derivativeOfFunction = Term(createExpressionIfPossible({Term(-1), Term("*"), csc(inputTerm), Term("^"), Term(2)}));
    }
    return derivativeOfFunction;
}


}

}
