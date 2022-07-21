#include "SubstitutionOfTermsToTerms.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms()
{}

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms(initializer_list<TermTermPair> const& variablesWithValues)
{
    putTermsToTermsMapping(variablesWithValues);
}

SubstitutionOfTermsToTerms::SubstitutionOfTermsToTerms(TermToTermMap const& variablesWithValues)
{
    putTermsToTermsMapping(variablesWithValues);
}

bool SubstitutionOfTermsToTerms::isEmpty() const
{
    return m_termsToTermsMap.empty();
}

bool SubstitutionOfTermsToTerms::isTermFound(Term const& term) const
{
    return m_termsToTermsMap.find(term) != m_termsToTermsMap.cend();
}

unsigned int SubstitutionOfTermsToTerms::getSize() const
{
    return m_termsToTermsMap.size();
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

Term SubstitutionOfTermsToTerms::performSubstitutionTo(Function const& functionObject) const
{
    Term result;
    Term functionTerm(functionObject);
    if(isTermFound(functionTerm))
    {
        result = getTermForTerm(functionTerm);
    }
    else
    {
        result = simplifyAndConvertFunctionToSimplestTerm(performSubstitutionForFunction(functionObject));
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

Equation SubstitutionOfTermsToTerms::performSubstitutionTo(
        Equation const& equation) const
{
    Equation simplifiedEquation(
                performSubstitutionTo(equation.getLeftHandTerm()),
                equation.getEquationOperator().getOperatorString(),
                performSubstitutionTo(equation.getRightHandTerm()));
    simplifiedEquation.simplify();
    return simplifiedEquation;
}

Expression SubstitutionOfTermsToTerms::performSubstitutionForExpression(Expression const& expression) const
{
    Expression newExpression(expression);
    performSubstitutionForTermsWithAssociation(newExpression.getTermsWithAssociationReference());
    newExpression.simplify();
    return newExpression;
}
Function SubstitutionOfTermsToTerms::performSubstitutionForFunction(Function const& functionObject) const
{
    Function newFunction(functionObject);
    getTermReferenceFromBaseTerm(newFunction.getInputTermReference())
            = performSubstitutionTo(functionObject.getInputTermConstReference());
    newFunction.simplify();
    return newFunction;
}
void SubstitutionOfTermsToTerms::putTermsToTermsMapping(initializer_list<TermTermPair> const& variablesWithValues)
{
    for(TermTermPair const& variableValuesPair : variablesWithValues)    {
        putTermToTermMapping(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfTermsToTerms::putTermsToTermsMapping(TermToTermMap const& variablesWithValues)
{
    for(auto const& variableValuesPair : variablesWithValues)
    {
        putTermToTermMapping(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfTermsToTerms::putTermToTermMapping(Term const& term1, Term const& term2)
{
    m_termsToTermsMap[term1]=term2;
}

void SubstitutionOfTermsToTerms::performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const
{
    for(TermWithDetails & termWithDetails : termsWithAssociation.getTermsWithDetailsReference())
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        term = performSubstitutionTo(term);
    }
}

}

}
