#include "Expression.hpp"

#include <Optional/AlbaOptional.hpp>
#include <PerformOperation.hpp>
#include <Term.hpp>
#include <Utilities.hpp>

#include <sstream>

using namespace std;
using AssociationType=alba::equation::TermsWithPriorityAndAssociation::AssociationType;
using TermWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{
Expression::Expression()
    : m_commonOperatorLevel(OperatorLevel::Unknown)
{}

Expression::Expression(BaseTerm const& baseTerm)
    : m_commonOperatorLevel(OperatorLevel::Unknown)
{
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
}

Expression::~Expression()
{}

bool Expression::operator==(Expression const& second) const
{
    return m_commonOperatorLevel == second.m_commonOperatorLevel
            && m_termsWithPriorityAndAssociation==second.m_termsWithPriorityAndAssociation;
}

bool Expression::containsNoTerms() const
{
    return 0 == m_termsWithPriorityAndAssociation.getSize();
}

bool Expression::containsOnlyOneTerm() const
{
    return 1 == m_termsWithPriorityAndAssociation.getSize();
}

OperatorLevel Expression::getCommonOperatorLevel() const
{    return m_commonOperatorLevel;
}

BaseTerm const& Expression::getFirstTermConstReference() const
{
    return m_termsWithPriorityAndAssociation.getFirstTermConstReference();
}

TermsWithPriorityAndAssociation const& Expression::getTerms() const
{
    return m_termsWithPriorityAndAssociation;
}

string Expression::getDisplayableString() const
{
    bool isFirst(true);
    stringstream result;
    TermsWithDetails const& termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
    result << "(";
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(isFirst)
        {
            result << getFirstStringIfNegativeAssociation(m_commonOperatorLevel, termWithDetails.association);
            isFirst=false;
        }
        else
        {
            result << getOperatingString(m_commonOperatorLevel, termWithDetails.association);
        }
        result << term.getDisplayableString();
    }    result << ")";
    return result.str();
}

void Expression::simplify()
{
    TermsWithDetails termsToCombine;
    TermsWithDetails termsNotToCombine;
    segregateTerms(termsToCombine, termsNotToCombine, m_termsWithPriorityAndAssociation.getTermsWithDetails());
    m_termsWithPriorityAndAssociation.clear();
    processTermsToCombine(termsToCombine, termsNotToCombine);
    processTermsNotToCombine(termsNotToCombine);
}

void Expression::clearAndSetTerm(BaseTerm const& baseTerm)
{
    m_termsWithPriorityAndAssociation.clear();
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
    m_commonOperatorLevel = OperatorLevel::Unknown;}

void Expression::addTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    }
}

void Expression::subtractTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
        break;
    }
    }
}

void Expression::multiplyTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    }
}

void Expression::divideTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
        break;
    }
    }
}

void Expression::raiseToPowerTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
    case OperatorLevel::RaiseToPower:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::MultiplicationAndDivision:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    }
}

void Expression::setCommonOperatorLevel(OperatorLevel const operatorLevel)
{
    m_commonOperatorLevel = operatorLevel;
}

void Expression::reverseTheAssociationOfTheTerms()
{
    m_termsWithPriorityAndAssociation.reverseTheAssociationOfTheTerms();
}

void Expression::segregateTerms(
        TermsWithDetails & termsToCombine,
        TermsWithDetails & termsNotToCombine,
        TermsWithDetails const& termsToSegregate)
{
    for(TermWithDetails const& termWithDetails : termsToSegregate)
    {
        BaseTerm const& baseTerm(getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
        if(term.isExpression())
        {
            Expression expression(term.getExpressionConstReference());
            expression.simplify();
            segregateTermsInExpression(termsToCombine, termsNotToCombine, expression, termWithDetails.association);
        }
        else if(term.isValueTermButNotAnExpression())
        {
            termsToCombine.emplace_back(baseTerm, termWithDetails.association);
        }
    }
}

void Expression::segregateTermsInExpression(
        TermsWithDetails & termsToCombine,
        TermsWithDetails & termsNotToCombine,
        Expression const& expression,
        AssociationType const association)
{
    OperatorLevel expressionOperatorLevel(expression.getCommonOperatorLevel());
    if(expression.containsOnlyOneTerm() || m_commonOperatorLevel == expressionOperatorLevel || OperatorLevel::Unknown == m_commonOperatorLevel)
    {
        if(OperatorLevel::Unknown == m_commonOperatorLevel)
        {
            m_commonOperatorLevel = expression.getCommonOperatorLevel();
        }
        TermsWithPriorityAndAssociation termsWithAssociation(expression.getTerms());
        if(AssociationType::Negative == association)
        {
            termsWithAssociation.reverseTheAssociationOfTheTerms();
        }
        segregateTerms(termsToCombine, termsNotToCombine, termsWithAssociation.getTermsWithDetails());
    }
    else
    {
        termsNotToCombine.emplace_back(getBaseTermConstReferenceFromTerm(Term(expression)), association);
    }
}

void Expression::processTermsToCombine(
        TermsWithDetails const& termsToCombine,
        TermsWithDetails & termsNotToCombine)
{
    Term combinedTerm;
    combineTerms(getBaseTermReferenceFromTerm(combinedTerm), termsToCombine);
    if(combinedTerm.isExpression())
    {
        for(TermWithDetails const& termWithDetails : combinedTerm.getExpressionConstReference().getTerms().getTermsWithDetails())
        {
            m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
        }
    }
    else if(combinedTerm.isValueTermButNotAnExpression())
    {        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(getBaseTermConstReferenceFromTerm(combinedTerm));
    }
}

void Expression::processTermsNotToCombine(TermsWithDetails const& termsNotToCombine)
{
    for(TermWithDetails const& termWithDetails : termsNotToCombine)
    {
        m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::combineTerms(BaseTerm & combinedBaseTerm, TermsWithDetails const& termsToCombine)
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    bool isFirst(true);
    for(TermWithDetails const& termWithDetails : termsToCombine)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if((OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel &&  term.isTheValueZero()) ||
                (OperatorLevel::MultiplicationAndDivision == m_commonOperatorLevel &&  term.isTheValueOne()) ||
                (OperatorLevel::RaiseToPower == m_commonOperatorLevel &&  term.isTheValueOne()))        {
            continue;
        }
        else if(isFirst)
        {
            combinedTerm = term;
            isFirst=false;
        }
        else
        {
            accumulateAndDoOperationOnTermDetails(combinedTerm, m_commonOperatorLevel, termWithDetails);
        }
    }
}

}

}
