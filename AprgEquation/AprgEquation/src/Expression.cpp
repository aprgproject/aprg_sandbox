#include "Expression.hpp"

#include <Optional/AlbaOptional.hpp>
#include <PerformOperation.hpp>
#include <Term.hpp>
#include <Utilities.hpp>

#include <sstream>


#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

namespace equation
{

Expression::Expression()
    : m_commonOperatorLevel(OperatorLevel::Unknown)
{}

Expression::Expression(BaseTermSharedPointer const& sharedPointer)
    : m_commonOperatorLevel(OperatorLevel::Unknown)
{
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
}

Expression::~Expression()
{}

bool Expression::operator==(Expression const& second) const
{
    return m_commonOperatorLevel == second.m_commonOperatorLevel
            && m_termsWithPriorityAndAssociation==second.m_termsWithPriorityAndAssociation;
}

bool Expression::containsOnlyOneTerm() const
{
    return getNumberOfTerms()==1;
}

OperatorLevel Expression::getCommonOperatorLevel() const
{
    return m_commonOperatorLevel;
}

unsigned int Expression::getNumberOfTerms() const
{
    return m_termsWithPriorityAndAssociation.getSize();
}

string Expression::getDisplayableString() const
{
    bool isFirst(true);
    stringstream result;
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
    for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
        if(!isFirst)
        {
            if(termWithDetails.hasPositiveAssociation())
            {
                switch(m_commonOperatorLevel)
                {
                case OperatorLevel::AdditionAndSubtraction:
                    result << "+";
                    break;
                case OperatorLevel::MultiplicationAndDivision:
                    result << "*";
                    break;
                case OperatorLevel::RaiseToPower:
                    result << "^";
                    break;
                default:
                    break;
                }
            }
            else if(termWithDetails.hasNegativeAssociation())
            {
                switch(m_commonOperatorLevel)
                {
                case OperatorLevel::AdditionAndSubtraction:
                    result << "-";
                    break;
                case OperatorLevel::MultiplicationAndDivision:
                    result << "/";
                    break;
                default:
                    break;
                }
            }
        }
        isFirst=false;
        result << term.getDisplayableString();
    }
    return result.str();
}

BaseTermSharedPointer const& Expression::getFirstTermConstReference() const
{
    return m_termsWithPriorityAndAssociation.getFirstTermConstReference();
}

TermsWithPriorityAndAssociation const& Expression::getTerms() const
{
    return m_termsWithPriorityAndAssociation;
}

void Expression::clearAndSetTerm(BaseTermSharedPointer const& sharedPointer)
{
    m_termsWithPriorityAndAssociation.clear();
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
    m_commonOperatorLevel = OperatorLevel::Unknown;
}

void Expression::addTerm(BaseTermSharedPointer const& sharedPointer)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(createBaseTermSharedPointerFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    }
}

void Expression::subtractTerm(BaseTermSharedPointer const& sharedPointer)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(createBaseTermSharedPointerFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(sharedPointer);
        break;
    }
    }
}

void Expression::multiplyTerm(BaseTermSharedPointer const& sharedPointer)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(createBaseTermSharedPointerFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    }
}

void Expression::divideTerm(BaseTermSharedPointer const& sharedPointer)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(createBaseTermSharedPointerFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(sharedPointer);
        break;
    }
    }
}

void Expression::raiseToPowerTerm(BaseTermSharedPointer const& sharedPointer)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::RaiseToPower:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::MultiplicationAndDivision:
    {
        clearAndSetTerm(createBaseTermSharedPointerFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(sharedPointer);
        break;
    }
    }
}


