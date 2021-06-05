#include "TermsSimplificator.hpp"

#include <PerformOperation.hpp>
#include <Utilities.hpp>


#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

namespace equation
{

TermsSimplificator::TermsSimplificator(Terms const& terms)
    : m_terms(terms)
{}

Terms const& TermsSimplificator::getTermsConstReference() const
{
    return m_terms;
}

void TermsSimplificator::buildExpressionFromTerms()
{
    bool continueToSimplify(true);
    while(continueToSimplify)
    {
        AlbaOptional<unsigned int> nextOperatorIndexOptional(getNextOperatorIndexToPerform());
        continueToSimplify = nextOperatorIndexOptional.hasContent();
        ALBA_PRINT2(continueToSimplify, nextOperatorIndexOptional.hasContent());
        if(nextOperatorIndexOptional.hasContent())
        {
            unsigned int nextOperatorIndex = nextOperatorIndexOptional.get();
            ALBA_PRINT3(continueToSimplify, nextOperatorIndex, m_terms.size());
            continueToSimplify = buildExpressionWithBinaryOperationAndReturnIfBuilt(nextOperatorIndex);
            if(!continueToSimplify)
            {
                continueToSimplify = buildExpressionWithUnaryOperationAndReturnIfBuilt(nextOperatorIndex);
            }
        }
        ALBA_PRINT2(continueToSimplify, m_terms.size());
        for(Term const& term : m_terms)
        {
            ALBA_PRINT2(static_cast<unsigned int>(term.getTermType()), term.getDisplayableString());
        }
    }
}

void TermsSimplificator::simplifyTerms()
{
    bool continueToSimplify(true);
    while(continueToSimplify)
    {
        AlbaOptional<unsigned int> nextOperatorIndexOptional(getNextOperatorIndexToPerform());
        continueToSimplify = nextOperatorIndexOptional.hasContent();
        ALBA_PRINT2(continueToSimplify, nextOperatorIndexOptional.hasContent());
        if(nextOperatorIndexOptional.hasContent())
        {
            unsigned int nextOperatorIndex = nextOperatorIndexOptional.get();
            ALBA_PRINT3(continueToSimplify, nextOperatorIndex, m_terms.size());
            continueToSimplify = simplifyBinaryOperationAndReturnIfSimplified(nextOperatorIndex);
            if(!continueToSimplify)
            {
                continueToSimplify=simplifyUnaryOperationAndReturnIfSimplified(nextOperatorIndex);
            }
        }
        ALBA_PRINT2(continueToSimplify, m_terms.size());
        for(Term const& term : m_terms)
        {
            ALBA_PRINT2(getTermPriorityValue(term), term.getDisplayableString());
        }
    }
}

AlbaOptional<unsigned int> TermsSimplificator::getNextOperatorIndexToPerform() const
{
    AlbaOptional<unsigned int> operatorIndexOptional;
    multimap<unsigned int, unsigned int> operatorLevelToIndexMap;
    for(unsigned int i=0; i<m_terms.size(); i++)
    {
        Term const& term(m_terms[i]);
        if(term.isOperator())
        {
            operatorLevelToIndexMap.emplace(term.getOperatorConstReference().getOperatorLevelValue(), i);
        }
    }
    if(!operatorLevelToIndexMap.empty())
    {
        pair<unsigned int, unsigned int> operatorLevelToIndexPair(*operatorLevelToIndexMap.rbegin());
        operatorIndexOptional.setValue(operatorLevelToIndexPair.second);
    }
    return operatorIndexOptional;
}

bool TermsSimplificator::buildExpressionWithBinaryOperationAndReturnIfBuilt(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms[index-1]);
        Term const& term2(m_terms[index]);
        Term const& term3(m_terms[index+1]);
        if(term1.isValueTerm() && term2.isOperator() && term3.isValueTerm())
        {
            Expression newExpression(convertTermToExpression(term1));
            Operator const& operatorTerm(term2.getOperatorConstReference());
            if(operatorTerm.isAddition())
            {
                newExpression.addTerm(createBaseTermSharedPointerFromTerm(term3));
            }
            else if(operatorTerm.isSubtraction())
            {
                newExpression.subtractTerm(createBaseTermSharedPointerFromTerm(term3));
            }
            else if(operatorTerm.isMultiplication())
            {
                newExpression.multiplyTerm(createBaseTermSharedPointerFromTerm(term3));
            }
            else if(operatorTerm.isDivision())
            {
                newExpression.divideTerm(createBaseTermSharedPointerFromTerm(term3));
            }
            else if(operatorTerm.isRaiseToPower())
            {
                newExpression.raiseToPowerTerm(createBaseTermSharedPointerFromTerm(term3));
            }
            Term newTerm(newExpression);
            eraseTermsInclusive(index-1, index+1);
            insertTerm(index-1, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

bool TermsSimplificator::buildExpressionWithUnaryOperationAndReturnIfBuilt(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index+1]);
        if(term1.isOperator() && term2.isValueTerm() &&
                OperatorLevel::AdditionAndSubtraction == term2.getOperatorConstReference().getOperatorLevel())
        {
            Expression newExpression;
            Operator const& operatorTerm(term1.getOperatorConstReference());
            if(operatorTerm.isAddition())
            {
                newExpression.addTerm(createBaseTermSharedPointerFromTerm(term2));
            }
            else if(operatorTerm.isSubtraction())
            {
                newExpression.subtractTerm(createBaseTermSharedPointerFromTerm(term2));
            }
            Term newTerm(newExpression);
            eraseTermsInclusive(index, index+1);
            insertTerm(index, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

bool TermsSimplificator::simplifyBinaryOperationAndReturnIfSimplified(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms[index-1]);
        Term const& term2(m_terms[index]);
        Term const& term3(m_terms[index+1]);
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

bool TermsSimplificator::simplifyUnaryOperationAndReturnIfSimplified(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index+1]);
        if(term1.isOperator() && term2.isValueTerm() &&
                OperatorLevel::AdditionAndSubtraction == term2.getOperatorConstReference().getOperatorLevel())
        {
            Term newTerm = performOperation(term2.getOperatorConstReference(), term1);
            eraseTermsInclusive(index, index+1);
            insertTerm(index, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

void TermsSimplificator::eraseTermsInclusive(
        unsigned int const firstIndex,
        unsigned int const secondIndex)
{
    m_terms.erase(m_terms.cbegin()+firstIndex, m_terms.cbegin()+secondIndex+1);
}

void TermsSimplificator::insertTerm(
        unsigned int const index,
        Term const& term)
{
    m_terms.emplace(m_terms.cbegin()+index, term);
}

}

}
