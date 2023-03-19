#include "SegregateTermsByConditionInAdditionAndSubtractionRetriever.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

SegregateTermsByConditionInAdditionAndSubtractionRetriever::SegregateTermsByConditionInAdditionAndSubtractionRetriever(
        ConditionFunction const& condition)
    : m_condition(condition)
{}

Term const& SegregateTermsByConditionInAdditionAndSubtractionRetriever::getTermWithCondition() const
{
    return m_termWithCondition;
}

Term const& SegregateTermsByConditionInAdditionAndSubtractionRetriever::getTermWithoutCondition() const
{
    return m_termWithoutCondition;
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromConstant(
        Constant const& constant)
{
    saveTerm(Term(constant));
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromVariable(
        Variable const& variable)
{
    saveTerm(Term(variable));
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromMonomial(
        Monomial const& monomial)
{
    saveTerm(Term(monomial));
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromPolynomial(
        Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        retrieveFromMonomial(monomial);
    }
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromExpression(
        Expression const& expression)
{
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        for(TermWithDetails const& termWithDetails
            : expression.getTermsWithAssociation().getTermsWithDetails())
        {
            if(termWithDetails.hasPositiveAssociation())
            {
                retrieveFromTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
            }
            else
            {
                retrieveFromTerm(negateTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer)));
            }
        }
    }
    else
    {
        saveTerm(Term(expression));
    }
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromFunction(
        Function const& functionObject)
{
    saveTerm(Term(functionObject));
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::retrieveFromTerm(
        Term const& term)
{
    if(term.isConstant())
    {
        retrieveFromConstant(term.getConstantConstReference());
    }
    else if(term.isVariable())
    {
        retrieveFromVariable(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        retrieveFromMonomial(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        retrieveFromPolynomial(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        retrieveFromExpression(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        retrieveFromFunction(term.getFunctionConstReference());
    }
}

void SegregateTermsByConditionInAdditionAndSubtractionRetriever::saveTerm(
        Term const& term)
{
    if(m_condition(term))
    {
        m_termWithCondition += term;
    }
    else
    {
        m_termWithoutCondition += term;
    }
}

}

}
