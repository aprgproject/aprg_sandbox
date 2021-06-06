#include "Expression.hpp"

#include <Optional/AlbaOptional.hpp>
#include <PerformOperation.hpp>
#include <Term.hpp>
#include <Utilities.hpp>

#include <algorithm>
#include <sstream>

using namespace std;
using AssociationType=alba::equation::TermsWithPriorityAndAssociation::AssociationType;
using TermWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermWithDetails;using TermsWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermsWithDetails;

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

bool Expression::isEmpty() const
{
    return m_termsWithPriorityAndAssociation.isEmpty();
}

bool Expression::containsOnlyOneTerm() const
{
    return 1 == m_termsWithPriorityAndAssociation.getSize();
}

OperatorLevel Expression::getCommonOperatorLevel() const
{
    return m_commonOperatorLevel;
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
    result << "( " << getEnumShortString(m_commonOperatorLevel) << "||";
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));        if(isFirst)
        {
            result << getFirstStringIfNegativeAssociation(m_commonOperatorLevel, termWithDetails.association);
            isFirst=false;
        }
        else
        {
            result << getOperatingString(m_commonOperatorLevel, termWithDetails.association);
        }
        result << getEnumShortString(termWithDetails.association) << term.getDisplayableString();
    }
    result << " )";
    return result.str();
}
void Expression::simplify()
{
    TermsWithDetails termsToUpdate;
    simplifyAndCopyTerms(termsToUpdate, m_termsWithPriorityAndAssociation.getTermsWithDetails());
    m_termsWithPriorityAndAssociation.clear();
    combineTermAndSave(termsToUpdate);
}

void Expression::clearAndSetTerm(BaseTerm const& baseTerm){
    m_termsWithPriorityAndAssociation.clear();
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
    m_commonOperatorLevel = OperatorLevel::Unknown;
}

void Expression::addTerm(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnAdditionOrSubtraction(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            *this = createOrCopyExpressionFromATerm(
                        getTermConstReferenceFromBaseTerm(baseTerm));
        }
        else
        {
            switch(m_commonOperatorLevel)
            {
            case OperatorLevel::Unknown:
                m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            case OperatorLevel::AdditionAndSubtraction:
            {
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
                break;
            }
            case OperatorLevel::MultiplicationAndDivision:
            case OperatorLevel::RaiseToPower:
            {
                clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
                m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
                break;
            }
            }
        }
    }
}

void Expression::subtractTerm(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnAdditionOrSubtraction(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
        }
        else
        {
            switch(m_commonOperatorLevel)
            {
            case OperatorLevel::Unknown:
                m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            case OperatorLevel::AdditionAndSubtraction:
            {
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
                break;
            }
            case OperatorLevel::MultiplicationAndDivision:
            case OperatorLevel::RaiseToPower:
            {
                clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
                m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
                break;
            }
            }
        }
    }
}

void Expression::multiplyTerm(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            *this = createOrCopyExpressionFromATerm(
                        getTermConstReferenceFromBaseTerm(baseTerm));
        }
        else
        {
            switch(m_commonOperatorLevel)
            {
            case OperatorLevel::Unknown:
                m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            case OperatorLevel::MultiplicationAndDivision:
            {
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
                break;
            }
            case OperatorLevel::AdditionAndSubtraction:
            case OperatorLevel::RaiseToPower:
            {
                clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
                m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
                break;
            }
            }
        }
    }
}

void Expression::divideTerm(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
        }
        else
        {
            switch(m_commonOperatorLevel)
            {
            case OperatorLevel::Unknown:
                m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            case OperatorLevel::MultiplicationAndDivision:
            {
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
                break;
            }
            case OperatorLevel::AdditionAndSubtraction:
            case OperatorLevel::RaiseToPower:
            {
                clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
                m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
                break;
            }
            }
        }
    }
}

void Expression::raiseToPowerTerm(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            *this = createOrCopyExpressionFromATerm(
                        getTermConstReferenceFromBaseTerm(baseTerm));
        }
        else
        {
            switch(m_commonOperatorLevel)
            {
            case OperatorLevel::Unknown:
                m_commonOperatorLevel = OperatorLevel::RaiseToPower;
            case OperatorLevel::RaiseToPower:
            {
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
                break;
            }
            case OperatorLevel::AdditionAndSubtraction:
            case OperatorLevel::MultiplicationAndDivision:
            {
                clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
                m_commonOperatorLevel = OperatorLevel::RaiseToPower;
                putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
                break;
            }
            }
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

void Expression::putTermForExpressionAndNonExpressions(
        BaseTerm const& baseTerm,
        AssociationType const overallAssociation)
{
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(term.isExpression())
    {
        Expression const & expression(term.getExpressionConstReference());
        if(!expression.isEmpty())
        {
            if(m_commonOperatorLevel == expression.getCommonOperatorLevel() ||
                    OperatorLevel::Unknown == expression.getCommonOperatorLevel())
            {
                putTermsWithAssociation(expression.getTerms(), overallAssociation);
            }
            else
            {
                putTerm(baseTerm, overallAssociation);
            }
        }
    }
    else if(term.isValueTermButNotAnExpression())
    {
        putTerm(baseTerm, overallAssociation);
    }
}

void Expression::putTerm(BaseTerm const& baseTerm, AssociationType const overallAssociation)
{
    if(AssociationType::Positive == overallAssociation)
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
    }
    else if(AssociationType::Negative == overallAssociation)
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
    }
}

