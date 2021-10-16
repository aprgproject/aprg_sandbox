#include "Integration.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{
namespace algebra
{

namespace
{
    static string C = "C";
}

Integration::Integration(
        string const& nameOfVariableToIntegrate)
    : m_nameOfVariableToIntegrate(nameOfVariableToIntegrate)
{}

Term Integration::integrate(Term const& term) const
{
    return integrateTerm(term);
}

Term Integration::integrate(Constant const& constant) const
{
    return Term(integrateConstant(constant));
}

Term Integration::integrate(Variable const& variable) const
{
    Term result(integrateVariable(variable));
    result.simplify();
    return result;
}

Term Integration::integrate(Monomial const& monomial) const
{
    Term result(integrateMonomial(monomial));
    result.simplify();
    return result;
}

Term Integration::integrate(Polynomial const& polynomial) const
{
    Term result(integratePolynomial(polynomial));
    result.simplify();
    return result;
}

Term Integration::integrate(Expression const& expression) const
{
    return integrateExpression(expression);
}

Term Integration::integrate(Function const& functionObject) const
{
    return integrateFunction(functionObject);
}

Term Integration::integrateWithPlusC(Term const& term) const
{
    Term result(createExpressionIfPossible({integrateTerm(term), Term("+"), Term(C)}));
    result.simplify();
    return result;
}

Term Integration::integrateTerm(Term const& term) const
{
    Term result;
    if(term.isConstant())
    {
        result = integrate(term.getConstantConstReference());
    }
    else if(term.isVariable())
    {
        result = integrate(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        result = integrate(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = integrate(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = integrate(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        result = integrate(term.getFunctionConstReference());
    }
    return result;
}

Monomial Integration::integrateConstant(Constant const& constant) const
{
    return Monomial(constant.getNumberConstReference(), {{m_nameOfVariableToIntegrate, 1}});
}

Monomial Integration::integrateVariable(Variable const& variable) const
{
    Monomial result;
    string const& nameOfVariable(variable.getVariableName());
    if(isVariableToIntegrate(nameOfVariable))
    {
        result = Monomial(AlbaNumber::createFraction(1, 2), {{variable.getVariableName(), 2}});
    }
    else
    {
        result = Monomial(1, {{variable.getVariableName(), 1}, {m_nameOfVariableToIntegrate, 1}});
    }
    return result;
}

Monomial Integration::integrateMonomial(Monomial const& monomial) const
{
    Monomial result(monomial);
    bool hasVariabletoIntegrate(false);
    for(auto const& variableExponentPair :
        monomial.getVariablesToExponentsMapConstReference())
    {
        string const& variableName(variableExponentPair.first);
        AlbaNumber const& exponent(variableExponentPair.second);
        if(isVariableToIntegrate(variableName))
        {
            result.putVariableWithExponent(variableName, exponent+1);
            result.divideNumber(exponent+1);
            hasVariabletoIntegrate = true;
        }
    }
    if(!hasVariabletoIntegrate)
    {
        result.putVariableWithExponent(m_nameOfVariableToIntegrate, 1);
    }
    result.simplify();
    return result;
}

Polynomial Integration::integratePolynomial(Polynomial const& polynomial) const
{
    Polynomial result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result.addMonomial(integrateMonomial(monomial));
    }
    result.simplify();
    return result;
}

Term Integration::integrateExpression(
        Expression const& expression) const
{
    return integrateAsTermOrExpressionIfNeeded(expression);
}

Term Integration::integrateFunction(
        Function const& functionObject) const
{
    return integrateFunctionOnly(functionObject);
}

bool Integration::isVariableToIntegrate(
        string const& variableName) const
{
    return variableName == m_nameOfVariableToIntegrate;
}

Term Integration::integrateUsingChainRule(
        Term const& outerTerm,
        Term const& innerTerm) const
{
    Differentiation differentiation(m_nameOfVariableToIntegrate);
    return Term(createExpressionIfPossible({outerTerm, Term("/"), differentiation.differentiate(innerTerm)}));
}

Term Integration::integrateAsTermOrExpressionIfNeeded(
        Expression const& expression) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    Term simplifiedTerm(expression);
    simplifiedTerm.simplify();
    if(simplifiedTerm.isExpression())
    {
        result = integrateSimplifiedExpressionOnly(simplifiedTerm.getExpressionConstReference());
    }
    else
    {
        result = integrate(simplifiedTerm);
    }
    return result;
}

Term Integration::integrateSimplifiedExpressionOnly(
        Expression const& expression) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        result = integrateTermsInAdditionOrSubtraction(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        result = integrateTermsInMultiplicationOrDivision(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = integrateTermsInRaiseToPower(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    result.simplify();
    return result;
}

Term Integration::integrateTermsInAdditionOrSubtraction(
        TermsWithDetails const& termsWithDetails) const
{
    Expression accumulatedExpression(createOrCopyExpressionFromATerm(Constant(0)));
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& currentTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term integratedTerm(integrate(currentTerm));
        if(termWithDetails.hasPositiveAssociation())
        {
            accumulatedExpression.putTermWithAdditionIfNeeded(integratedTerm);
        }
        else
        {
            accumulatedExpression.putTermWithSubtractionIfNeeded(integratedTerm);
        }
    }
    return Term(accumulatedExpression);
}

Term Integration::integrateTermsInMultiplicationOrDivision(
        TermsWithDetails const& termsWithDetails) const
{
    //implement this
    return Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

Term Integration::integrateTermsInRaiseToPower(
        TermsWithDetails const& termsWithDetails) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    if(termsWithDetails.size() == 2)
    {
        Term const& firstTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
        Term const& secondTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
        if(firstTerm.isConstant())
        {
            result = integrateConstantRaiseToTerm(firstTerm.getConstantValueConstReference(), secondTerm);
        }
        else if(secondTerm.isConstant())
        {
            result = integrateTermRaiseToConstant(firstTerm, secondTerm.getConstantValueConstReference());
        }
        else
        {
            result = integrateTermRaiseToTerm(firstTerm, secondTerm);
        }
    }
    return result;
}

Term Integration::integrateConstantRaiseToTerm(
        AlbaNumber const& number,
        Term const& term) const
{
    //implement this
    return Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

Term Integration::integrateTermRaiseToConstant(
        Term const& term,
        AlbaNumber const& number) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    if(getDegreeForVariableToIntegrate(term) == 1)
    {
        result = integrateUsingChainRule(Term(createExpressionIfPossible(
        {term, Term("^"), Term(number+1), Term("/"), Term(number+1)})), term);
    }
    return result;
}

Term Integration::integrateTermRaiseToTerm(
        Term const& ,
        Term const& ) const
{
    return Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

Term Integration::integrateFunctionOnly(
        Function const& functionObject) const
{
    Term integrationOfFunction(AlbaNumber(AlbaNumber::Value::NotANumber));
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if(getDegreeForVariableToIntegrate(inputTerm) == 1)
    {
        if("sin" == functionObject.getFunctionName())
        {
            integrationOfFunction = integrateUsingChainRule(Term(createExpressionIfPossible({Term(-1), Term("*"), cos(inputTerm)})), inputTerm);
        }
        else if("cos" == functionObject.getFunctionName())
        {
            integrationOfFunction = integrateUsingChainRule(Term(sin(inputTerm)), inputTerm);
        }
        /*else if("tan" == functionObject.getFunctionName())
        {
            integrationOfFunction = Term(createExpressionIfPossible({sec(inputTerm), Term("^"), Term(2)}));
        }
        else if("csc" == functionObject.getFunctionName())
        {
            integrationOfFunction = Term(createExpressionIfPossible({Term(-1), Term("*"), csc(inputTerm), Term("*"), cot(inputTerm)}));
        }
        else if("sec" == functionObject.getFunctionName())
        {
            integrationOfFunction = Term(createExpressionIfPossible({sec(inputTerm), Term("*"), tan(inputTerm)}));
        }
        else if("cot" == functionObject.getFunctionName())
        {
            integrationOfFunction = Term(createExpressionIfPossible({Term(-1), Term("*"), csc(inputTerm), Term("^"), Term(2)}));
        }*/
    }
    integrationOfFunction.simplify();
    return integrationOfFunction;
}

AlbaNumber Integration::getDegreeForVariableToIntegrate(Term const& term) const
{
    AlbaNumber result(0);
    if(term.isVariable() && isVariableToIntegrate(term.getVariableConstReference().getVariableName()))
    {
        result = 1;
    }
    else if(term.isMonomial())
    {
        result = term.getMonomialConstReference().getExponentForVariable(m_nameOfVariableToIntegrate);
    }
    else if(term.isPolynomial())
    {
        result = term.getPolynomialConstReference().getDegreeForVariable(m_nameOfVariableToIntegrate);
    }
    return result;
}


}

}