void performOperationForTermDetails(
        Term & newTerm,
        OperatorLevel const operatorLevel,
        TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails)
{
    Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
    switch(operatorLevel)
    {
    case OperatorLevel::AdditionAndSubtraction:
    {
        if(termWithDetails.hasPositiveAssociation())
        {
            newTerm = performAddition(newTerm, term);
        }
        else if(termWithDetails.hasNegativeAssociation())
        {
            newTerm = performSubtraction(newTerm, term);
        }
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    {
        if(termWithDetails.hasPositiveAssociation())
        {
            newTerm = performMultiplication(newTerm, term);
        }
        else if(termWithDetails.hasNegativeAssociation())
        {
            newTerm = performDivision(newTerm, term);
        }
        break;
    }
    case OperatorLevel::RaiseToPower:
    {
        if(termWithDetails.hasPositiveAssociation())
        {
            newTerm = performRaiseToPower(newTerm, term);
        }
        break;
    }
    default:
        break;
    }
}

void Expression::simplify()
{
    TermsWithPriorityAndAssociation::TermsWithDetails onlySimplifiedExpressions;
    TermsWithPriorityAndAssociation::TermsWithDetails onlyValueTermsNonExpressions;
    TermsWithPriorityAndAssociation::TermsWithDetails inputTerms(
                m_termsWithPriorityAndAssociation.getTermsWithDetails());
    for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails : inputTerms)
    {
        Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
        ALBA_PRINT3(term.isExpression(), term.isValueTermButNotAnExpression(), term.getDisplayableString());
        if(term.isExpression())
        {
            Expression expression(term.getExpressionConstReference());
            expression.simplify();
            if(expression.containsOnlyOneTerm())
            {
                Term const& oneTermInExpression = *dynamic_cast<Term const*const>(expression.getFirstTermConstReference().get());
                if(oneTermInExpression.isExpression())
                {
                    onlySimplifiedExpressions.emplace_back(createBaseTermSharedPointerFromTerm(oneTermInExpression), termWithDetails.association);
                }
                else if(term.isValueTermButNotAnExpression())
                {
                    onlyValueTermsNonExpressions.emplace_back(createBaseTermSharedPointerFromTerm(oneTermInExpression), termWithDetails.association);
                }
            }
            else if(expression.getCommonOperatorLevel() == m_commonOperatorLevel)
            {
                TermsWithPriorityAndAssociation::TermsWithDetails termsInSubExpression(
                            m_termsWithPriorityAndAssociation.getTermsWithDetails());
                for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetailsInSubExpression : termsInSubExpression)
                {
                    Term const& termInSubExpression = *dynamic_cast<Term const*const>(termWithDetailsInSubExpression.baseTermSharedPointer.get());
                    if(termInSubExpression.isExpression())
                    {
                        onlySimplifiedExpressions.emplace_back(createBaseTermSharedPointerFromTerm(termInSubExpression), termWithDetailsInSubExpression.association);
                    }
                    else if(termInSubExpression.isValueTermButNotAnExpression())
                    {
                        onlyValueTermsNonExpressions.emplace_back(createBaseTermSharedPointerFromTerm(termInSubExpression), termWithDetailsInSubExpression.association);
                    }
                }
            }
            else
            {
                onlySimplifiedExpressions.emplace_back(createBaseTermSharedPointerFromTerm(term), termWithDetails.association);
            }
        }
        else if(term.isValueTermButNotAnExpression())
        {
            onlyValueTermsNonExpressions.emplace_back(createBaseTermSharedPointerFromTerm(term), termWithDetails.association);
        }
    }
    Term newTermCombinedNonExpressions;
    bool isFirst(true);
    for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails : onlyValueTermsNonExpressions)
    {
        Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
        ALBA_PRINT2(isFirst, term.getDisplayableString());
        if((OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel &&  term.isTheValueZero()) ||
                (OperatorLevel::MultiplicationAndDivision == m_commonOperatorLevel &&  term.isTheValueOne()) ||
                (OperatorLevel::RaiseToPower == m_commonOperatorLevel &&  term.isTheValueOne()))
        {
            continue;
        }
        else if(isFirst)
        {
            newTermCombinedNonExpressions = term;
            isFirst=false;
        }
        else
        {
            performOperationForTermDetails(newTermCombinedNonExpressions, m_commonOperatorLevel, termWithDetails);
        }
    }
    m_termsWithPriorityAndAssociation.clear();
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(createBaseTermSharedPointerFromTerm(newTermCombinedNonExpressions));
    for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails : onlyValueTermsNonExpressions)
    {
        Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
        ALBA_PRINT2(static_cast<unsigned int>(term.getTermType()), term.getDisplayableString());
        m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
    }
}

}

}
