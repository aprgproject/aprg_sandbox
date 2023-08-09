#include "TermsAggregator.hpp"

#include <Equation/Operations/PerformOperations.hpp>
#include <Equation/Utilities.hpp>

using namespace std;
namespace alba
{

namespace equation
{

TermsAggregator::TermsAggregator(Terms const& terms)
    : m_terms(terms)
{}

Terms const& TermsAggregator::getTermsConstReference() const
{
    return m_terms;
}

void TermsAggregator::buildExpressionFromTerms()
{
    traverse(AggregatorTraverseSteps::BuildExpression);
}

void TermsAggregator::simplifyTerms()
{
    traverse(AggregatorTraverseSteps::Simplify);
}

void TermsAggregator::traverse(AggregatorTraverseSteps const traverseSteps)
{
    bool continueToCombine(true);
    while(continueToCombine)
    {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
        bool continueToTraverse(true);
        while(continueToTraverse)
        {
            AlbaOptional<unsigned int> nextOperatorIndexOptional(getNextOperatorIndexToTraverse());
            continueToTraverse = nextOperatorIndexOptional.hasContent();
            if(nextOperatorIndexOptional.hasContent())
            {
                unsigned int nextOperatorIndex = nextOperatorIndexOptional.get();
                continueToTraverse = performTraverseStepsWithBinaryOperationAndReturnIfContinue(traverseSteps, nextOperatorIndex);
                if(!continueToTraverse)
                {
                    continueToTraverse = performTraverseStepsWithUnaryOperationAndReturnIfContinue(traverseSteps, nextOperatorIndex);
                }
            }
        }
        continueToCombine = combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined();
    }
}

void TermsAggregator::updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators()
{
    m_startIndex=0;
    m_endIndex=0;
    if(!m_terms.empty())
    {
        m_endIndex=m_terms.size()-1;
    }
    for(unsigned int i=0; i<m_terms.size(); i++)
    {
        Term const& term(m_terms.at(i));
        if(term.isOperator())
        {
            Operator const& operatorTerm(term.getOperatorConstReference());
            if(operatorTerm.isOpeningGroupOperator())
            {
                m_startIndex = i;
                m_endIndex = i;
            }
            else if(operatorTerm.isClosingGroupOperator())
            {
                m_endIndex = i;
                break;
            }
        }
    }
}

bool TermsAggregator::combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined()
{
    bool isCombined(false);
    if(m_startIndex+2==m_endIndex && m_endIndex < m_terms.size())
    {
        Term const& term1(m_terms.at(m_startIndex));
        Term const& term2(m_terms.at(m_startIndex+1));
        Term const& term3(m_terms.at(m_endIndex));
        if(term1.isOperator() && term1.getOperatorConstReference().isOpeningGroupOperator()
                && term2.isValueTerm()
                && term3.isOperator() && term3.getOperatorConstReference().isClosingGroupOperator())
        {
            Term newTerm(term2);
            eraseTermsInclusive(m_startIndex, m_endIndex);
            insertTerm(m_startIndex, newTerm);
            isCombined=true;
        }
    }
    return isCombined;
}

bool TermsAggregator::performTraverseStepsWithBinaryOperationAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps,
        unsigned int const nextOperatorIndex)
{
    bool continueToTraverse(true);
    if(AggregatorTraverseSteps::BuildExpression == traverseSteps)
    {
        continueToTraverse = buildExpressionWithBinaryOperationAndReturnIfBuilt(nextOperatorIndex);
    }
    else if(AggregatorTraverseSteps::Simplify == traverseSteps)
    {
        continueToTraverse = simplifyBinaryOperationAndReturnIfSimplified(nextOperatorIndex);
    }
    return continueToTraverse;
}

bool TermsAggregator::performTraverseStepsWithUnaryOperationAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps,
        unsigned int const nextOperatorIndex)
{
    bool continueToTraverse(true);
    if(AggregatorTraverseSteps::BuildExpression == traverseSteps)
    {
        continueToTraverse = buildExpressionWithUnaryOperationAndReturnIfBuilt(nextOperatorIndex);
    }
    else if(AggregatorTraverseSteps::Simplify == traverseSteps)
    {
        continueToTraverse = simplifyUnaryOperationAndReturnIfSimplified(nextOperatorIndex);
    }
    return continueToTraverse;
}

