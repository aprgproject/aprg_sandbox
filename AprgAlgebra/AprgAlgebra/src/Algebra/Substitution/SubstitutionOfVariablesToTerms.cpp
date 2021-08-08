#include "SubstitutionOfVariablesToTerms.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

SubstitutionOfVariablesToTerms::SubstitutionOfVariablesToTerms()
{}

SubstitutionOfVariablesToTerms::SubstitutionOfVariablesToTerms(
        initializer_list<VariableTermPair> const& variablesWithTerms)
{
    putVariablesWithTerms(variablesWithTerms);
}

SubstitutionOfVariablesToTerms::SubstitutionOfVariablesToTerms(
        VariablesToTermsMap const& variablesWithTerms)
{
    putVariablesWithTerms(variablesWithTerms);
}

bool SubstitutionOfVariablesToTerms::isEmpty() const
{
    return m_variableToExpressionsMap.empty();
}

bool SubstitutionOfVariablesToTerms::isVariableFound(string const& variable) const
{
    return m_variableToExpressionsMap.find(variable) != m_variableToExpressionsMap.cend();
}

unsigned int SubstitutionOfVariablesToTerms::getSize() const
{
    return m_variableToExpressionsMap.size();
}

Term SubstitutionOfVariablesToTerms::getTermForVariable(string const& variable) const
{
    Term result;
    if(isVariableFound(variable))
    {
        result = m_variableToExpressionsMap.at(variable);
    }
    return result;
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Variable const& variable) const
{
    Term result;
    string variableName(variable.getVariableName());
    if(isVariableFound(variableName))
    {
        result = getTermForVariable(variableName);
    }
    else
    {
        result = Term(variable);
    }
    return result;
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Monomial const& monomial) const
{
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForMonomial(monomial));
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Polynomial const& polynomial) const
{
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForPolynomial(polynomial));
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Expression const& expression) const
{
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Function const& functionAsParameter) const
{
    return simplifyAndConvertFunctionToSimplestTerm(performSubstitutionForFunction(functionAsParameter));
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Term const& term) const
{
    Term newTerm(term);
    if(term.isVariable())
    {
        newTerm = performSubstitutionTo(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        newTerm = performSubstitutionTo(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        newTerm = performSubstitutionTo(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        newTerm = performSubstitutionTo(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        newTerm = performSubstitutionTo(term.getFunctionConstReference());
    }
    return newTerm;
}

Equation SubstitutionOfVariablesToTerms::performSubstitutionTo(
        Equation const& equation) const
{
    Equation simplifiedEquation(
                performSubstitutionTo(equation.getLeftHandTerm()),
                equation.getEquationOperator().getOperatorString(),
                performSubstitutionTo(equation.getRightHandTerm()));
    simplifiedEquation.simplify();
    return simplifiedEquation;
}

Expression SubstitutionOfVariablesToTerms::performSubstitutionForMonomial(Monomial const& monomial) const
{
    Monomial remainingMonomial(createMonomialFromConstant(monomial.getConstantConstReference()));
    Monomial::VariablesToExponentsMap previousVariableExponentMap(monomial.getVariablesToExponentsMapConstReference());
    Expression substitutedExpressions;
    for(Monomial::VariableExponentPair const& variableExponentPair : previousVariableExponentMap)
    {
        if(isVariableFound(variableExponentPair.first))
        {
            Expression substitutedExpression(getTermForVariable(variableExponentPair.first));
            substitutedExpression.putTermWithRaiseToPowerIfNeeded(Term(variableExponentPair.second));
            substitutedExpressions.putTermWithMultiplicationIfNeeded(Term(substitutedExpression));
        }
        else
        {
            remainingMonomial.putVariableWithExponent(variableExponentPair.first, variableExponentPair.second);
        }
    }
    Expression finalExpression(getBaseTermConstReferenceFromTerm(Term(remainingMonomial)));
    finalExpression.putTermWithMultiplicationIfNeeded(Term(substitutedExpressions));
    return finalExpression;
}

Expression SubstitutionOfVariablesToTerms::performSubstitutionForPolynomial(Polynomial const& polynomial) const
{
    Expression newExpression;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        newExpression.putTermWithAdditionIfNeeded(Term(performSubstitutionForMonomial(monomial)));
    }
    return newExpression;
}

Expression SubstitutionOfVariablesToTerms::performSubstitutionForExpression(Expression const& expression) const
{
    Expression newExpression(expression);
    performSubstitutionForTermsWithAssociation(newExpression.getTermsWithAssociationReference());
    return newExpression;
}

Function SubstitutionOfVariablesToTerms::performSubstitutionForFunction(Function const& functionAsParameter) const
{
    Function newFunction(functionAsParameter);
    getTermReferenceFromBaseTerm(newFunction.getInputTermReference())
            = performSubstitutionTo(functionAsParameter.getInputTermConstReference());
    return newFunction;
}

void SubstitutionOfVariablesToTerms::performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const
{
    for(TermWithDetails & termWithDetails : termsWithAssociation.getTermsWithDetailsReference())
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        term = performSubstitutionTo(term);
    }
}

void SubstitutionOfVariablesToTerms::putVariablesWithTerms(
        initializer_list<VariableTermPair> const& variablesWithTerms)
{
    for(VariableTermPair const& variableValuesPair : variablesWithTerms)
    {
        putVariableWithTerm(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToTerms::putVariablesWithTerms(
        VariablesToTermsMap const& variablesWithTerms)
{
    for(VariableTermPair const& variableValuesPair : variablesWithTerms)
    {
        putVariableWithTerm(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToTerms::putVariableWithTerm(
        string const& variable,
        Term const& term)
{
    m_variableToExpressionsMap[variable]=term;
    m_variableToExpressionsMap.at(variable).simplify();
}

}

}