#include "SubstitutionOfVariablesToExpressions.hpp"

#include <Equation/Utilities.hpp>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

SubstitutionOfVariablesToExpressions::SubstitutionOfVariablesToExpressions(
        initializer_list<VariableExpressionPair> const& variablesWithExpressions)
{
    putVariablesWithExpressions(variablesWithExpressions);
}

SubstitutionOfVariablesToExpressions::SubstitutionOfVariablesToExpressions(
        VariablesToExpressionsMap const& variablesWithExpressions)
{
    putVariablesWithExpressions(variablesWithExpressions);
}

bool SubstitutionOfVariablesToExpressions::isVariableFound(string const& variable) const
{
    return m_variableToExpressionsMap.find(variable) != m_variableToExpressionsMap.cend();
}

Expression SubstitutionOfVariablesToExpressions::getExpressionForVariable(string const& variable) const
{
    Expression result;
    if(isVariableFound(variable))
    {
        result = m_variableToExpressionsMap.at(variable);
    }
    return result;
}

Term SubstitutionOfVariablesToExpressions::performSubstitutionTo(Variable const& variable) const
{
    Term result;
    string variableName(variable.getVariableName());
    if(isVariableFound(variableName))
    {
        result = Term(getExpressionForVariable(variableName));
    }
    else
    {
        result = Term(variable);
    }
    return result;
}

Term SubstitutionOfVariablesToExpressions::performSubstitutionTo(Monomial const& monomial) const
{
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForMonomial(monomial));
}

Term SubstitutionOfVariablesToExpressions::performSubstitutionTo(Polynomial const& polynomial) const
{
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForPolynomial(polynomial));
}

Term SubstitutionOfVariablesToExpressions::performSubstitutionTo(Expression const& expression) const
{
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
}

Term SubstitutionOfVariablesToExpressions::performSubstitutionTo(Term const& term) const
{
    Term newTerm;
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
    return newTerm;
}

Expression SubstitutionOfVariablesToExpressions::performSubstitutionForMonomial(Monomial const& monomial) const
{
    Monomial newMonomial(createMonomialFromConstant(monomial.getConstantConstReference()));
    Monomial::VariablesToExponentsMap previousVariableExponentMap(monomial.getVariablesToExponentsMapConstReference());
    Expression substitutedExpressions;
    for(Monomial::VariableExponentPair const& variableExponentPair : previousVariableExponentMap)
    {
        if(isVariableFound(variableExponentPair.first))
        {
            Expression substitutedExpression(Term(getExpressionForVariable(variableExponentPair.first)));
            substitutedExpression.putTermWithRaiseToPowerIfNeeded(Term(variableExponentPair.second));
            substitutedExpressions.putTermWithMultiplicationIfNeeded(Term(substitutedExpression));
        }
        else
        {
            newMonomial.putVariableWithExponent(variableExponentPair.first, variableExponentPair.second);
        }
    }
    Expression finalExpression(getBaseTermConstReferenceFromTerm(Term(newMonomial)));
    finalExpression.putTermWithMultiplicationIfNeeded(Term(substitutedExpressions));
    return finalExpression;
}

Expression SubstitutionOfVariablesToExpressions::performSubstitutionForPolynomial(Polynomial const& polynomial) const
{
    Expression newExpression;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        newExpression.putTermWithAdditionIfNeeded(Term(performSubstitutionForMonomial(monomial)));
    }
    return newExpression;
}

Expression SubstitutionOfVariablesToExpressions::performSubstitutionForExpression(Expression const& expression) const
{
    Expression newExpression(expression);
    performSubstitutionForTermsWithAssociation(newExpression.getTermsWithAssociationReference());
    return newExpression;
}

void SubstitutionOfVariablesToExpressions::performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const
{
    for(TermWithDetails & termWithDetails : termsWithAssociation.getTermsWithDetailsReference())
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        term = performSubstitutionTo(term);
    }
}

void SubstitutionOfVariablesToExpressions::putVariablesWithExpressions(
        initializer_list<VariableExpressionPair> const& variablesWithExpressions)
{
    for(VariableExpressionPair const& variableValuesPair : variablesWithExpressions)
    {
        putVariableWithValue(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToExpressions::putVariablesWithExpressions(
        VariablesToExpressionsMap const& variablesWithExpressions)
{
    for(VariableExpressionPair const& variableValuesPair : variablesWithExpressions)
    {
        putVariableWithValue(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToExpressions::putVariableWithValue(string const& variable, Expression const& expression)
{
    m_variableToExpressionsMap[variable]=expression;
}

}

}