void Expression::putTermsWithAssociation(TermsWithPriorityAndAssociation const& termsWithAssociation, AssociationType const overallAssociation)
{
    TermsWithPriorityAndAssociation newTermsWithAssociation(termsWithAssociation);
    if(AssociationType::Negative == overallAssociation)
    {
        newTermsWithAssociation.reverseTheAssociationOfTheTerms();
    }
    for(TermWithDetails const& termWithDetails : newTermsWithAssociation.getTermsWithDetails())
    {
        m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::simplifyAndCopyTerms(
        TermsWithDetails & termsToUpdate,
        TermsWithDetails const& termsToCheck)
{
    for(TermWithDetails const& termWithDetails : termsToCheck)
    {
        BaseTerm const& baseTerm(getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));        if(term.isExpression())
        {
            Expression expression(term.getExpressionConstReference());
            expression.simplify();
            simplifyAndCopyTermsFromAnExpression(termsToUpdate, expression, termWithDetails.association);
        }
        else if(term.isValueTermButNotAnExpression())
        {
            termsToUpdate.emplace_back(baseTerm, termWithDetails.association);
        }
    }
}

void Expression::simplifyAndCopyTermsFromAnExpression(
        TermsWithDetails & termsToUpdate,
        Expression const& expression,
        AssociationType const association)
{
    OperatorLevel expressionOperatorLevel(expression.getCommonOperatorLevel());
    if(expression.containsOnlyOneTerm() || OperatorLevel::Unknown == m_commonOperatorLevel || expressionOperatorLevel == m_commonOperatorLevel)
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
        simplifyAndCopyTerms(termsToUpdate, termsWithAssociation.getTermsWithDetails());
    }
    else
    {
        termsToUpdate.emplace_back(getBaseTermConstReferenceFromTerm(Term(expression)), association);
    }
}

void Expression::combineTermAndSave(TermsWithDetails & termsToCombine)
{
    Term combinedTerm;
    combineTermAndSaveBaseOnOperatorLevel(getBaseTermReferenceFromTerm(combinedTerm), termsToCombine);
    saveCombinedTerm(getBaseTermReferenceFromTerm(combinedTerm));
}

void Expression::combineTermAndSaveBaseOnOperatorLevel(BaseTerm & combinedBaseTerm, TermsWithDetails & termsToCombine)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:    {
        saveTerms(termsToCombine);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    {
        processAndSaveTermsForAdditionAndSubtraction(combinedBaseTerm, termsToCombine);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:    {
        accumulateTermsForMultiplicationAndDivision(combinedBaseTerm, termsToCombine);
        break;
    }
    case OperatorLevel::RaiseToPower:
    {
        accumulateTermsForRaiseToPower(combinedBaseTerm, termsToCombine);
        break;
    }
    }
}

void Expression::processAndSaveTermsForAdditionAndSubtraction(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails & termsToCombine)
{
    sortTermsForAdditionAndSubtraction(termsToCombine);
    accumulateTermsForAdditionAndSubtraction(combinedBaseTerm, termsToCombine);
}

void Expression::sortTermsForAdditionAndSubtraction(
        TermsWithDetails & termsToSort)
{
    stable_sort(termsToSort.begin(), termsToSort.end(), [](
                TermWithDetails const& termWithDetails1,
                TermWithDetails const& termWithDetails2)
    {
        Term const& term1(getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
        Term const& term2(getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
        return term1.isValueTermButNotAnExpression() > term2.isValueTermButNotAnExpression();
    });
}

void Expression::accumulateTermsForAdditionAndSubtraction(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails & termsToCombine)
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    bool isFirst(true);    for(TermWithDetails const& termWithDetails : termsToCombine)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(willHaveNoEffectOnAdditionOrSubtraction(term))
        {
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

void Expression::accumulateTermsForMultiplicationAndDivision(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails & termsToCombine)
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    bool isFirst(true);    for(TermWithDetails const& termWithDetails : termsToCombine)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
        {
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

void Expression::accumulateTermsForRaiseToPower(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails & termsToCombine)
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    bool isFirst(true);    for(TermWithDetails const& termWithDetails : termsToCombine)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
        {
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

void Expression::saveCombinedTerm(BaseTerm const& combinedBaseTerm)
{
    Term const& combinedTerm(getTermConstReferenceFromBaseTerm(combinedBaseTerm));
    if(combinedTerm.isExpression())    {
        for(TermWithDetails const& termWithDetails : combinedTerm.getExpressionConstReference().getTerms().getTermsWithDetails())
        {
            m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
        }
    }
    else if(combinedTerm.isValueTermButNotAnExpression())
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(getBaseTermConstReferenceFromTerm(combinedTerm));
    }
}

void Expression::saveTerms(TermsWithDetails const& termsToSave)
{
    for(TermWithDetails const& termWithDetails : termsToSave)
    {
        m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
    }
}

}

}