AlbaOptional<unsigned int> TermsAggregator::getNextOperatorIndexToTraverse() const
{
    AlbaOptional<unsigned int> operatorIndexOptional;
    multimap<unsigned int, unsigned int> operatorLevelToIndexMap;
    for(unsigned int i=m_startIndex; i<m_endIndex; i++)
    {
        Term const& term(m_terms.at(i));
        if(term.isOperator())
        {
            Operator const& operatorTerm(term.getOperatorConstReference());
            if(operatorTerm.isAnOperatorThatCanPerformed())
            {
                operatorLevelToIndexMap.emplace(getOperatorLevelInversePriority(operatorTerm.getOperatorLevel()), i);
            }
        }
    }
    if(!operatorLevelToIndexMap.empty())
    {
        pair<unsigned int, unsigned int> operatorLevelToIndexPair(*operatorLevelToIndexMap.begin());
        operatorIndexOptional.setValue(operatorLevelToIndexPair.second);
    }
    return operatorIndexOptional;
}

bool TermsAggregator::buildExpressionWithBinaryOperationAndReturnIfBuilt(unsigned int const index)
{
    bool isBuilt(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms.at(index-1));
        Term const& term2(m_terms.at(index));
        Term const& term3(m_terms.at(index+1));
        if(term1.isValueTerm() && term2.isOperator() && term3.isValueTerm())
        {
            Expression newExpression(createOrCopyExpressionFromATerm(term1));
            Operator const& operatorTerm(term2.getOperatorConstReference());
            if(operatorTerm.isAddition())
            {
                newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(term3));
            }
            else if(operatorTerm.isSubtraction())
            {
                newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(term3));
            }
            else if(operatorTerm.isMultiplication())
            {
                newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(term3));
            }
            else if(operatorTerm.isDivision())
            {
                newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(term3));
            }
            else if(operatorTerm.isRaiseToPower())
            {
                newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(term3));
            }
            Term newTerm(newExpression);
            eraseTermsInclusive(index-1, index+1);
            insertTerm(index-1, newTerm);
            isBuilt=true;
        }
    }
    return isBuilt;
}

bool TermsAggregator::buildExpressionWithUnaryOperationAndReturnIfBuilt(unsigned int const index)
{
    bool isBuilt(false);
    if(index+1 < m_terms.size())
    {
        Term const& term1(m_terms.at(index));
        Term const& term2(m_terms.at(index+1));
        if(term1.isOperator() && term2.isValueTerm() &&
                OperatorLevel::AdditionAndSubtraction == term1.getOperatorConstReference().getOperatorLevel())
        {
            Expression newExpression;
            Operator const& operatorTerm(term1.getOperatorConstReference());
            if(operatorTerm.isAddition())
            {
                newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(term2));
            }
            else if(operatorTerm.isSubtraction())
            {
                newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(term2));
            }
            Term newTerm(newExpression);
            eraseTermsInclusive(index, index+1);
            insertTerm(index, newTerm);
            isBuilt=true;
        }
    }
    return isBuilt;
}

bool TermsAggregator::simplifyBinaryOperationAndReturnIfSimplified(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms.at(index-1));
        Term const& term2(m_terms.at(index));
        Term const& term3(m_terms.at(index+1));
        if(term1.isValueTerm() && term2.isOperator() && term3.isValueTerm())
        {
            Term newTerm = performOperation(term2.getOperatorConstReference(), term1, term3);
            eraseTermsInclusive(index-1, index+1);
            insertTerm(index-1, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

bool TermsAggregator::simplifyUnaryOperationAndReturnIfSimplified(unsigned int const index)
{
    bool isSimplified(false);
    if(index+1 < m_terms.size())
    {
        Term const& term1(m_terms.at(index));
        Term const& term2(m_terms.at(index+1));
        if(term1.isOperator() && term2.isValueTerm() &&
                OperatorLevel::AdditionAndSubtraction == term1.getOperatorConstReference().getOperatorLevel())
        {
            Term newTerm = performOperation(term1.getOperatorConstReference(), term2);
            eraseTermsInclusive(index, index+1);
            insertTerm(index, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

void TermsAggregator::eraseTermsInclusive(
        unsigned int const firstIndex,
        unsigned int const secondIndex)
{
    bool isOutsideStartAndEndIndex(m_startIndex>firstIndex || m_endIndex<secondIndex);
    m_terms.erase(m_terms.cbegin()+firstIndex, m_terms.cbegin()+secondIndex+1);
    if(isOutsideStartAndEndIndex)
    {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    }
    else
    {
        m_endIndex = m_endIndex-(secondIndex-firstIndex+1);
    }
}

void TermsAggregator::insertTerm(
        unsigned int const index,
        Term const& term)
{
    bool isOutsideStartAndEndIndex(m_startIndex>index || m_endIndex<index);
    m_terms.emplace(m_terms.cbegin()+index, term);
    if(isOutsideStartAndEndIndex)
    {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    }
    else
    {
        m_endIndex++;
    }
}

}

}
