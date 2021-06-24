#include "SubstitutionOfTermsToTerms.hpp"

#include <Equation/Utilities.hpp>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms()
{}

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms(std::initializer_list<TermTermPair> const& variablesWithValues)
{
    putTermsToTermsMapping(variablesWithValues);
}

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms(TermToTermMap const& variablesWithValues)
{
    putTermsToTermsMapping(variablesWithValues);
}

bool SubstitutionOfTermsToTerms::isTermFound(Term const& term) const
{
    return m_termsToTermsMap.find(term) != m_termsToTermsMap.cend();
}

Term SubstitutionOfTermsToTerms::getTermForTerm(Term const& term) const
{
    Term result;
    if(isTermFound(term))
    {
        result = m_termsToTermsMap.at(term);
    }
    return result;
}

Term SubstitutionOfTermsToTerms::performSubstitutionTo(Expression const& expression) const
{
    Term result;
    Term expressionTerm(expression);
    if(isTermFound(expressionTerm))
    {
        result = getTermForTerm(expressionTerm);
    }
    else
    {
        result = simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
    }
    return result;
}

Term SubstitutionOfTermsToTerms::performSubstitutionTo(Function const& functionAsParameter) const
{
    Term result;
    Term functionTerm(functionAsParameter);
    if(isTermFound(functionTerm))
    {
        result = getTermForTerm(functionTerm);
    }
    else
    {
        result = simplifyAndConvertFunctionToSimplestTerm(performSubstitutionForFunction(functionAsParameter));
    }
    return result;
}

Term SubstitutionOfTermsToTerms::performSubstitutionTo(Term const& term) const
{
    Term newTerm(term);
    if(isTermFound(term))
    {
        newTerm = getTermForTerm(term);
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

Expression SubstitutionOfTermsToTerms::performSubstitutionForExpression(Expression const& expression) const
{
    Expression newExpression(expression);
    performSubstitutionForTermsWithAssociation(newExpression.getTermsWithAssociationReference());
    return newExpression;
}

Function SubstitutionOfTermsToTerms::performSubstitutionForFunction(Function const& functionAsParameter) const
{
    Function newFunction(functionAsParameter);
    newFunction.getInputExpressionReference()
            = performSubstitutionForExpression(functionAsParameter.getInputExpressionConstReference());
    return newFunction;
}

void SubstitutionOfTermsToTerms::performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const
{
    for(TermWithDetails & termWithDetails : termsWithAssociation.getTermsWithDetailsReference())
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        term = performSubstitutionTo(term);
    }
}

void SubstitutionOfTermsToTerms::putTermsToTermsMapping(initializer_list<TermTermPair> const& variablesWithValues)
{
    for(TermTermPair const& variableValuesPair : variablesWithValues)
    {
        putTermToTermMapping(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfTermsToTerms::putTermsToTermsMapping(TermToTermMap const& variablesWithValues)
{
    for(TermTermPair const& variableValuesPair : variablesWithValues)
    {
        putTermToTermMapping(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfTermsToTerms::putTermToTermMapping(Term const& term1, Term const& term2)
{
    m_termsToTermsMap[term1]=term2;
}

}

}
