#include "RetrieveHelpers.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba
{

namespace algebra
{

AlbaNumbersSet getNumbers(Term const& term)
{
    AlbaNumbersSet result;
    retrieveNumbers(result, term);
    return result;
}

void retrieveNumbers(AlbaNumbersSet & numbers, Term const& term)
{
    if(term.isConstant())
    {
        retrieveNumbers(numbers, term.getConstantConstReference());
    }
    else if(term.isMonomial())
    {
        retrieveNumbers(numbers, term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        retrieveNumbers(numbers, term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        retrieveNumbers(numbers, term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        retrieveNumbers(numbers, term.getFunctionConstReference());
    }
}

void retrieveNumbers(AlbaNumbersSet & numbers, Constant const& constant)
{
    numbers.emplace(constant.getNumberConstReference());
}

void retrieveNumbers(AlbaNumbersSet & numbers, Monomial const& monomial)
{
    numbers.emplace(monomial.getConstantConstReference());
    for(Monomial::VariableExponentPair const& variableExponentsPair
        : monomial.getVariablesToExponentsMapConstReference())
    {
        numbers.emplace(variableExponentsPair.second);
    }
}

void retrieveNumbers(AlbaNumbersSet & numbers, Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        retrieveNumbers(numbers, monomial);
    }
}

void retrieveNumbers(AlbaNumbersSet & numbers, Expression const& expression)
{
    for(TermsWithAssociation::TermWithDetails const& termWithDetails
        : expression.getTermsWithAssociation().getTermsWithDetails())
    {
        retrieveNumbers(numbers, getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
    }
}

void retrieveNumbers(AlbaNumbersSet & numbers, Function const& functionObject)
{
    retrieveNumbers(numbers, functionObject.getInputExpressionConstReference());
}

VariableNamesSet getVariableNames(Term const& term)
{
    VariableNamesSet result;
    retrieveVariableNames(result, term);
    return result;
}

void retrieveVariableNames(VariableNamesSet & variableNames, Term const& term)
{
    if(term.isVariable())
    {
        retrieveVariableNames(variableNames, term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        retrieveVariableNames(variableNames, term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        retrieveVariableNames(variableNames, term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        retrieveVariableNames(variableNames, term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        retrieveVariableNames(variableNames, term.getFunctionConstReference());
    }
}

void retrieveVariableNames(VariableNamesSet & variableNames, Variable const& variable)
{
    variableNames.emplace(variable.getVariableName());
}

void retrieveVariableNames(VariableNamesSet & variableNames, Monomial const& monomial)
{
    for(Monomial::VariableExponentPair const& variableExponentsPair
        : monomial.getVariablesToExponentsMapConstReference())
    {
        variableNames.emplace(variableExponentsPair.first);
    }
}

void retrieveVariableNames(VariableNamesSet & variableNames, Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        retrieveVariableNames(variableNames, monomial);
    }
}

void retrieveVariableNames(VariableNamesSet & variableNames, Expression const& expression)
{
    for(TermsWithAssociation::TermWithDetails const& termWithDetails
        : expression.getTermsWithAssociation().getTermsWithDetails())
    {
        retrieveVariableNames(variableNames, getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
    }
}

void retrieveVariableNames(VariableNamesSet & variableNames, Function const& functionObject)
{
    retrieveVariableNames(variableNames, functionObject.getInputExpressionConstReference());
}

FunctionsSet getFunctionsWithCondition(
        Term const& term,
        FunctionCondition const& isFunctionIncluded)
{
    FunctionsSet result;
    retrieveFunctionsWithCondition(result, term, isFunctionIncluded);
    return result;
}

void retrieveFunctionsWithCondition(
        FunctionsSet & functions,
        Term const& term,
        FunctionCondition const& isFunctionIncluded)
{
    if(term.isExpression())
    {
        retrieveFunctionsWithCondition(functions, term.getExpressionConstReference(), isFunctionIncluded);
    }
    else if(term.isFunction())
    {
        retrieveFunctionsWithCondition(functions, term.getFunctionConstReference(), isFunctionIncluded);
    }
}

void retrieveFunctionsWithCondition(
        FunctionsSet & functions,
        Expression const& expression,
        FunctionCondition const& isFunctionIncluded)
{
    for(TermsWithAssociation::TermWithDetails const& termWithDetails
        : expression.getTermsWithAssociation().getTermsWithDetails())
    {
        retrieveFunctionsWithCondition(
                    functions,
                    getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer),
                    isFunctionIncluded);
    }
}

void retrieveFunctionsWithCondition(
        FunctionsSet & functions,
        Function const& functionObject,
        FunctionCondition const& isFunctionIncluded)
{
    if(isFunctionIncluded(functionObject))
    {
        functions.emplace(functionObject);
    }
}

}

}