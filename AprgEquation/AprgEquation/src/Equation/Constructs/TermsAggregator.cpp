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
            continueToTraverse = traverseOnOperatorIndexesAndReturnIfContinue(traverseSteps, OperatorInputType::UnaryOperation);
            if(!continueToTraverse)
            {
                continueToTraverse = traverseOnOperatorIndexesAndReturnIfContinue(traverseSteps, OperatorInputType::BinaryOperation);
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
            Term termBeforeStart;
            if(m_startIndex>=1)
            {
                termBeforeStart = m_terms.at(m_startIndex-1);
            }
            if(m_startIndex>=1 && termBeforeStart.isFunction())
            {
                Function newFunction(termBeforeStart.getFunctionConstReference());
                newFunction.getInputExpressionReference() = createOrCopyExpressionFromATerm(term2);
                Term newTerm(newFunction);
                eraseAndThenInsert(m_startIndex-1, m_endIndex, newTerm);
                isCombined=true;
            }
            else
            {
                Term newTerm(term2);
                eraseAndThenInsert(m_startIndex, m_endIndex, newTerm);
                isCombined=true;
            }
        }
    }
    return isCombined;
}

bool TermsAggregator::traverseOnOperatorIndexesAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps,
        OperatorInputType const operatorInputType)
{
    bool continueToTraverse(false);
    Indexes nextOperatorIndexes(getNextOperatorIndexes(operatorInputType));
    for(unsigned int const nextOperatorIndex : nextOperatorIndexes)
    {
        continueToTraverse = performTraverseStepsAndReturnIfContinue(traverseSteps, nextOperatorIndex, operatorInputType);
        if(continueToTraverse)
        {
            break;
        }
    }
    return continueToTraverse;
}

bool TermsAggregator::performTraverseStepsAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps,
        unsigned int const nextOperatorIndex,
        OperatorInputType const operatorInputType)
{
    bool continueToTraverse(false);
    if(OperatorInputType::UnaryOperation == operatorInputType)
    {
        continueToTraverse = performTraverseStepsWithUnaryOperationAndReturnIfContinue(traverseSteps, nextOperatorIndex);
    }
    else if(OperatorInputType::BinaryOperation == operatorInputType)
    {
        continueToTraverse = performTraverseStepsWithBinaryOperationAndReturnIfContinue(traverseSteps, nextOperatorIndex);
    }
    return continueToTraverse;
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

TermsAggregator::Indexes TermsAggregator::getNextOperatorIndexes(OperatorInputType const operatorInputType) const
{
    Indexes operatorIndexes;
    multimap<unsigned int, unsigned int> operatorLevelToIndexMap;
    for(unsigned int i=m_startIndex; i<m_endIndex; i++)
    {
        Term const& term(m_terms.at(i));
        if(term.isOperator())
        {
            Operator const& operatorTerm(term.getOperatorConstReference());
            if(operatorTerm.isSameOperatorInputType(operatorInputType))
            {
                operatorLevelToIndexMap.emplace(getOperatorLevelInversePriority(operatorTerm.getOperatorLevel()), i);
            }
        }
    }
    for(pair<unsigned int, unsigned int> const& operatorLevelToIndexPair : operatorLevelToIndexMap)
    {
        operatorIndexes.emplace_back(operatorLevelToIndexPair.second);
    }
    return operatorIndexes;
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
                newExpression.putTermWithAdditionIfNeeded(term3);
            }
            else if(operatorTerm.isSubtraction())
            {
                newExpression.putTermWithSubtractionIfNeeded(term3);
            }
            else if(operatorTerm.isMultiplication())
            {
                newExpression.putTermWithMultiplicationIfNeeded(term3);
            }
            else if(operatorTerm.isDivision())
            {
                newExpression.putTermWithDivisionIfNeeded(term3);
            }
            else if(operatorTerm.isRaiseToPower())
            {
                newExpression.putTermWithRaiseToPowerIfNeeded(term3);
            }
            Term newTerm(newExpression);
            eraseAndThenInsert(index-1, index+1, newTerm);            isBuilt=true;
        }
    }
    return isBuilt;}

bool TermsAggregator::buildExpressionWithUnaryOperationAndReturnIfBuilt(unsigned int const index)
{
    bool isBuilt(false);
    if(index+1 < m_terms.size())
    {
        Term const& term1(m_terms.at(index));
        Term const& term2(m_terms.at(index+1));
        bool haveNoFirstValue(hasNoValueBeforeThisIndex(index));
        if(haveNoFirstValue && term1.isOperator() && term2.isValueTerm() &&
                OperatorLevel::AdditionAndSubtraction == term1.getOperatorConstReference().getOperatorLevel())
        {
            Expression newExpression;
            Operator const& operatorTerm(term1.getOperatorConstReference());
            if(operatorTerm.isAddition())
            {
                newExpression.putTermWithAdditionIfNeeded(term2);
            }
            else if(operatorTerm.isSubtraction())
            {
                newExpression.putTermWithSubtractionIfNeeded(term2);
            }
            Term newTerm(newExpression);
            eraseAndThenInsert(index, index+1, newTerm);            isBuilt=true;
        }
    }
    return isBuilt;}

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
            eraseAndThenInsert(index-1, index+1, newTerm);
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
        bool haveNoFirstValue(hasNoValueBeforeThisIndex(index));
        if(haveNoFirstValue && term1.isOperator() && term2.isValueTerm() &&
                OperatorLevel::AdditionAndSubtraction == term1.getOperatorConstReference().getOperatorLevel())
        {
            Term newTerm = performOperation(term1.getOperatorConstReference(), term2);
            eraseAndThenInsert(index, index+1, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

bool TermsAggregator::hasNoValueBeforeThisIndex(unsigned int const index)
{
    bool result(false);
    if(index==0)
    {
        result = true;
    }
    else if(index-1 < m_terms.size())
    {
        result = !m_terms.at(index-1).isValueTerm();
    }
    return result;
}

void TermsAggregator::eraseAndThenInsert(
        unsigned int const firstIndex,
        unsigned int const secondIndex,
        Term const newTerm)
{
    eraseTermsInclusive(firstIndex, secondIndex);
    insertTerm(firstIndex, newTerm);
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
